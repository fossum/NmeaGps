/* 
 * File:   msg_classes.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 10:49 AM
 */

#include "msg_classes.h"

NmeaBase::NmeaBase(string raw, float epoch = 0) {
    _raw = raw;
    char t[10];
    
    sscanf(raw.c_str(), "$%s,", t);
    
    _type = t;
    _epoch = epoch;
}

NmeaBase::NmeaBase(const NmeaBase& orig) {
    _type = orig._type;
    _raw = orig._raw;
    _epoch = orig._epoch;
}

NmeaGga::NmeaGga(string raw) : NmeaBase(raw) {
//    long time_str;
    float lat_deg, lon_deg;
    char lat_dir, lon_dir;
    
    try {
        sscanf(raw.c_str(), "%2hu%2hu%2hu,%f,%c,%f,%c,%hu,%hu,%f,%f", 
               &_time[0], &_time[1], &_time[2], &lat_deg, &lat_dir, &lon_deg, &lon_dir, &_qual, &_num_tracking, &_dilution, &_above_sea);
    } catch(...) {
        cout << "Invalid GGA string: " << raw << endl;
    }
    
    
//    _time[0] = time_str / 10000;
//    _time[1] = (time_str % 10000) / 100;
//    _time[2] = (time_str % 100);
    
    _lat = degToDec(lat_deg, lat_dir);
    _lon = degToDec(lon_deg, lon_dir);
}
