/*
 * StscBox.cpp
 *
 *
 */

#include "StscBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

StscBox::StscBox()
{
	_boxType = BoxBase::StscBox;
	_chunks = NULL;
}

FUNC_RES StscBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_chunks = (unsigned int *) malloc(sizeof(unsigned int) * _entryCount * 3);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		// first chunk
		stream->ReadBytes(fourChars, 4, &a);
		_chunks[i*3] = UtilsIntFromFourChars(fourChars);
		// samples per chunk
		stream->ReadBytes(fourChars, 4, &a);
		_chunks[i*3+1] = UtilsIntFromFourChars(fourChars);
		// description index
		stream->ReadBytes(fourChars, 4, &a);
		_chunks[i*3+2] = UtilsIntFromFourChars(fourChars);
	}

	return SUCCESS;
}

void StscBox::Print()
{
	printf("Box Type: Stsc.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentry count: 0x%08X.\r\n", _entryCount);
	if (_chunks == NULL)
		return;
	printf("\tchunks:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		printf("\t\tchunk %d: first chunk 0x%08X\t samples per chunk 0x%08X\t description index %x.\r\n", i, _chunks[i*3], _chunks[i*3+1], _chunks[i*3+2]);
	}
}

StscBox::~StscBox()
{
	if (_chunks)
	{
		free(_chunks);
	}
	_chunks = NULL;
}

} /* namespace MPEG4Player */
