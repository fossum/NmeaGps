/* 
 * File:   NmeaVtg.h
 * Author: ericfoss
 *
 * Created on December 28, 2014, 5:08 PM
 */

#ifndef NMEAVTG_H
#define	NMEAVTG_H

#include "messages/NmeaBase.h"

class NmeaVtg: public NmeaBase {
public:
    NmeaVtg();
    NmeaVtg(string raw);
//    NmeaVtg(const NmeaVtg& orig);
    virtual ~NmeaVtg();
    
    // Getters
    float getTrueAng() const { return _true_track; }
    float getMagneticAng() const { return _mag_track; }
    float getKnots() const { return _knots; }
    float getKmph() const { return _kmph; }
private:
    float _true_track, _mag_track;
    float _knots, _kmph;
};

#endif	/* NMEAVTG_H */

