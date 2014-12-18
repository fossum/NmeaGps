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
    try {
        NmeaBase nmeaBase(good_msg);
    } catch (...) {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(true);
}

void msgtestclass::baseBadConstructor() {
    string bad_msg = "$GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,*27";
//    NmeaBase nmeaBase(bad_msg);
    try {
        NmeaBase nmeaBase(bad_msg);
    } catch (...) {
        CPPUNIT_ASSERT(true);
    }
    CPPUNIT_ASSERT(false);
}

void msgtestclass::ggaGoodConstructor() {
    string good_msg = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    try {
        NmeaBase nmeaBase(good_msg);
    } catch (...) {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(true);
}

void msgtestclass::ggaBadConstructor() {
    string bad_msg = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*00";
    try {
        NmeaBase nmeaBase(bad_msg);
    } catch (...) {
        CPPUNIT_ASSERT(true);
    }
    CPPUNIT_ASSERT(false);
}
