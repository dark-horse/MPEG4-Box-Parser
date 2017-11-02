/*
 * SttsBox.cpp
 *
 *
 */

#include "SttsBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

SttsBox::SttsBox()
{
	_boxType = BoxBase::SttsBox;
	_samples = NULL;
}

FUNC_RES SttsBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_samples = (unsigned int *) malloc(sizeof(unsigned int) * _entryCount * 2);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		// count
		stream->ReadBytes(fourChars, 4, &a);
		_samples[i*2] = UtilsIntFromFourChars(fourChars);
		// delta
		stream->ReadBytes(fourChars, 4, &a);
		_samples[i*2+1] = UtilsIntFromFourChars(fourChars);
	}

	return SUCCESS;
}

void SttsBox::Print()
{
	printf("Box Type: Stts.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentry count: 0x%08X.\r\n", _entryCount);
	if (_samples == NULL)
		return;
	printf("\tsamples:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		printf("\t\tsample %d: count 0x%08X\t delta 0x%08X.\r\n", i, _samples[i*2], _samples[i*2+1]);
	}
}

SttsBox::~SttsBox()
{
	if (_samples)
	{
		free(_samples);
	}
	_samples = NULL;
}

} /* namespace MPEG4Player */
