/*
 * SbgpBox.cpp
 *
 *
 */

#include "SbgpBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

SbgpBox::SbgpBox()
{
	_boxType = BoxBase::SbgpBox;
	_entries = NULL;
}

FUNC_RES SbgpBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_entries = (unsigned int *) malloc(sizeof(unsigned int) * _entryCount * 2);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		// sample count
		stream->ReadBytes(fourChars, 4, &a);
		_entries[i*2] = UtilsIntFromFourChars(fourChars);
		// group description index
		stream->ReadBytes(fourChars, 4, &a);
		_entries[i*2+1] = UtilsIntFromFourChars(fourChars);
	}

	return SUCCESS;
}

void SbgpBox::Print()
{
	printf("Box Type: Sbgp.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentry count: 0x%08X.\r\n", _entryCount);
	if (_entries == NULL)
		return;
	printf("\tentries:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		printf("\t\tentry %d: sample count 0x%08X\tgroup description index 0x%08X.\r\n", i, _entries[i*2], _entries[i*2+1]);
	}
}

SbgpBox::~SbgpBox()
{
	if (_entries)
	{
		free(_entries);
	}
	_entries = NULL;
}

} /* namespace MPEG4Player */
