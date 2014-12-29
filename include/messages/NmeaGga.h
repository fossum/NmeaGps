/* 
 * File:   NmeaGga.h
 * Author: ericfoss
 *
 * Created on December 28, 2014, 4:02 PM
 */

#ifndef NMEAGGA_H
#define	NMEAGGA_H

#include <string>
#include "messages/NmeaBase.h"

typedef std::string string;

class NmeaGga: public NmeaBase {
public:
    NmeaGga();
    NmeaGga(string raw);
//    NmeaGga(const NmeaGga& orig);
    virtual ~NmeaGga();
    
    // Getters
    float getLatitude() const { return _lat; }
    float getLongitude() const { return _lon; }
    unsigned short getQuality() const { return _qual; }
    unsigned short getTracking() const { return _num_tracking; }
    float getDilution() const { return _dilution; }
    float getAboveSea() const { return _above_sea; }
private:
    float _time[3];
    float _lat, _lon;
    unsigned short _qual, _num_tracking;
    float _dilution, _above_sea, _geo_id_height;
    unsigned int _dgps_id, _dgps_age;
};

#endif	/* NMEAGGA_H */

