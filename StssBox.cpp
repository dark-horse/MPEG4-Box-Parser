/*
 * StssBox.cpp
 *
 *
 */

#include "StssBox.h"
#include "Utils.h"

namespace MPEG4Player
{

StssBox::StssBox()
{
	_boxType = BoxBase::StssBox;
	_entry_count = 0;
}

FUNC_RES StssBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	stream->ReadBytes(fourChars, 4, &a);
	_entry_count = UtilsIntFromFourChars(fourChars);

	unsigned int loopCount = min (_entry_count, StssBox::EntryTblSize);
	unsigned int i = 0;

	while (i < loopCount)
	{
		stream->ReadBytes(fourChars, 4, &a);
		_entries[0] = UtilsIntFromFourChars(fourChars);
		i++;
	}

	// read the rest of the sample entries.
	while (i < _entry_count)
	{
		stream->ReadBytes(fourChars, 4, &a);
		i++;
	}

	return SUCCESS;
}

void StssBox::Print()
{
	printf("Box Type: Stss.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tentries_count: %d.\r\n", _entry_count);

	for (unsigned int i = 0; i < min(_entry_count, StssBox::EntryTblSize); i++)
	{
		printf("\t\tentry %d: %d.\r\n", i, _entries[i]);
	}
}

StssBox::~StssBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
