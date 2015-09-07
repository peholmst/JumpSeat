#include <cstdlib>

#include "modem_io.hpp"
#include "sms_logger.hpp"
#include "alert_dispatcher.hpp"
#include "response_dispatcher.hpp"
#include "alert_type_repository.hpp"
#include "alert_logger.hpp"

using namespace std;

int main(int argc, char** argv) {
    // Create modules
    auto modemIO = JumpSeat::ModemIO();
    auto smsLogger = JumpSeat::SMSLogger();
    auto alertTypeRepository = JumpSeat::AlertTypeRepository();
    
    auto alertDispatcher = JumpSeat::AlertDispatcher(alertTypeRepository);
    alertDispatcher.setAlertRegex(std::regex("^TKU (.+),(.*),(.*),(.*),(.*),(.*),(.*),(.*)"));
    // TODO What should this format be in? Would love to be able to use regex and extract parts of it into variables
    alertDispatcher.setAlertFormat("TKU {code}{urgency},{region},{region},{address},{address},{name},*");
    
    auto responseDispatcher = JumpSeat::ResponseDispatcher();
    auto alertLogger = JumpSeat::AlertLogger();
    
    // Set up handlers
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::SMSLogger::onReceiveSMS, &smsLogger, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::AlertDispatcher::onReceiveSMS, &alertDispatcher, _1));
    modemIO.addOnSMSHandler(boost::bind(&JumpSeat::ResponseDispatcher::onReceiveSMS, &responseDispatcher, _1));
    
    alertDispatcher.addOnAlertHandler(boost::bind(&JumpSeat::AlertLogger::onReceiveAlert, &alertLogger, _1));
    
    // Send a few fake SMSes
    modemIO.signalFakeSms("TKU 432 ,PARGAS,,address,,,RVSPG11,RVSPG31,RVSPG13,RVSIT3,,description");
    modemIO.signalFakeSms("TKU 402A,PARGAS,NAGU,address,,,RVSPG11,RVSPG31,RVSPG13,RVSIT3,,description");
    modemIO.signalFakeSms("TKU 203A,PARGAS,,address1,address2,,RVSPG11,RVSPG31,,description");
    modemIO.signalFakeSms("TKU 103 ,PARGAS,,address,,name,RVSPG11,RVSPG31,,description");
    modemIO.signalFakeSms("Another SMS");
    
    return 0;
}
