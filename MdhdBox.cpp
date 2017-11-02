/*
 * MdhdBox.cpp
 *
 *
 */

#include "MdhdBox.h"
#include "Utils.h"
namespace MPEG4Player
{

MdhdBox::MdhdBox()
{
	_boxType = BoxBase::MdhdBox;
}

FUNC_RES MdhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	if(_version == 1)
	{
		char eightChars[8];
		stream->ReadBytes(eightChars, 8, &a);
		_creationTime_64 = UtilsLongIntFromEightChars(eightChars);
		stream->ReadBytes(eightChars, 8, &a);
		_modificationTime_64 = UtilsLongIntFromEightChars(eightChars);
		stream->ReadBytes(fourChars, 4, &a);
		_timescale = UtilsIntFromFourChars(fourChars);
		stream->ReadBytes(eightChars, 8, &a);
		_duration_64 = UtilsLongIntFromEightChars(eightChars);
	}
	else
	{
		stream->ReadBytes(fourChars, 4, &a);
		_creationTime = UtilsIntFromFourChars(fourChars);
		stream->ReadBytes(fourChars, 4, &a);
		_modificationTime = UtilsIntFromFourChars(fourChars);
		stream->ReadBytes(fourChars, 4, &a);
		_timescale = UtilsIntFromFourChars(fourChars);
		stream->ReadBytes(fourChars, 4, &a);
		_duration = UtilsIntFromFourChars(fourChars);
	}

	stream->ReadBytes(fourChars, 4, &a);
	// why the hell did they pack the language code the way they did???
	// There are better ways to pack 3 bytes into a 32 bit value than
	// the characters in the language code are offsets from character 0x60
	unsigned int b = * reinterpret_cast<unsigned int*>(fourChars);
	_language[0] = ((b & 0x0)) + ((char) 0x60);
	// TODO - finish this ridiculousness.
	return SUCCESS;
}

void MdhdBox::Print()
{
	printf("Box Type: Mdhd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	if (_version == 1)
	{
		// 64 bit dates. Not now.
		printf("\tdate - 64 bit date support will be added later.\r\n");
	}
	else
	{
		int year, month, date, hour, minute, second;
		DateFormat(_creationTime, &year, &month, &date, &hour, &minute, &second);
		printf("\tCreation Time:\r\n");
		printf("\t\tyear:\t%d\r\n", year);
		printf("\t\tmonth:\t%d\r\n", month);
		printf("\t\tdate:\t%d\r\n", date);
		printf("\t\thour:\t%d\r\n", hour);
		printf("\t\tminute:\t%d\r\n", minute);
		printf("\t\tsecond:\t%d.\r\n\r\n", second);

		DateFormat(_modificationTime, &year, &month, &date, &hour, &minute, &second);
		printf("\tModification Time:\r\n");
		printf("\t\tyear:\t%d\r\n", year);
		printf("\t\tmonth:\t%d\r\n", month);
		printf("\t\tdate:\t%d\r\n", date);
		printf("\t\thour:\t%d\r\n", hour);
		printf("\t\tminute:\t%d\r\n", minute);
		printf("\t\tsecond:\t%d.\r\n\r\n", second);
	}

	if (_version == 1)
	{
		printf("\tduration - 64 bit duration will be added later.\r\n");
	}
	else
	{
		printf("\tduration: %d.\r\n", _duration);
	}

	printf("\tlanguage: %c%c%c.\r\n", _language[0], _language[1], _language[2]);
}


MdhdBox::~MdhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
