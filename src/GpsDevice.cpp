/* 
 * File:   GpsDevice.cpp
 * Author: ericfoss
 * 
 * Created on December 25, 2014, 5:23 PM
 */

#include "GpsDevice.h"

#include <cassert>
#include <iostream>

#include "utilities.h"

void *read(void *arg) {
    GpsDevice *dev = (GpsDevice *)arg;
    
    while(dev->isRunning() && dev->good()) {
        std::string line = dev->getLine();
//        std::cout << line << std::endl;
        if (isMsgValid(line)) {
            NmeaBase base(line);
            if (base.getType().compare("GPGGA") == 0) {
                dev->setGga(line);
                NmeaGga *gga = dev->getGga();
                std::cout << "New GGA lat(" << gga->getLatitude() << ") lon(" << gga->getLongitude() << ")" << std::endl;
            } else if (base.getType().compare("GPGSA") == 0) {
                dev->setGsa(line);
                NmeaGsa *gsa = dev->getGsa();
                std::cout << "New GSA dilution(" << gsa->getDilution() << ")" << std::endl;
            } else if (base.getType().compare("GPRMC") == 0) {
                dev->setRmc(line);
                NmeaRmc *rmc = dev->getRmc();
                std::cout << "New RMC lat(" << rmc->getLatitude() << ") lon(" << rmc->getLongitude() << ")" << std::endl;
            } else if (base.getType().compare("GPVTG") == 0) {
                dev->setVtg(line);
                NmeaVtg *vtg = dev->getVtg();
                std::cout << "New Vtg KPH(" << vtg->getKmph() << ") angle(" << vtg->getTrueAng() << ")" << std::endl;
            } else if (base.getType().compare("GPGSV") == 0) {
                std::cout << "Tossing GSV message" << std::endl;
            } else {
                std::cerr << "Unknown message type: " << line << std::endl;
                assert(0);
                throw std::out_of_range("Unknown message type");
            }
        }
    }
}

//GpsDevice::GpsDevice(fstream device): _device(device) {
//    _path = "";
//    if(!_device.is_open()) {
//        throw logic_error("GPS device is not open");
//    }
//}

string GpsDevice::getLine() {
    std::string line;
    
    while (_device.good() && _device.peek() != '$') {
        _device.get();
    }
    
    while(_device.good()) {
        line.push_back(_device.get());
        if (line.length() > 2 &&
            line.at(line.length()-3) == '*') {
            break;
        }
    }
    return line;
}

GpsDevice::GpsDevice(std::string path): _device(path.c_str(), std::fstream::in | std::fstream::binary) {
    _running = false;
    _path = path;
    if(!_device.is_open()) {
        throw std::logic_error("Could not open GPS device");
    }
}

GpsDevice::~GpsDevice() {
    _device.close();
}

void GpsDevice::run() {
   /* Initialize and set thread detached attribute */
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
    _running = true;
    _reader = pthread_create(&_reader, &attr, read, this);
    
   pthread_attr_destroy(&attr);
}

int GpsDevice::stop() {
    int rc = -1;
    void *status;
    
    _running = false;
    rc = pthread_join(_reader, &status);
    
    return rc;
}
