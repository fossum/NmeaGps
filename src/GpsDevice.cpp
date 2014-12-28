/* 
 * File:   GpsDevice.cpp
 * Author: ericfoss
 * 
 * Created on December 25, 2014, 5:23 PM
 */

#include "GpsDevice.h"

#include <cassert>
#include <iostream>

#include "conversions.h"
#include "msg_classes.h"

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
                cout << "New GGA lat(" << gga->getLatitude() << ") lon(" << gga->getLongitude() << ")" << endl;
            } else if (base.getType().compare("GPGSA") == 0) {
                dev->setGsa(line);
                NmeaGsa *gsa = dev->getGsa();
                cout << "New GSA dilution(" << gsa->getDilution() << ")" << endl;
            } else if (base.getType().compare("GPRMC") == 0) {
                dev->setRmc(line);
                NmeaRmc *rmc = dev->getRmc();
                cout << "New RMC lat(" << rmc->getLatitude() << ") lon(" << rmc->getLongitude() << ")" << endl;
            } else if (base.getType().compare("GPVTG") == 0) {
                dev->setVtg(line);
                NmeaVtg *vtg = dev->getVtg();
                cout << "New Vtg KPH(" << vtg->getKmph() << ") angle(" << vtg->getTrueAng() << ")" << endl;
            } else if (base.getType().compare("GPGSV") == 0) {
                cout << "Tossing GSV message" << endl;
            } else {
                cerr << "Unknown message type: " << line << endl;
                assert(0);
                throw out_of_range("Unknown message type");
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

GpsDevice::GpsDevice(std::string path): _device(path.c_str(), fstream::in | fstream::binary) {
    _running = false;
    _path = path;
    if(!_device.is_open()) {
        throw logic_error("Could not open GPS device");
    }
}

GpsDevice::~GpsDevice() {
    _device.close();
}

void GpsDevice::run() {
    _running = true;
    _reader = pthread_create(&_reader, NULL, read, this);
}

void GpsDevice::stop() {
    _running = false;
    pthread_join(_reader, NULL);
}
