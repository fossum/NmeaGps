/* 
 * File:   NmeaRmc.cpp
 * Author: ericfoss
 * 
 * Created on December 28, 2014, 5:11 PM
 */

#include "messages/NmeaRmc.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utilities.h"

NmeaRmc::NmeaRmc() {
    _time[0] = 0;
    _time[1] = 0;
    _time[2] = 0;
    _active = false;
    _speed = 0;
    _angle = 0;
    _date[0] = 0;
    _date[1] = 0;
    _date[2] = 0;
    _mag_variation = 0;
    _lat = 0;
    _lon = 0;
}

NmeaRmc::NmeaRmc(string raw): NmeaBase(raw) {
    char str[100], *ptr;
    int index = 0;
    float lat_deg, lon_deg;
    char lat_dir, lon_dir;
    
    strncpy(str, _raw.c_str(), 100);
    
    ptr = xstrtok(str, ",*");
    while (ptr != NULL) {
        switch(index++) {
            case 0:     // Message type
            case 12:    // Checksum
                break;
            case 1:     // Time
                sscanf(ptr, "%2f%2f%f", &_time[0], &_time[1], &_time[2]);
                break;
            case 2:     // Active state
                if(*ptr == 'A') {
                    _active = true;
                } else if (*ptr == 'V') {
                    _active = false;
                } else {
                    std::cerr << "Message active char out of range: '" << *ptr << "'" << std::endl;
                    assert(0);
                    throw std::out_of_range("invalid active state");
                }
                break;
            case 3:     // Lat. degree
                lat_deg = strtof(ptr, NULL);
                break;
            case 4:     // Lat. direction
                lat_dir = *ptr;
                break;
            case 5:     // Lon. degree
                lon_deg = strtof(ptr, NULL);
                break;
            case 6:     // Lon. direction
                lon_dir = *ptr;
                break;
            case 7:     // Speed
                _speed = strtof(ptr, NULL);
                break;
            case 8:     // Angle of movement
                _angle = strtof(ptr, NULL);
                break;
            case 9:     // Date
                sscanf(ptr, "%2hu%2hu%2hu", &_date[0], &_date[1], &_date[2]);
                break;
            case 10:    // Magnetic variation
                _mag_variation = strtof(ptr, NULL);
                break;
            case 11:    // Magnetic direction
                if(*ptr == 'W') {
                    _mag_variation *= -1;
                } else if (*ptr != 'E') {
//                    cerr << "Magnetic variation out of range: '" << mag_dir << "'" << endl;
//                    assert(0);
//                    throw out_of_range("invalid magnetic direction");
                    _mag_variation = 0;
                }
                break;
            case 13:
                _mode = *ptr;
                break;
            default:
                std::cerr << "Could not parse: '" << _raw << "'" << std::endl;
                assert(0);
                throw std::out_of_range("Could not parse");
        }
        ptr = xstrtok(NULL, ",*");
    }
    
    // Calc epoch
    _epoch = dateTimeToEpoch(_date, _time);
    
    // Calc lat/lon
    _lat = degToDec(lat_deg, lat_dir);
    _lon = degToDec(lon_deg, lon_dir);
}

//NmeaRmc::NmeaRmc(const NmeaRmc& orig) {
//}

NmeaRmc::~NmeaRmc() {
}

