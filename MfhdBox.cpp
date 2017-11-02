/*
 * MfhdBox.cpp
 *
 *
 */

#include "MfhdBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

MfhdBox::MfhdBox()
{
	_boxType = BoxBase::MfhdBox;
}

FUNC_RES MfhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// _sequenceNumber
	stream->ReadBytes(fourChars, 4, &a);
	_sequenceNumber = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void MfhdBox::Print()
{
	printf("Box Type: Mehd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	
	printf("\t sequence number: 0x%08X.\r\n", _sequenceNumber);
}

MfhdBox::~MfhdBox()
{
}

} /* namespace MPEG4Player */
