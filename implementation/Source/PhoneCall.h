/*
 * JumpSeat
 * Copyright (C) 2015 Petter Holmström
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PHONE_CALL_H
#define	PHONE_CALL_H

#include <ctime>
#include <string>
#include <boost/signals2/signal.hpp>

#include "Time.h"

namespace JumpSeat {

    struct PhoneCall {
        std::string number;
        DateTime timestamp;
    };

    typedef boost::signals2::signal<void (const PhoneCall&) > OnPhoneCall;
    typedef OnPhoneCall::slot_type OnPhoneCallHandler;
}

#endif	/* PHONE_CALL_H */

