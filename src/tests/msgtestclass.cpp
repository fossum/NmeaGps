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

void msgtestclass::gsaGoodConstructor() {
    string good_msg = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    string type = "GPGSA";
    NmeaGsa nmeaGsa(good_msg);
    
    // Inheritance
    CPPUNIT_ASSERT_EQUAL(type, nmeaGsa.getType());
    CPPUNIT_ASSERT_EQUAL(good_msg, nmeaGsa.getRaw());
    CPPUNIT_ASSERT_EQUAL((float)0, nmeaGsa.getEpoch());
    
    // GSA message
    CPPUNIT_ASSERT_EQUAL('A', nmeaGsa.getSelectionMode());
    CPPUNIT_ASSERT_EQUAL((unsigned short)4, nmeaGsa.getPrn(1));
    CPPUNIT_ASSERT_EQUAL((unsigned short)24, nmeaGsa.getPrn(5));
    CPPUNIT_ASSERT_EQUAL((unsigned short)0, nmeaGsa.getPrn(6));
    CPPUNIT_ASSERT_EQUAL((unsigned short)0, nmeaGsa.getPrn(12));
    CPPUNIT_ASSERT_EQUAL((unsigned short)5, nmeaGsa.getPrnCount());
    CPPUNIT_ASSERT_EQUAL((float)2.5, nmeaGsa.getDilution());
    CPPUNIT_ASSERT_EQUAL((float)1.3, nmeaGsa.getHorzDilution());
    CPPUNIT_ASSERT_EQUAL((float)2.1, nmeaGsa.getVertDilution());
}

void msgtestclass::gsaBadConstructor() {
    string bad_msg = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*38";
    
    // Bad chk-sum case
    bool asserted = false;
    try {
        NmeaGsa nmeaGsa(bad_msg);
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
    
    // Empty string case
    asserted = false;
    try {
        NmeaGsa nmeaGsa("");
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
}
    
void msgtestclass::rmcGoodConstructor() {
    string msg1 = "$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62";
    string msg2 = "$GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68";

    NmeaRmc nmea1(msg1);
    CPPUNIT_ASSERT_EQUAL(true, nmea1.getState());
    CPPUNIT_ASSERT_EQUAL((float)-37.860833, nmea1.getLatitude());
    CPPUNIT_ASSERT_EQUAL((float)145.122666, nmea1.getLongitude());
    CPPUNIT_ASSERT_EQUAL((float)0, nmea1.getSpeed());
    CPPUNIT_ASSERT_EQUAL((float)360.0, nmea1.getAngle());
    CPPUNIT_ASSERT_EQUAL((float)11.3, nmea1.getMagneticVariation());
    CPPUNIT_ASSERT_EQUAL((float)905674716, nmea1.getEpoch());

    NmeaRmc nmea2(msg1);
    CPPUNIT_ASSERT_EQUAL(true, nmea2.getState());
    CPPUNIT_ASSERT_EQUAL((float)49.274166, nmea2.getLatitude());
    CPPUNIT_ASSERT_EQUAL((float)-123.185333, nmea2.getLongitude());
    CPPUNIT_ASSERT_EQUAL((float)0.5, nmea2.getSpeed());
    CPPUNIT_ASSERT_EQUAL((float)54.7, nmea2.getAngle());
    CPPUNIT_ASSERT_EQUAL((float)20.3, nmea2.getMagneticVariation());
    CPPUNIT_ASSERT_EQUAL((float)785285686, nmea2.getEpoch());
}

void msgtestclass::rmcBadConstructor() {
    string bad_msg = "$GPRMC,01836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62";
    
    // Bad chk-sum case
    bool asserted = false;
    try {
        NmeaRmc nmea1(bad_msg);
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
    
    // Empty string case
    asserted = false;
    try {
        NmeaRmc nmea2("");
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
}
    
void msgtestclass::vtgGoodConstructor() {
    string msg1 = "$GPVTG,360.0,T,348.7,M,000.0,N,000.0,K*43";

    NmeaVtg nmea1(msg1);
    CPPUNIT_ASSERT_EQUAL((float)360, nmea1.getTrueAng());
    CPPUNIT_ASSERT_EQUAL((float)348.7, nmea1.getMagneticAng());
    CPPUNIT_ASSERT_EQUAL((float)0, nmea1.getKnots());
    CPPUNIT_ASSERT_EQUAL((float)0, nmea1.getKmph());
}

void msgtestclass::vtgBadConstructor() {
    string bad_msg = "$GPVTG,360.0,T,348.7,M,000.0,N,000 0,K*43";
    
    // Bad chk-sum case
    bool asserted = false;
    try {
        NmeaVtg nmea1(bad_msg);
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
    
    // Empty string case
    asserted = false;
    try {
        NmeaVtg nmea2("");
    } catch (...) {
        asserted = true;
    }
    CPPUNIT_ASSERT(asserted);
}

