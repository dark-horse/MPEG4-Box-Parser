/*
 * TrexBox.cpp
 *
 *
 */

#include "TrexBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

TrexBox::TrexBox()
{
	_boxType = BoxBase::TrexBox;
}

FUNC_RES TrexBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// _trackID;
	stream->ReadBytes(fourChars, 4, &a);
	_trackID = UtilsIntFromFourChars(fourChars);

	// _defaultSampleDescriptionIndex;
	stream->ReadBytes(fourChars, 4, &a);
	_defaultSampleDescriptionIndex = UtilsIntFromFourChars(fourChars);
	
	// _defaultSampleDuration;
	stream->ReadBytes(fourChars, 4, &a);
	_defaultSampleDuration = UtilsIntFromFourChars(fourChars);

	// _defaultSampleSize;
	stream->ReadBytes(fourChars, 4, &a);
	_defaultSampleSize = UtilsIntFromFourChars(fourChars);
	
	// _defaultSampleFlags;
	stream->ReadBytes(fourChars, 4, &a);
	_defaultSampleFlags = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void TrexBox::Print()
{
	printf("Box Type: Trex.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	
	printf("\t track ID: 0x%08X.\r\n", _trackID);
	printf("\t default sample description index: 0x%08X.\r\n", _defaultSampleDescriptionIndex);
	printf("\t default sample duration: 0x%08X.\r\n", _defaultSampleDuration);
	printf("\t default sample size: 0x%08X.\r\n", _defaultSampleSize);
	printf("\t default sample flags: 0x%08X.\r\n", _defaultSampleFlags);
}

TrexBox::~TrexBox()
{
}

} /* namespace MPEG4Player */
