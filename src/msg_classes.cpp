/* 
 * File:   msg_classes.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 10:49 AM
 */

#include "msg_classes.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "conversions.h"

char *xstrtok(char *line, char *delims);

NmeaBase::NmeaBase() {
    _raw = "";
    _type = "";
    _epoch = 0;
}

NmeaBase::NmeaBase(string raw) {
    _raw = raw;
    char type[10];
    
    if (!isMsgValid(_raw)) {
        cerr << "Invalid NMEA message: '" << _raw << "'" << endl;
        assert(0);
        throw std::out_of_range("invalid NMEA");
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
    float lat_deg, lon_deg;
    char lat_dir, lon_dir;
    
    if (11 != sscanf(_raw.c_str(),
                     "$GPGGA,%2f%2f%f,%f,%c,%f,%c,%hu,%hu,%f,%f", 
                     &_time[0], &_time[1], &_time[2],
                     &lat_deg, &lat_dir, &lon_deg, &lon_dir, 
                     &_qual, &_num_tracking, &_dilution, &_above_sea)) {
        cerr << "Could not parse: '" << _raw << "'" << endl;
        assert(0);
        throw out_of_range("Could not parse");
    }
    
    _lat = degToDec(lat_deg, lat_dir);
    _lon = degToDec(lon_deg, lon_dir);
}

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
    char prns[80], *tok, del[2] = {',', '\0'};
    int index = 0, itr = 0;
    
    sscanf(_raw.c_str(), "$GPGSA,%c,%hu,%[^*]*", &_selection, &_fix, prns);
    
    tok = xstrtok(prns, del);
    while (tok != NULL && itr < 12) {
        unsigned int tmp = atoi(tok);
        if (tmp > 0) {
            _prn[index++] = tmp;
        }
        itr++;
        tok = xstrtok(NULL, del);
    }
    _count = index;
    while(index < 12) {
        _prn[index++] = 0;
    }
    
    _dilution = strtof(tok, &tok);
    _horz_dil = strtof(tok+1, &tok);    // Plus one to move past delim
    _vert_dil = strtof(tok+1, &tok);
}

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
    char active = '\0', lat_dir, lon_dir, mag_dir;
    float lat, lon;
    
    if (13 > sscanf(_raw.c_str(),
                    "$GPRMC,%2f%2f%f,%c,%f,%c,%f,%c,%f,%f,%2hu%2hu%2hu,%f,%c",
                    &_time[0], &_time[1], &_time[2],
                    &active,
                    &lat, &lat_dir,
                    &lon, &lon_dir,
                    &_speed, &_angle,
                    &_date[0], &_date[1], &_date[2],
                    &_mag_variation, &mag_dir)) {
        cerr << "Could not parse: '" << _raw << "'" << endl;
        assert(0);
        throw out_of_range("Could not parse");
    }
    
    // Calc active message
    switch(active) {
        case 'A':
            _active = true;
            break;
        case 'V':
            _active = false;
            break;
        default:
            cerr << "Message active char out of range: '" << active << "'" << endl;
            assert(0);
            throw out_of_range("invalid active state");
    }
    
    // Calc epoch
    _epoch = dateTimeToEpoch(_date, _time);
    
    // Calc lat/lon
    _lat = degToDec(lat, lat_dir);
    _lon = degToDec(lon, lon_dir);
    
    // Calc mag. var.
    switch(mag_dir) {
        case 'E':
            break;
        case 'W':
            _mag_variation *= -1;
            break;
        default:
//            cerr << "Magnetic variation out of range: '" << mag_dir << "'" << endl;
//            assert(0);
//            throw out_of_range("invalid magnetic direction");
            _mag_variation = 0;
    }
}

NmeaVtg::NmeaVtg() {
    _true_track = _mag_track = 0;
    _knots = _kmph = 0;
}

NmeaVtg::NmeaVtg(string raw): NmeaBase(raw) {
//    if ( 4 != sscanf(_raw.c_str(),
//                     "$GPVTG,%f,T,%f,M,%f,N,%f,K",
//                     &_true_track, &_mag_track, &_knots, &_kmph)) {
//        cerr << "Could not parse: '" << _raw << "'" << endl;
//        assert(0);
//        throw out_of_range("Could not parse VTG message");
//    }
    char message[255], *ptr;
    int index = 0;
    strncpy(message, _raw.c_str(), 255);
    
    ptr = xstrtok(message, ",");
    while (ptr != NULL) {
        switch (index++) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
            case 9:
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
                cerr << "Unable to parse '" << _raw << "'" << endl;
                assert(0);
                break;
        }
        ptr = xstrtok(NULL, ",");
    }
}

/*
 * strtok version that handles null fields
 */
char *xstrtok(char *line, char *delims) {
    static char *saveline = NULL;
    char *p;
    int n;

    if(line != NULL)
        saveline = line;

    /*
    *see if we have reached the end of the line 
    */
    if(saveline == NULL || *saveline == '\0') 
        return(NULL);
    /*
    *return the number of characters that aren't delims 
    */
    n = strcspn(saveline, delims);
    p = saveline; /*save start of this token*/

    saveline += n; /*bump past the delim*/

    if(*saveline != '\0') /*trash the delim if necessary*/
        *saveline++ = '\0';

    return(p);
}
