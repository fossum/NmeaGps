/* 
 * File:   GpsDevice.h
 * Author: ericfoss
 *
 * Created on December 25, 2014, 5:23 PM
 */

#ifndef GPSDEVICE_H
#define	GPSDEVICE_H

#include <fstream>
#include <pthread.h>

#include "messages/NmeaGga.h"
#include "messages/NmeaGsa.h"
#include "messages/NmeaRmc.h"
#include "messages/NmeaVtg.h"

class GpsDevice {
public:
    // Constructors
//    GpsDevice(fstream device);
    GpsDevice(std::string dev_path);
    virtual ~GpsDevice();
    
    // Methods
    void run();
    int stop();
    std::string getLine();
    bool isRunning() const { return _running; }
    bool good() const { return _device.good(); }
    
    // Messages
    void setGga(std::string msg) { _gga = NmeaGga(msg); }
    NmeaGga *getGga() { return &_gga; }
    void setGsa(std::string msg) { _gsa = NmeaGsa(msg); }
    NmeaGsa *getGsa() { return &_gsa; }
    void setRmc(std::string msg) { _rmc = NmeaRmc(msg); }
    NmeaRmc *getRmc() { return &_rmc; }
    void setVtg(std::string msg) { _vtg = NmeaVtg(msg); }
    NmeaVtg *getVtg() { return &_vtg; }
private:
    std::string _path;
    pthread_t _reader;
    std::ifstream _device;
    bool _running;
    
    NmeaGga _gga;
    NmeaGsa _gsa;
    NmeaRmc _rmc;
    NmeaVtg _vtg;
};

#endif	/* GPSDEVICE_H */

