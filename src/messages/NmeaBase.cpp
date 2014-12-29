/* 
 * File:   NmeaBase.cpp
 * Author: ericfoss
 * 
 * Created on December 28, 2014, 3:36 PM
 */

#include "messages/NmeaBase.h"

#include <cassert>
#include <cstdio>
#include <iostream>

#include "utilities.h"

NmeaBase::NmeaBase() {
    _raw = "";
    _type = "";
    _epoch = 0;
}

NmeaBase::NmeaBase(string raw) {
    _raw = raw;
    char type[10];
    
    if (!isMsgValid(_raw)) {
        std::cerr << "Invalid NMEA message: '" << _raw << "'" << std::endl;
        assert(0);
        throw std::out_of_range("invalid NMEA");
    }
    sscanf(_raw.c_str(), "$%[^,],", type);
    
    _type = type;
    _epoch = 0;
}

NmeaBase::NmeaBase(const NmeaBase& orig) {
    _type = orig._type;
    _raw = orig._raw;
    _epoch = orig._epoch;
}

NmeaBase::~NmeaBase() {
}
