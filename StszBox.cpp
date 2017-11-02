/*
 * StszBox.cpp
 *
 *
 */

#include "StszBox.h"
#include "Utils.h"

namespace MPEG4Player
{

StszBox::StszBox()
{
	_boxType = BoxBase::StszBox;
	_sample_count = 0;
}

FUNC_RES StszBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	stream->ReadBytes(fourChars, 4, &a);
	_default_size = UtilsIntFromFourChars(fourChars);

	if (_default_size == 0)
	{
		stream->ReadBytes(fourChars, 4, &a);
		_sample_count = UtilsIntFromFourChars(fourChars);

		unsigned int loopCount = min (_sample_count, StszBox::EntryTblSize);
		unsigned int i = 0;
		while (i < loopCount)
		{
			stream->ReadBytes(fourChars, 4, &a);
			_sample_sizes[i] = UtilsIntFromFourChars(fourChars);
			i++;
		}

		while (i < _sample_count)
		{
			stream->ReadBytes(fourChars, 4, &a);
			i++;
		}
	}


	return SUCCESS;
}

void StszBox::Print()
{
	printf("Box Type: Stsz.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tdefault sample size: %d.\r\n", _default_size);

	for (unsigned int i = 0; i < min(_sample_count, StszBox::EntryTblSize); i++)
	{
		printf("\t\tsample size %d: %d.\r\n", i, _sample_sizes[i]);
	}
}

StszBox::~StszBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
