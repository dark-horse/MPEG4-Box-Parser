/*
 * Utils.cpp
 *
 *	Some utility functions.
 *
 */

#include "Utils.h"

// convert from big endian to small endian
unsigned int UtilsIntFromTwoChars(char *twoChars)
{
	char fourChars[4];
	fourChars[0] = twoChars[0]; fourChars[1] = twoChars[1]; fourChars[2] = '\0'; fourChars[3] = '\0';
	return UtilsIntFromFourChars(fourChars);
}

// convert from big endian to small endian
unsigned int UtilsIntFromFourChars(char *fourChars)
{
	unsigned int a;
	a = * reinterpret_cast<unsigned int*>(fourChars);
	a = ( a >> 24 ) | ( ( a << 8 ) & 0x00FF0000 ) |
	       ( ( a >> 8 ) & 0x0000FF00 ) | ( a << 24 );

	return a;
}

// convert from big endian to small endian
unsigned long long int UtilsLongIntFromEightChars(char *eightChars)
{
	unsigned long long int a;
	a = * reinterpret_cast<unsigned int*>(eightChars);
	unsigned long long int a0 = a >> 56;
	unsigned long long int a1 = (a >> 40) | 0x000000000000FF00;
	unsigned long long int a2 = (a >> 24) | 0x0000000000FF0000;
	unsigned long long int a3 = (a >>  8) | 0x00000000FF000000;
	unsigned long long int a4 = (a <<  8) | 0x000000FF00000000;
	unsigned long long int a5 = (a << 24) | 0x0000FF0000000000;
	unsigned long long int a6 = (a << 40) | 0x00FF000000000000;
	unsigned long long int a7 = a << 56;

	a = a0 | a1 | a2 | a3 | a4 | a5 | a6 | a7;

	return a;
}

// input time in number of seconds since midnight Jan 1, 1904,
// output the time in year / month / day / hour / minute / second format.
void DateFormat(unsigned int time, int *year, int *month, int *date, int *hour, int *minute, int *second)
{

	int numDays = time / (60 * 60 * 24);
	int numSecs = time % (60 * 60 * 24);

	// hour
	*hour = numSecs / (60 * 60);
	// minute
	*minute = (numSecs / 60) % 60;
	// second
	*second = numSecs % 60;

	// to find the year / month / date we will cut some corners (sorry, but none of my videos start before 2010. and MPEG4 was published in Oct 2008 anyway)
	// start with 01/01/2008
	numDays -= 37986;
	if (numDays < 0)
	{
		*year = 0;
		*month = 0;
		*date = 0;
		return;
	}

	// The video is more recent than 01/01/2008.
	int yr = 2008;
	int days;
	while (true)
	{
		IsLeapYear(yr)? days = 366 : days = 365;
		if (numDays < days)
			break;
		numDays -= days;
		yr ++;
	}
	// year
	*year = yr;
	bool leapYr = IsLeapYear(yr);
	int mth = 1;
	while (true)
	{
		days = DaysInMonth(mth, leapYr);
		if (numDays < days)
			break;
		numDays -= days;
		mth ++;
	}
	// month
	*month = mth;
	// date
	*date = numDays;
}

bool IsLeapYear(int year)
{
	if (year % 400 == 0)
	{
		return true;
	}
	else if (year % 100 == 0)
	{
		return false;
	}
	else if (year % 4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int DaysInMonth (int month, bool leapYear)
{
	switch (month)
	{
	case 1:
		return 31;
	case 2:
		return leapYear ? 29 : 28;
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	default:
		return 0;
	}
}

// Exp-Golomb functions: ParseUev/ParseSev/ParseMev
unsigned int ParseUev(char *buf, unsigned int offset, unsigned int *updatedOffset)
{
	int leadingZeroBits = -1;

	int offsetInBit = offset % 8;
	int offsetInBuf = offset / 8;
	char ch = buf[offsetInBuf];

	for (int b = 0; !b; leadingZeroBits ++)
	{
		if (offsetInBit == 8)
		{
			// move to the next char
			offsetInBit = 0;
			offsetInBuf ++;
			ch = buf[offsetInBuf];
		}

		unsigned char uCh = ((unsigned char) ch) << offsetInBit;
		b = uCh & 0x80 ? 1 : 0;
		offsetInBit ++;
		offset ++;
	}

	unsigned int suffix = 0;
	for (int i = 0; i < leadingZeroBits; i++)
	{
		if (offsetInBit == 8)
		{
			// move to the next char
			offsetInBit = 0;
			offsetInBuf ++;
			ch = buf[offsetInBuf];
		}
		unsigned char uCh = ((unsigned char) ch) << offsetInBit;
		unsigned int b = uCh & 0x80 ? 1 : 0;
		suffix = (suffix << 1) | b;					// suffix * 2 + b
		offsetInBit ++;
		offset ++;
	}

	*updatedOffset = offset;

	//return (((unsigned int)1) << leadingZeroBits) - 1 + suffix;		// 2 ^ leadingZeroBits - 1 + suffix
	return ((((unsigned int)1)<<leadingZeroBits) | suffix) - 1;			// 2 ^ leadingZeroBits - 1 + suffix
}

int ParseSev(char *buf, unsigned int offset, unsigned int * updatedOffset)
{
	unsigned int i = ParseUev(buf, offset, updatedOffset);
	int sign = (i+1) % 2 ? -1 : 1;				// the compiler optimizes this to an AND operation (and not division by 2). Checked the assembly.

	return sign *( i/2 + i%2);					// the compilers optimizes this to Right Shift + AND operation. Checked the assembly.
}

unsigned int intra_4x4Table[48] =
								{
									47, 	31, 	15, 	0, 		23, 	27, 	29, 	30,
									7, 		11, 	13, 	14, 	39, 	43,		45,		46,
									16, 	3, 		5, 		10,		 12,	19, 	21, 	26,
									28, 	35, 	37, 	42,		44, 	1, 		2, 		4,
									8, 		17, 	18,		20,		24, 	6,		9, 		22,
									25, 	32,		33,		34,		36,		40,		38,		41
								};

unsigned int interTable[48] =
								{
									0,		16,		1,		2,		4,		8,		32,		3,
									5,		10,		12,		15,		47,		7,		11,		13,
									14,		6,		9,		31,		35,		37,		42,		44,
									33,		34,		36,		40,		39,		43,		45,		46,
									17,		18,		20,		24,		19,		21,		26,		28,
									23,		27,		29,		30,		22,		25,		38,		41
								};

unsigned int ParseMev(char *buf, unsigned int offset, unsigned int * updatedOffset, PredictionMode predMode)
{
	unsigned int i = ParseUev(buf, offset, updatedOffset);
	if (predMode == Intra_4x4)
	{
		return intra_4x4Table[i];
	}
	else if (predMode == Inter)
	{
		return interTable[i];
	}

	// should not be the case....
	return 0;
}

