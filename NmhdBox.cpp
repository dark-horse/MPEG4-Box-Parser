/*
 * NmhdBox.cpp
 *
 *
 */

#include "NmhdBox.h"

namespace MPEG4Player
{

NmhdBox::NmhdBox()
{
	_boxType = BoxBase::NmhdBox;
}

FUNC_RES NmhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	return SUCCESS;
}

void NmhdBox::Print()
{
	printf("Box Type: Nmhd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
}

NmhdBox::~NmhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
