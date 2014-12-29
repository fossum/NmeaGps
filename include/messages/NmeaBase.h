/* 
 * File:   NmeaBase.h
 * Author: ericfoss
 *
 * Created on December 28, 2014, 3:36 PM
 */

#ifndef NMEABASE_H
#define	NMEABASE_H

#include <string>

typedef std::string string;

class NmeaBase {
public:
    NmeaBase();
    NmeaBase(string raw);
    NmeaBase(const NmeaBase& orig);
    virtual ~NmeaBase();
    
    // Getters
    string getType() const { return _type; }
    string getRaw() const { return _raw; }
    float getEpoch() const { return _epoch; }
protected:
    string _raw;
    string _type;
    float _epoch;
};

#endif	/* NMEABASE_H */

