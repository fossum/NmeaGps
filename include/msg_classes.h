/* 
 * File:   msg_classes.h
 * Author: ericfoss
 *
 * Created on December 17, 2014, 10:49 AM
 */

#ifndef MSG_CLASSES_H
#define	MSG_CLASSES_H

using namespace std;

#include <string>

class NmeaBase {
public:
    NmeaBase(string raw);
    NmeaBase(const NmeaBase& orig);
    virtual ~NmeaBase() {}
    
    // Getters
    string getType() const { return _type; }
    string getRaw() const { return _raw; }
    float getEpoch() const { return _epoch; }
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
    float getLatitude() const { return _lat; }
    float getLongitude() const { return _lon; }
    unsigned short getQuality() const { return _qual; }
    unsigned short getTracking() const { return _num_tracking; }
    float getDilution() const { return _dilution; }
    float getAboveSea() const { return _above_sea; }
private:
    short _time[3];
    float _lat, _lon;
    unsigned short _qual, _num_tracking;
    float _dilution, _above_sea;
};

class NmeaGsa: public NmeaBase {
public:
    NmeaGsa(string raw);
    virtual ~NmeaGsa() {}
    
    // Getters
    char getSelectionMode() const { return _selection; };
    unsigned short getPrn(unsigned int index) { return _prn[index-1]; }
    unsigned short getPrnCount() { return _count; }
    float getDilution() const { return _dilution; }
    float getHorzDilution() const { return _horz_dil; }
    float getVertDilution() const { return _vert_dil; }
private:
    char _selection;
    unsigned short _prn[12], _fix, _count;
    float _dilution, _horz_dil, _vert_dil;
};

class NmeaRmc: public NmeaBase {
public:
    NmeaRmc(string raw);
    virtual ~NmeaRmc() {}
    
    // Getters
    bool getState() const { return(_active); }
    float getLatitude() const { return(_lat); }
    float getLongitude() const { return(_lon); }
    float getSpeed() const { return(_speed); }
    float getAngle() const { return(_angle); }
    float getMagneticVariation() const { return(_mag_variation); }
private:
    unsigned short _time[3], _date[3];
    bool _active;
    float _lat, _lon;
    float _speed, _angle;
    float _mag_variation;
};

class NmeaVtg: public NmeaBase {
public:
    NmeaVtg(string raw);
    virtual ~NmeaVtg() {}
    
    // Getters
    float getTrueAng() const { return _true_track; }
    float getMagneticAng() const { return _mag_track; }
    float getKnots() const { return _knots; }
    float getKmph() const { return _kmph; }
private:
    float _true_track, _mag_track;
    float _knots, _kmph;
};

#endif	/* MSG_CLASSES_H */

