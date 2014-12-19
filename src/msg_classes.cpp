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
    char prns[80], *tok;
    int index = 0, itr = 0;
    
    sscanf(_raw.c_str(), "$GPGSA,%c,%hu,%[^*]*", &_selection, &_fix, prns);
    
    tok = xstrtok(prns, ",");
    while (tok != NULL && itr < 12) {
        unsigned int tmp = atoi(tok);
        if (tmp > 0) {
            _prn[index++] = tmp;
        }
        itr++;
        tok = xstrtok(NULL, ",");
    }
    _count = index;
    while(index < 12) {
        _prn[index++] = 0;
    }
    
    _dilution = strtof(tok, &tok);
    _horz_dil = strtof(tok+1, &tok);    // Plus one to so around '\0' from strtok
    _vert_dil = strtof(tok, &tok);
}

NmeaGsv::NmeaGsv(string raw): NmeaBase(raw) {
    
}

NmeaVtg::NmeaVtg(string raw): NmeaBase(raw) {
    
}

NmeaRmc::NmeaRmc(string raw): NmeaBase(raw) {
    
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
