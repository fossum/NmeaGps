/* 
 * File:   msg_classes.h
 * Author: ericfoss
 *
 * Created on December 17, 2014, 10:49 AM
 */

#ifndef MSG_CLASSES_H
#define	MSG_CLASSES_H

#include <cstdio>
#include <iostream>
#include <string>

#include "convertions.h"

using namespace std;

class NmeaBase {
public:
    NmeaBase(string raw, float epoch);
    NmeaBase(const NmeaBase& orig);
    virtual ~NmeaBase() {}
    
    // Getters
    string getType() const { return _type; }
    string getRaw() const { return _raw; }
    float getEpoch() const { return _epoch; }
    
    // Setters
//    void setType(std::string t) const { _type = t; }
//    void setRaw(std::string r) const { _raw = r; }
//    void setEpoch(float e) const { _epoch = e; }
protected:
    string _raw;
    string _type;
    float _epoch;
};

class NmeaGga: public NmeaBase {
public:
    NmeaGga(string raw);
    virtual ~NmeaGga() {}
    
    // Getters
    unsigned short getQuality() const { return _qual; }
private:
    short _time[3];
    float _lat, _lon;
    unsigned short _qual;
    unsigned short _num_tracking;
    float _dilution, _above_sea;
};

#endif	/* MSG_CLASSES_H */
