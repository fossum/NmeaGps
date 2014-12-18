/*
 * File:   newtestclass.h
 * Author: ericfoss
 *
 * Created on Dec 17, 2014, 6:53:45 PM
 */

#ifndef MSGTESTCLASS_H
#define	MSGTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class msgtestclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(msgtestclass);

    CPPUNIT_TEST(baseGoodConstructor);
    CPPUNIT_TEST(baseBadConstructor);
    CPPUNIT_TEST(ggaGoodConstructor);
    CPPUNIT_TEST(ggaBadConstructor);

    CPPUNIT_TEST_SUITE_END();

public:
    msgtestclass();
    virtual ~msgtestclass();
    void setUp();
    void tearDown();

private:
    void baseGoodConstructor();
    void baseBadConstructor();
    
    void ggaGoodConstructor();
    void ggaBadConstructor();
};

#endif	/* MSGTESTCLASS_H */

