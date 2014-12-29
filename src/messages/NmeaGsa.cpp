/* 
 * File:   NmeaGsa.cpp
 * Author: ericfoss
 * 
 * Created on December 28, 2014, 4:45 PM
 */

#include "messages/NmeaGsa.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "utilities.h"

NmeaGsa::NmeaGsa() {
    int index = 0;
    
    _count = index;
    while(index < 12) {
        _prn[index++] = 0;
    }
    
    _selection = '\0';
    _fix = 0;
    _dilution = 0;
    _horz_dil = 0;
    _vert_dil = 0;
}

NmeaGsa::NmeaGsa(string raw): NmeaBase(raw) {
    char str[100], *ptr;
    int index = 0;
    unsigned short prn;
    
    _count = 0;
    strncpy(str, _raw.c_str(), 100);
    
    ptr = xstrtok(str, ",");
    while(ptr != 0) {
        switch(index++) {
            case 0:     // Type
            case 18:    // Checksum
                break;
            case 1:     // Selection type
                _selection = *ptr;
                break;
            case 2:     // Fix type
                _fix = (unsigned short) strtoul(ptr, NULL, 0);
                break;
            case 3:     // PRN 1
            case 4:     // PRN 2
            case 5:     // PRN 3
            case 6:     // PRN 4
            case 7:     // PRN 5
            case 8:     // PRN 6
            case 9:     // PRN 7
            case 10:    // PRN 8
            case 11:    // PRN 9
            case 12:    // PRN 10
            case 13:    // PRN 11
            case 14:    // PRN 12
                prn = (unsigned short) strtoul(ptr, NULL, 0);
                if (prn > 0) {
                    _prn[_count++] = prn;
                }
                break;
            case 15:    // Dilution
                _dilution = strtof(ptr, NULL);
                break;
            case 16:    // Horizonal dilution
                _horz_dil = strtof(ptr, NULL);
                break;
            case 17:    // Vertical dilution
                _vert_dil = strtof(ptr, NULL);
                break;
            default:    // Here in error
                std::cerr << "Could not parse: '" << _raw << "'" << std::endl;
                assert(0);
//                throw out_of_range("Could not parse");
        }
        ptr = xstrtok(NULL, ",");
    }
    
    // Zero out list
    for (int i = _count; i < 12; i++) {
        _prn[i] = 0;
    }
}

//NmeaGsa::NmeaGsa(const NmeaGsa& orig) {
//}

NmeaGsa::~NmeaGsa() {
}
