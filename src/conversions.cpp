/* 
 * File:   convertions.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 11:26 AM
 */

#include "conversions.h"

#include <cstdio>

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
    
    sscanf(msg.c_str(), "$%100[^*]*%hx", data, &exp_sum);
    
    return (calcChecksum(data) == exp_sum);
}