/*
 * File:   conversionstestclass.cpp
 * Author: ericfoss
 *
 * Created on Dec 17, 2014, 7:35:26 PM
 */

#include "conversionstestclass.h"

#include <cmath>

#include "utilities.h"

using namespace std;

#define DEC_ACCURACY 0.000001

CPPUNIT_TEST_SUITE_REGISTRATION(conversionstestclass);

conversionstestclass::conversionstestclass() {
}

conversionstestclass::~conversionstestclass() {
}

void conversionstestclass::setUp() {
}

void conversionstestclass::tearDown() {
}

void conversionstestclass::testDegToDecN() {
    float expect = 33.335998;
    float offset = expect - degToDec(3320.16, 'N');
    CPPUNIT_ASSERT(abs(offset) <= DEC_ACCURACY);
}

void conversionstestclass::testDegToDecS() {
    float expect = -33.335998;
    float offset = expect - degToDec(3320.16, 'S');
    CPPUNIT_ASSERT(abs(offset) <= DEC_ACCURACY);
}

void conversionstestclass::testDegToDecE() {
    float expect = 33.335998;
    float offset = expect - degToDec(3320.16, 'E');
    CPPUNIT_ASSERT(abs(offset) <= DEC_ACCURACY);
}

void conversionstestclass::testDegToDecW() {
    float expect = -33.335998;
    float offset = expect - degToDec(3320.16, 'W');
    CPPUNIT_ASSERT(abs(offset) <= DEC_ACCURACY);
}

void conversionstestclass::testCalcChecksum() {
    string msg = "GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,";
    char expect = 0x28;
    CPPUNIT_ASSERT_EQUAL(expect, calcChecksum(msg));
}

void conversionstestclass::testIsMsgValid() {
    string msg = "$GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,*28";
    CPPUNIT_ASSERT(isMsgValid(msg));
}
