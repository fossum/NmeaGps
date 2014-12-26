/* 
 * File:   msg_classes.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 10:49 AM
 */

#include "msg_classes.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "conversions.h"

char *xstrtok(char *line, char *delims);

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

NmeaRmc::NmeaRmc(string raw): NmeaBase(raw) {
    char active = '\0', lat_dir, lon_dir, mag_dir;
    float lat, lon;
    
    sscanf(_raw.c_str(),
           "$GPRMC,%2hu%2hu%2hu,%c,%f,%c,%f,%c,%f,%f,%2hu%2hu%2hu,%f,%c",
           &_time[0], &_time[1], &_time[2],
           &active,
           &lat, &lat_dir,
           &lon, &lon_dir,
           &_speed, &_angle,
           &_date[0], &_date[1], &_date[2],
           &_mag_variation, &mag_dir);
    
    // Calc active message
    switch(active) {
        case 'A':
            _active = true;
            break;
        case 'V':
            _active = false;
            break;
        default:
            char str[100];
            sprintf(str, "Message active char out of range: '%c'", active);
            throw out_of_range(str);
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
            char str[100];
            sprintf(str, "Magnetic variation out of range: '%c'", mag_dir);
            throw out_of_range(str);
    }
}

NmeaVtg::NmeaVtg(string raw): NmeaBase(raw) {
    if ( 4 != sscanf(_raw.c_str(),
                     "$GPVTG,%f,T,%f,M,%f,N,%f,K",
                     &_true_track, &_mag_track, &_knots, &_kmph)) {
        throw "Could not parse VTG message";
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
