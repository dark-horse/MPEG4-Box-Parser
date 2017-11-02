/*
 * ElstBox.cpp
 *
 *
 */

#include "ElstBox.h"
#include "Utils.h"

#include <stdlib.h>

namespace MPEG4Player
{

ElstBox::ElstBox()
{
	_boxType = BoxBase::ElstBox;
	_entries = NULL;
}

FUNC_RES ElstBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char twoChars[2];
	char fourChars[4];
	char eightChars[8];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_entries = (EditListEntry *) malloc(sizeof(EditListEntry) * _entryCount);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		if (_version)
		{
			// 64 bit segment
			// segment duration
			stream->ReadBytes(eightChars, 8, &a);
			_entries[i]._duration._duration64 = UtilsLongIntFromEightChars(eightChars);
			// media time
			stream->ReadBytes(eightChars, 8, &a);
			_entries[i]._mediaTime._mediaTime64 = UtilsLongIntFromEightChars(eightChars);
		}
		else
		{
			// 32 bit segment
			// segment duration
			stream->ReadBytes(fourChars, 4, &a);
			_entries[i]._duration._duration32 = UtilsIntFromFourChars(fourChars);
			// media time
			stream->ReadBytes(fourChars, 4, &a);
			_entries[i]._mediaTime._mediaTime32 = UtilsIntFromFourChars(fourChars);
		}
		
		// media_rate_Integer
		stream->ReadBytes(twoChars, 2, &a);
		_entries[i]._media_rate_integer = UtilsIntFromTwoChars(twoChars);
		stream->ReadBytes(twoChars, 2, &a);
	}

	return SUCCESS;
}

void ElstBox::Print()
{
	printf("Box Type: Elst.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentries count: 0x%08X.\r\n", _entryCount);

	if (_entries == NULL)
		return;
	printf("\tentries:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		if (_version)
		{
			// 64 bit
			printf("\t\tentry %dd: duration %I64d\t media time %I64d\t media rate integer %x.\r\n",
				i,
				_entries[i]._duration._duration64,
				_entries[i]._mediaTime._mediaTime64,
				_entries[i]._media_rate_integer);
		}
		else
		{
			//32 bit
			printf("\t\tentry %d: duration %x\t media time %x\t media rate integer %x.\r\n",
				i,
				_entries[i]._duration._duration32,
				_entries[i]._mediaTime._mediaTime32,
				_entries[i]._media_rate_integer);
		}
	}
}

ElstBox::~ElstBox()
{
	if (_entries)
	{
		free(_entries);
	}
	_entries = NULL;
}

} /* namespace MPEG4Player */
