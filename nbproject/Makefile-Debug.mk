#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1494353551/GpsDevice.o \
	${OBJECTDIR}/_ext/98585804/NmeaBase.o \
	${OBJECTDIR}/_ext/98585804/NmeaGga.o \
	${OBJECTDIR}/_ext/98585804/NmeaGsa.o \
	${OBJECTDIR}/_ext/98585804/NmeaRmc.o \
	${OBJECTDIR}/_ext/98585804/NmeaVtg.o \
	${OBJECTDIR}/src/utilities.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2

# C Compiler Flags
CFLAGS=`cppunit-config --cflags` 

# CC Compiler Flags
CCFLAGS=`cppunit-config --cflags` -pthread 
CXXFLAGS=`cppunit-config --cflags` -pthread 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/include `cppunit-config --libs` `cppunit-config --libs` -pthread  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f1

${TESTDIR}/TestFiles/f1: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1494353551/GpsDevice.o: /home/ericfoss/Documents/NmeaGps/src/GpsDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1494353551
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1494353551/GpsDevice.o /home/ericfoss/Documents/NmeaGps/src/GpsDevice.cpp

${OBJECTDIR}/_ext/98585804/NmeaBase.o: /home/ericfoss/Documents/NmeaGps/src/messages/NmeaBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaBase.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaBase.cpp

${OBJECTDIR}/_ext/98585804/NmeaGga.o: /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGga.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaGga.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGga.cpp

${OBJECTDIR}/_ext/98585804/NmeaGsa.o: /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaGsa.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGsa.cpp

${OBJECTDIR}/_ext/98585804/NmeaRmc.o: /home/ericfoss/Documents/NmeaGps/src/messages/NmeaRmc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaRmc.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaRmc.cpp

${OBJECTDIR}/_ext/98585804/NmeaVtg.o: /home/ericfoss/Documents/NmeaGps/src/messages/NmeaVtg.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaVtg.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaVtg.cpp

${OBJECTDIR}/src/utilities.o: src/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utilities.o src/utilities.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f3: ${TESTDIR}/src/tests/conversionsrunner.o ${TESTDIR}/src/tests/conversionstestclass.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/src/tests/msg_test.o ${TESTDIR}/src/tests/msgtestclass.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/src/tests/conversionsrunner.o: src/tests/conversionsrunner.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/tests/conversionsrunner.o src/tests/conversionsrunner.cpp


${TESTDIR}/src/tests/conversionstestclass.o: src/tests/conversionstestclass.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/tests/conversionstestclass.o src/tests/conversionstestclass.cpp


${TESTDIR}/src/tests/msg_test.o: src/tests/msg_test.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/tests/msg_test.o src/tests/msg_test.cpp


${TESTDIR}/src/tests/msgtestclass.o: src/tests/msgtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/src/tests/msgtestclass.o src/tests/msgtestclass.cpp


${OBJECTDIR}/_ext/1494353551/GpsDevice_nomain.o: ${OBJECTDIR}/_ext/1494353551/GpsDevice.o /home/ericfoss/Documents/NmeaGps/src/GpsDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1494353551
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1494353551/GpsDevice.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1494353551/GpsDevice_nomain.o /home/ericfoss/Documents/NmeaGps/src/GpsDevice.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1494353551/GpsDevice.o ${OBJECTDIR}/_ext/1494353551/GpsDevice_nomain.o;\
	fi

${OBJECTDIR}/_ext/98585804/NmeaBase_nomain.o: ${OBJECTDIR}/_ext/98585804/NmeaBase.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/98585804/NmeaBase.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaBase_nomain.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaBase.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/98585804/NmeaBase.o ${OBJECTDIR}/_ext/98585804/NmeaBase_nomain.o;\
	fi

${OBJECTDIR}/_ext/98585804/NmeaGga_nomain.o: ${OBJECTDIR}/_ext/98585804/NmeaGga.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGga.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/98585804/NmeaGga.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaGga_nomain.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGga.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/98585804/NmeaGga.o ${OBJECTDIR}/_ext/98585804/NmeaGga_nomain.o;\
	fi

${OBJECTDIR}/_ext/98585804/NmeaGsa_nomain.o: ${OBJECTDIR}/_ext/98585804/NmeaGsa.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/98585804/NmeaGsa.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaGsa_nomain.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaGsa.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/98585804/NmeaGsa.o ${OBJECTDIR}/_ext/98585804/NmeaGsa_nomain.o;\
	fi

${OBJECTDIR}/_ext/98585804/NmeaRmc_nomain.o: ${OBJECTDIR}/_ext/98585804/NmeaRmc.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaRmc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/98585804/NmeaRmc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaRmc_nomain.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaRmc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/98585804/NmeaRmc.o ${OBJECTDIR}/_ext/98585804/NmeaRmc_nomain.o;\
	fi

${OBJECTDIR}/_ext/98585804/NmeaVtg_nomain.o: ${OBJECTDIR}/_ext/98585804/NmeaVtg.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaVtg.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/98585804
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/98585804/NmeaVtg.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/98585804/NmeaVtg_nomain.o /home/ericfoss/Documents/NmeaGps/src/messages/NmeaVtg.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/98585804/NmeaVtg.o ${OBJECTDIR}/_ext/98585804/NmeaVtg_nomain.o;\
	fi

${OBJECTDIR}/src/utilities_nomain.o: ${OBJECTDIR}/src/utilities.o src/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/utilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Iinclude -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utilities_nomain.o src/utilities.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/utilities.o ${OBJECTDIR}/src/utilities_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
