/*
 * MdatBox.cpp
 *
 *
 */

#include "MdatBox.h"
#include "Utils.h"

namespace MPEG4Player
{

MdatBox::MdatBox()
{
	_boxType = BoxBase::MdatBox;
}

FUNC_RES MdatBox::ParseBox(MPEG4FileStream *stream)
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
		res = stream->Seek(_largeSize - 4 - 4 - 8); // 4 for initial size, another 4 for "free" type, and 8 for largeSize
	}
	else
	{
		res = stream->Seek(_size - 4 - 4);	// 4 is for initial size, another for for "free" type
	}

	return res;
}

void MdatBox::Print()
{
	printf("Box Type: Mdat.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
}


MdatBox::~MdatBox()
{
}

} /* namespace MPEG4Player */
