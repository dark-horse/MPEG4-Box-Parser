/*
 * Co64Box.cpp
 *
 *
 */

#include "Co64Box.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

Co64Box::Co64Box()
{
	_boxType = BoxBase::Co64Box;
	_chunkOffsets = NULL;
}

FUNC_RES Co64Box::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];
	char eightChars[8];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_chunkOffsets = (unsigned long long int *) malloc(sizeof(unsigned long long int) * _entryCount);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		// chunk Offsets
		stream->ReadBytes(eightChars, 4, &a);
		_chunkOffsets[i] = UtilsLongIntFromEightChars(eightChars);
	}

	return SUCCESS;
}

void Co64Box::Print()
{
	printf("Box Type: C064.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentry count: 0x%08X.\r\n", _entryCount);
	if (_chunkOffsets == NULL)
		return;
	printf("\tchunk Offsets:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		printf("\t\tchunk %d: offset 0x%I64d.\r\n", i, _chunkOffsets[i]);
	}
}

Co64Box::~Co64Box()
{
	if (_chunkOffsets)
	{
		free(_chunkOffsets);
	}
	_chunkOffsets = NULL;
}

} /* namespace MPEG4Player */
