/*
 * UdtaBox.cpp
 *
 *
 */

#include "UdtaBox.h"

namespace MPEG4Player
{

UdtaBox::UdtaBox()
{
	_boxType = BoxBase::UdtaBox;
}

FUNC_RES UdtaBox::ParseBox(MPEG4FileStream *stream)
{
	// just skip to the end of the box
	stream->Seek(_size - 4 - 4);				// 4 for size, 4 for 'udta' token

	return SUCCESS;
}

void UdtaBox::Print()
{
	printf("Box Type: Udta.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
}

UdtaBox::~UdtaBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
