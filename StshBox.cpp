/*
 * StshBox.cpp
 *
 *
 */

#include "StshBox.h"
#include "Utils.h"

namespace MPEG4Player
{

StshBox::StshBox()
{
	_boxType = BoxBase::StshBox;
	_entry_count = 0;
}

FUNC_RES StshBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	stream->ReadBytes(fourChars, 4, &a);
	_entry_count = UtilsIntFromFourChars(fourChars);

	unsigned int loopCount = min (_entry_count, StshBox::EntryTblSize);
	unsigned int i = 0;

	while (i < loopCount)
	{
		stream->ReadBytes(fourChars, 4, &a);
		_shadowed_sample_entries[i] = UtilsIntFromFourChars(fourChars);
		stream->ReadBytes(fourChars, 4, &a);
		_sync_sample_entries[i] = UtilsIntFromFourChars(fourChars);
		i++;
	}

	// read the rest of the box.
	while (i < _entry_count)
	{
		stream->ReadBytes(fourChars, 4, &a);
		stream->ReadBytes(fourChars, 4, &a);
		i++;
	}

	return SUCCESS;
}

void StshBox::Print()
{
	printf("Box Type: Stsh.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tentries_count: %d.\r\n", _entry_count);

	for (unsigned int i = 0; i < min(_entry_count, StshBox::EntryTblSize); i++)
	{
		printf("\t\tshadowed sample entry %d: %d.\r\n", i, _shadowed_sample_entries[i]);
		printf("\t\tsync sample entry %d: %d.\r\n", i, _sync_sample_entries[i]);
	}
}




StshBox::~StshBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
