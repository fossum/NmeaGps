/* 
 * File:   NmeaGga.cpp
 * Author: ericfoss
 * 
 * Created on December 28, 2014, 4:02 PM
 */

#include "messages/NmeaGga.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utilities.h"

NmeaGga::NmeaGga(): NmeaBase() {
    _time[0] = 0;
    _time[1] = 0;
    _time[2] = 0;
    _lat = 0;
    _lon = 0;
    _qual = 0;
    _num_tracking = 0;
    _dilution = 0;
    _above_sea = 0;
}

NmeaGga::NmeaGga(string raw): NmeaBase(raw) {
//    long time_str;
    char str[100], *ptr;
    int index = 0;
    
    float lat_deg, lon_deg;
    char lat_dir, lon_dir;
    
    strncpy(str, _raw.c_str(), 100);
    
    ptr = xstrtok(str, ",");
    while (ptr != NULL) {
        switch (index++) {
            case 0:     // Type
            case 10:    // Above sea units
            case 12:    // Geo ID height unit
            case 15:    // Checksum
                break;
            case 1:     // Time
                sscanf(ptr, "%2f%2f%f", &_time[0], &_time[1], &_time[2]);
                break;
            case 2:     // Lat. degrees
                lat_deg = strtof(ptr, NULL);
                break;
            case 3:     // Lat. direction
                lat_dir = *ptr;
                break;
            case 4:     // Lon. degrees
                lon_deg = strtof(ptr, NULL);
                break;
            case 5:     // Lon. direction
                lon_dir = *ptr;
                break;
            case 6:     // Quality
                _qual = (unsigned short) strtoul(ptr, NULL, 0);
                break;
            case 7:     // Number of tracking satellites
                _num_tracking = (unsigned short) strtoul(ptr, NULL, 0);
                break;
            case 8:     // Dilution of precision
                _dilution = strtof(ptr, NULL);
                break;
            case 9:     // Height above sea-level
                _above_sea = strtof(ptr, NULL);
                break;
            case 11:    // Height of geo ID
                _geo_id_height = strtof(ptr, NULL);
                break;
            case 13:    // seconds since DGPS update
                _dgps_age = (unsigned int) strtoul(ptr, NULL, 0);
                break;
            case 14:    // DGPS station
                _dgps_id = (unsigned int) strtoul(ptr, NULL, 0);
                break;
            default:    // Only here in error
                std::cerr << "Could not parse: '" << _raw << "'" << std::endl;
                assert(0);
//                throw out_of_range("Could not parse");
                break;
        }
        ptr = xstrtok(NULL, ",");
    }
    
    _lat = degToDec(lat_deg, lat_dir);
    _lon = degToDec(lon_deg, lon_dir);
}

//NmeaGga::NmeaGga(const NmeaGga& orig) {
//}

NmeaGga::~NmeaGga() {
}

