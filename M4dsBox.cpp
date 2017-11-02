/*
 * M4dsBox.cpp
 *
 *
 */

#include "M4dsBox.h"

namespace MPEG4Player
{

M4dsBox::M4dsBox()
{
	_boxType = BoxBase::M4dsBox;
}

FUNC_RES M4dsBox::ParseBox(MPEG4FileStream *stream)
{
	// TODO - implement this
	stream->Seek(_size - 4 - 4);		// 4 for size, 4 for "m4ds" token

	return SUCCESS;
}

void M4dsBox::Print()
{
	printf("Box Type: Btrt.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
}

M4dsBox::~M4dsBox()
{
}

} /* namespace MPEG4Player */
