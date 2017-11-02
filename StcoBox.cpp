/*
 * StcoBox.cpp
 *
 *
 */

#include "StcoBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

StcoBox::StcoBox()
{
	_boxType = BoxBase::StcoBox;
	_chunkOffsets = NULL;
	_entryCount = 0;
}

FUNC_RES StcoBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_chunkOffsets = (unsigned int *) malloc(sizeof(unsigned int) * _entryCount);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		// chunk Offsets
		stream->ReadBytes(fourChars, 4, &a);
		_chunkOffsets[i] = UtilsIntFromFourChars(fourChars);
	}

	return SUCCESS;
}

void StcoBox::Print()
{
	printf("Box Type: Stco.\r\n");
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
		printf("\t\tchunk %d: offset 0x%08X.\r\n", i, _chunkOffsets[i]);
	}
}

StcoBox::~StcoBox()
{
	if (_chunkOffsets)
	{
		free(_chunkOffsets);
	}
	_chunkOffsets = NULL;
}

} /* namespace MPEG4Player */
