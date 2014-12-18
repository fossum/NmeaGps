/*
 * File:   conversionstestclass.h
 * Author: ericfoss
 *
 * Created on Dec 17, 2014, 7:35:25 PM
 */

#ifndef CONVERSIONSTESTCLASS_H
#define	CONVERSIONSTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class conversionstestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(conversionstestclass);

    CPPUNIT_TEST(testDegToDecN);
    CPPUNIT_TEST(testDegToDecS);
    CPPUNIT_TEST(testDegToDecE);
    CPPUNIT_TEST(testDegToDecW);
    CPPUNIT_TEST(testCalcChecksum);
    CPPUNIT_TEST(testIsMsgValid);

    CPPUNIT_TEST_SUITE_END();

public:
    conversionstestclass();
    virtual ~conversionstestclass();
    void setUp();
    void tearDown();

private:
    void testDegToDecN();
    void testDegToDecS();
    void testDegToDecE();
    void testDegToDecW();
    void testCalcChecksum();
    void testIsMsgValid();
};

#endif	/* CONVERSIONSTESTCLASS_H */

