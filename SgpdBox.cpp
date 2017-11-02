/*
 * SgpdBox.cpp
 *
 *
 */

#include "SgpdBox.h"

namespace MPEG4Player
{

SgpdBox::SgpdBox()
{
	_boxType = BoxBase::SgpdBox;
}

FUNC_RES SgpdBox::ParseBox(MPEG4FileStream *stream)
{
	// TODO: implement this
	stream->Seek(_size - 4 - 4);				// 4 for size, 4 for 'sgpd' token
	return SUCCESS;
}
void SgpdBox::Print()
{
	printf("Box Type: Sgpd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tSgpd box not fully implemented.\r\n");
}


SgpdBox::~SgpdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
