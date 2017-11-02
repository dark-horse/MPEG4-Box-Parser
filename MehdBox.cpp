/*
 * MehdBox.cpp
 *
 *
 */

#include "MehdBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

MehdBox::MehdBox()
{
	_boxType = BoxBase::MehdBox;
}

FUNC_RES MehdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];
	char eightChars[8];

	if (_version)
	{
		// 64 bit
		stream->ReadBytes(eightChars, 8, &a);
		_fragmentDuration._duration64 =  UtilsLongIntFromEightChars(eightChars);
	}
	else
	{
		// 32 bit segment
		stream->ReadBytes(fourChars, 4, &a);
		_fragmentDuration._duration32 =  UtilsIntFromFourChars(fourChars);
	}
	
	return SUCCESS;
}

void MehdBox::Print()
{
	printf("Box Type: Mehd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	if (_version)
	{
		// 64 bit
		printf("\t\tfragment duration %I64d\r\n", _fragmentDuration._duration64);
	}
	else
	{
		//32 bit
		printf("\t\tfragment duration 0x%08X\r\n", _fragmentDuration._duration32);
	}
}

MehdBox::~MehdBox()
{
}

} /* namespace MPEG4Player */
