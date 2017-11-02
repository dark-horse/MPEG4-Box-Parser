/*
 * StsdBox.cpp
 *
 *
 */

#include "StsdBox.h"

namespace MPEG4Player
{

StsdBox::StsdBox()
{
	memset (this, 0, sizeof(StsdBox));
	_boxType = BoxBase::StsdBox;
}

FUNC_RES StsdBox::ParseBox(MPEG4FileStream *stream)
{
	// TODO - this only implements AVCC box.

	stream->Seek(_size - 4 - 4);			// 4 for size, 4 for 'stsd' token
	return SUCCESS;
}

void StsdBox::Print()
{
	printf("Box Type: Stsd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tStsd not fully implemented.\r\n");
}

StsdBox::~StsdBox()
{
	if (_boxes)
	{
		for (unsigned int i = 0; i < _numBoxes; i ++)
		{
			BoxBase *b = *(_boxes + i);
			if (b)
				delete (b);
		}

		free (_boxes);
	}

	memset (this, 0, sizeof(StsdBox));
}

} /* namespace MPEG4Player */
