/* 
 * File:   convertions.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 11:26 AM
 */

#include "conversions.h"

#include <cmath>
#include <cstdio>
#include <time.h>

float degToDec(float degree, char dir) {
    int deg = (int)degree / 100;
    float decimal = deg + ((degree - (deg * 100)) / 60);
    
    switch(dir) {
        case 'N':
        case 'E':
            break;
        case 'S':
        case 'W':
            decimal *= -1;
            break;
        default:
            throw std::out_of_range("Invalid compass direction");
    }
    
    return decimal;
}

char calcChecksum(std::string str) {
    char check = 0;
    
    // iterate over the string, XOR each byte with the total sum:
    for (int c = 0; c < str.length(); c++) {
        check = char(check ^ str.at(c));
    }
    
    // return the result
    return check;
}

bool isMsgValid(std::string msg) {
    char data[100];
    unsigned short exp_sum;
    
    if (2 == sscanf(msg.c_str(), "$%100[^*]*%hx", data, &exp_sum) &&
        calcChecksum(data) == exp_sum) {
        return true;
    }
    
    return false;
}

int dateTimeToEpoch(unsigned short date[], float time[]) {
    struct tm t = {0};
    
    t.tm_mday = date[0];
    t.tm_mon = date[1] - 1;
    if (date[2] > 70) {
        t.tm_year = date[2];
    } else {     // This is year-1900, so 112 = 2012
        t.tm_year = 100 + date[2];
    }
    t.tm_hour = (int)time[0];
    t.tm_min = (int)time[1];
    
    double seconds;
    float fractal = modf(time[2], &seconds);
    t.tm_sec = (int)seconds;
    float epoch = (float)timegm(&t);
    epoch += fractal;
    
    return epoch;
}
