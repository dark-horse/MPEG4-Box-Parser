/*
 * Tkhd.cpp
 *
 *
 */

#include "TkhdBox.h"
#include "Utils.h"

namespace MPEG4Player
{

TkhdBox::TkhdBox()
{
	_boxType = BoxBase::TkhdBox;
}

FUNC_RES TkhdBox::ParseBox(MPEG4FileStream *stream)
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
		_track_ID = UtilsIntFromFourChars(fourChars);

		// read reserved..
		stream->ReadBytes(fourChars, 4, &a);

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
		_track_ID = UtilsIntFromFourChars(fourChars);

		// read reserved..
		stream->ReadBytes(fourChars, 4, &a);

		stream->ReadBytes(fourChars, 4, &a);
		_duration = UtilsIntFromFourChars(fourChars);
	}

	// read reserved twice
	stream->ReadBytes(fourChars, 4, &a);
	stream->ReadBytes(fourChars, 4, &a);

	stream->ReadBytes(fourChars, 4, &a);
	unsigned int b = UtilsIntFromFourChars(fourChars);
	_layer = (b & 0xFFFF0000) >> 16;
	_alternate_group = (b & 0x0000FFFF);

	stream->ReadBytes(fourChars, 4, &a);
	b = UtilsIntFromFourChars(fourChars);
	_volume = (b & 0xFFFF0000) >> 16;

	// 3 x 3 matrix
	for (int i = 0; i < 3; i ++)
	{
		stream->ReadBytes(fourChars, 4, &a);
		_matrix [ i ] = UtilsIntFromFourChars(fourChars);

		stream->ReadBytes(fourChars, 4, &a);
		_matrix [ i + 3 ] = UtilsIntFromFourChars(fourChars);

		stream->ReadBytes(fourChars, 4, &a);
		_matrix [ i + 6 ] = UtilsIntFromFourChars(fourChars);
	}

	stream->ReadBytes(fourChars, 4, &a);
	_width = UtilsIntFromFourChars(fourChars);

	stream->ReadBytes(fourChars, 4, &a);
	_height = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void TkhdBox::Print()
{
	printf("Box Type: Tkhd.\r\n");
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

	printf("\tTrackID: %d.\r\n", _track_ID);

	if (_version == 1)
	{
		printf("\tduration - 64 bit duration will be added later.\r\n");
	}
	else
	{
		printf("\tduration: %d.\r\n", _duration);
	}
	printf("\tlayer: 0x%08X.\r\n", _layer);
	printf("\talternate Group: 0x%08X.\r\n", _alternate_group);
	printf("\tvolume: 0x%08X.\r\n", _volume);

	printf("\tmatrix:\r\n");
	printf("\t\t0x%08X\t0x%08X\t0x%08X\r\n", _matrix[0], _matrix[1], _matrix[2]);
	printf("\t\t0x%08X\t0x%08X\t0x%08X\r\n", _matrix[3], _matrix[4], _matrix[5]);
	printf("\t\t0x%08X\t0x%08X\t0x%08X\r\n", _matrix[6], _matrix[7], _matrix[8]);

	printf("\twidth: 0x%08X.\r\n", _width);
	printf("\theight: 0x%08X.\r\n", _height);
}


TkhdBox::~TkhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
