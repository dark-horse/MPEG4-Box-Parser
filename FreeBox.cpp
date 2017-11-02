/*
 * FreeBox.cpp
 *
 *
 */

#include "FreeBox.h"
#include "Utils.h"

namespace MPEG4Player
{

FreeBox::FreeBox()
{
	_boxType = BoxBase::FreeBox;
}

FUNC_RES FreeBox::ParseBox(MPEG4FileStream *stream)
{
	FUNC_RES res = ParseBoxHeader(stream);
	if (_isLargeBox)
	{
		res = stream->Seek(_largeSize - 4 - 4 - 8); // 4 for initial size, another 4 for "free" type, and 8 for largeSize
	}
	else
	{
		res = stream->Seek(_size - 4 - 4);	// 4 is for initial size, another for for "free" type
	}

	return res;
}

void FreeBox::Print()
{
	printf("Box Type: Free.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
}



FreeBox::~FreeBox()
{
}

} /* namespace MPEG4Player */
