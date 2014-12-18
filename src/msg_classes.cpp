/* 
 * File:   msg_classes.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 10:49 AM
 */

#include "msg_classes.h"

#include <cstdio>
#include <stdexcept>
#include <iostream>

#include "conversions.h"

NmeaBase::NmeaBase(string raw) {
    _raw = raw;
    char type[10];
    
    if (!isMsgValid(_raw)) {
        throw std::out_of_range("Invalid NMEA message: '" + _raw + "'");
    }
    sscanf(raw.c_str(), "$%[^,],", type);
    
    _type = type;
    _epoch = 0;
}

NmeaBase::NmeaBase(const NmeaBase& orig) {
    _type = orig._type;
    _raw = orig._raw;
    _epoch = orig._epoch;
}

NmeaGga::NmeaGga(string raw): NmeaBase(raw) {
//    long time_str;
    float lat_deg, lon_deg;
    char lat_dir, lon_dir;
    
    sscanf(_raw.c_str(), "$GPGGA,%2hu%2hu%2hu,%f,%c,%f,%c,%hu,%hu,%f,%f", 
           &_time[0], &_time[1], &_time[2], &lat_deg, &lat_dir, &lon_deg, &lon_dir, &_qual, &_num_tracking, &_dilution, &_above_sea);
    
    _lat = degToDec(lat_deg, lat_dir);
    _lon = degToDec(lon_deg, lon_dir);
}
