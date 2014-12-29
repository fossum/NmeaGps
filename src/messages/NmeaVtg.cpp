/* 
 * File:   NmeaVtg.cpp
 * Author: ericfoss
 * 
 * Created on December 28, 2014, 5:08 PM
 */

#include "messages/NmeaVtg.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utilities.h"

NmeaVtg::NmeaVtg() {
    _true_track = _mag_track = 0;
    _knots = _kmph = 0;
}

NmeaVtg::NmeaVtg(string raw): NmeaBase(raw) {
    char message[255], *ptr;
    int index = 0;
    
    strncpy(message, _raw.c_str(), 255);
    
    ptr = xstrtok(message, ",");
    while (ptr != NULL) {
        switch (index++) {
            case 0:     // Message type
            case 2:     // 
            case 4:     //
            case 6:     // Knots units
            case 8:     // KPH units
            case 9:     // Checksum
                break;
            case 1:
                _true_track = strtof(ptr, NULL);
                break;
            case 3:
                _mag_track = strtof(ptr, NULL);
                break;
            case 5:
                _knots = strtof(ptr, NULL);
                break;
            case 7:
                _kmph = strtof(ptr, NULL);
                break;
            default:
                std::cerr << "Unable to parse '" << _raw << "'" << std::endl;
                assert(0);
                break;
        }
        ptr = xstrtok(NULL, ",");
    }
}

//NmeaVtg::NmeaVtg(const NmeaVtg& orig) {
//}

NmeaVtg::~NmeaVtg() {
}

