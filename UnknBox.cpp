/*
 * UnknBox.cpp
 *
 *
 */

#include "UnknBox.h"
#include "Utils.h"

namespace MPEG4Player
{

UnknBox::UnknBox(char *token)
{
	memcpy(_token /*dest*/, token /*src*/, 4 /*num*/);
	_boxType = BoxBase::UnknBox;
}

FUNC_RES UnknBox::ParseBox(MPEG4FileStream *stream)
{
	unsigned int a;
	FUNC_RES res;
	// we have to move the pointer in the stream to the next box
	// We have to figure out the size of this box.

	if (_size == 1)
	{
		// this is a large box.
		_isLargeBox = true;
		char eightChars[8];
		stream->ReadBytes(eightChars, 8, &a);
		_largeSize = UtilsLongIntFromEightChars(eightChars);
		res = stream->Seek(_largeSize - 4 - 4 - 8); // 4 for initial size, another 4 for "unkn" token, and 8 for largeSize
	}
	else
	{
		res = stream->Seek(_size - 4 - 4);	// 4 is for initial size, another for for "unkn" type
	}

	return res;
}

void UnknBox::Print()
{
	printf("Box Type: UNKNOWN.\r\n");
	printf("\ttoken: %c%c%c%c.\r\n", _token[0],_token[1],_token[2],_token[3]);

	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
}

UnknBox::~UnknBox()
{
	// TODO Auto-generated destructor stub
}
} /* namespace MPEG4Player */
