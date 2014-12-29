/* 
 * File:   convertions.h
 * Author: ericfoss
 *
 * Created on December 17, 2014, 11:26 AM
 */

#ifndef CONVERSIONS_H
#define	CONVERSIONS_H

#include <stdexcept>
#include <string>

float degToDec(float degree, char dir);
char calcChecksum(std::string str);
bool isMsgValid(std::string msg);
int dateTimeToEpoch(unsigned short date[], float time[]);
char *xstrtok(char *line, char *delims);

#endif	/* CONVERSIONS_H */

