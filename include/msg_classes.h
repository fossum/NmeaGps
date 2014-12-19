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

class NmeaGsv: public NmeaBase {
public:
    NmeaGsv(string raw);
    virtual ~NmeaGsv() {}
    
    // Getters
private:
};

class NmeaVtg: public NmeaBase {
public:
    NmeaVtg(string raw);
    virtual ~NmeaVtg() {}
    
    // Getters
private:
};

class NmeaRmc: public NmeaBase {
public:
    NmeaRmc(string raw);
    virtual ~NmeaRmc() {}
    
    // Getters
private:
};

#endif	/* MSG_CLASSES_H */

