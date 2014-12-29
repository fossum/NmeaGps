/* 
 * File:   NmeaRmc.h
 * Author: ericfoss
 *
 * Created on December 28, 2014, 5:11 PM
 */

#ifndef NMEARMC_H
#define	NMEARMC_H

#include "messages/NmeaBase.h"

class NmeaRmc: public NmeaBase {
public:
    NmeaRmc();
    NmeaRmc(string raw);
//    NmeaRmc(const NmeaRmc& orig);
    virtual ~NmeaRmc();
    
    // Getters
    bool getState() const { return(_active); }
    float getLatitude() const { return(_lat); }
    float getLongitude() const { return(_lon); }
    float getSpeed() const { return(_speed); }
    float getAngle() const { return(_angle); }
    float getMagneticVariation() const { return(_mag_variation); }
private:
    float _time[3];
    unsigned short _date[3];
    bool _active;
    char _mode;
    float _lat, _lon;
    float _speed, _angle;
    float _mag_variation;
};

#endif	/* NMEARMC_H */

