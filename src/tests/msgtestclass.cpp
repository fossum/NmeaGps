/*
 * File:   newtestclass.cpp
 * Author: ericfoss
 *
 * Created on Dec 17, 2014, 6:53:45 PM
 */

#include "msgtestclass.h"

#include "msg_classes.h"

#include <string>

using namespace std;

#define DEC_ACCURACY 0.000001

CPPUNIT_TEST_SUITE_REGISTRATION(msgtestclass);

msgtestclass::msgtestclass() {
}

msgtestclass::~msgtestclass() {
}

void msgtestclass::setUp() {
}

void msgtestclass::tearDown() {
}

//NmeaBase::NmeaBase(std::string raw, float epoch);

void msgtestclass::baseGoodConstructor() {
    string good_msg = "$GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,*28";
    string type = "GPRMC";
    NmeaBase nmeaBase(good_msg);
    
    CPPUNIT_ASSERT_EQUAL(type, nmeaBase.getType());
    CPPUNIT_ASSERT_EQUAL(good_msg, nmeaBase.getRaw());
    CPPUNIT_ASSERT_EQUAL((float)0, nmeaBase.getEpoch());
}

void msgtestclass::baseBadConstructor() {
    string bad_msg = "$GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,*27";
    bool asserted = false;
    try {
        NmeaBase nmeaBase(bad_msg);
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
}

void msgtestclass::ggaGoodConstructor() {
    string good_msg = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    string type = "GPGGA";
    NmeaGga nmeaGga(good_msg);
    
    // Inheritance
    CPPUNIT_ASSERT_EQUAL(type, nmeaGga.getType());
    CPPUNIT_ASSERT_EQUAL(good_msg, nmeaGga.getRaw());
    CPPUNIT_ASSERT_EQUAL((float)0, nmeaGga.getEpoch());
    
    // GGA message
    float lat = 48.1173;
    CPPUNIT_ASSERT(lat - nmeaGga.getLatitude() < DEC_ACCURACY);
    float lon = 11.516666;
    CPPUNIT_ASSERT(lon - nmeaGga.getLatitude() < DEC_ACCURACY);
    CPPUNIT_ASSERT_EQUAL((unsigned short)1, nmeaGga.getQuality());
    CPPUNIT_ASSERT_EQUAL((unsigned short)8, nmeaGga.getTracking());
    CPPUNIT_ASSERT_EQUAL((float)0.9, nmeaGga.getDilution());
    CPPUNIT_ASSERT_EQUAL((float)545.4, nmeaGga.getAboveSea());
}

void msgtestclass::ggaBadConstructor() {
    string bad_msg = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*00";
    
    // Bad chk-sum case
    bool asserted = false;
    try {
        NmeaGga nmeaGga(bad_msg);
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
    
    // Empty string case
    asserted = false;
    try {
        NmeaGga nmeaGga("");
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
}
