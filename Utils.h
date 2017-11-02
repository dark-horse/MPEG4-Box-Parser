/*
 * Utils.h
 *
 * Some utility functions.
 *
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include "MPEG4Player.h"

unsigned int UtilsIntFromTwoChars(char *twoChars);
unsigned int UtilsIntFromFourChars(char *fourChars);
unsigned long long int UtilsLongIntFromEightChars(char *eightChars);
// input time in number of seconds since midnight Jan 1, 1904,
// output the time in year / month / day / hour / minute / second format.
void DateFormat(unsigned int time, int *year, int *month, int *date, int *hour, int *minute, int *second);
bool IsLeapYear(int year);
int DaysInMonth (int month, bool leapYear);

// parsing for Exp-Golomb codes
unsigned int ParseUev(char *buf, 						// the block of memory that contains the Exp-Golomb code
					  unsigned int offset,				// the offset in *bits* from where to start parsing
					  unsigned int *updatedOffset); 	// the updated offset in buf
int ParseSev(char *buf, 						// the block of memory that contains the Exp-Golomb code
			 unsigned int offset,				// the offset in *bits* from where to start parsing
			 unsigned int *updatedOffset); 		// the updated offset in buf
unsigned int ParseMev(char *buf, 						// the block of memory that contains the Exp-Golomb code
					  unsigned int offset,				// the offset in *bits* from where to start parsing
					  unsigned int *updatedOffset); 	// the updated offset in buf



#endif /* UTILS_H_ */
