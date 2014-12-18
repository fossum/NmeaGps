/* 
 * File:   convertions.cpp
 * Author: ericfoss
 * 
 * Created on December 17, 2014, 11:26 AM
 */

#include "convertions.h"

float degToDec(float degree, char dir) {
    int min = (int)degree % 100;
    float decimal = degree / 100;
    decimal += min / 60;
    
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

short calcChecksum(std::string str) {
    
}