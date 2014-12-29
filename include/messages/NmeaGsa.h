/* 
 * File:   NmeaGsa.h
 * Author: ericfoss
 *
 * Created on December 28, 2014, 4:45 PM
 */

#ifndef NMEAGSA_H
#define	NMEAGSA_H

#include "messages/NmeaBase.h"

class NmeaGsa: public NmeaBase {
public:
    NmeaGsa();
    NmeaGsa(string raw);
//    NmeaGsa(const NmeaGsa& orig);s
    virtual ~NmeaGsa();
    
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

#endif	/* NMEAGSA_H */

