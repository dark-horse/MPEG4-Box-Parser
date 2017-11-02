/*
 * SmhdBox.cpp
 *
 *
 */

#include "SmhdBox.h"
#include "Utils.h"

namespace MPEG4Player
{

SmhdBox::SmhdBox()
{
	_boxType = BoxBase::SmhdBox;
}

FUNC_RES SmhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char twoChars[2];

	stream->ReadBytes(twoChars, 2, &a);
	_balance = UtilsIntFromTwoChars(twoChars);
	stream->ReadBytes(twoChars, 2, &a);
	return SUCCESS;
}

void SmhdBox::Print()
{
	printf("Box Type: Smhd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tbalance: 0x%08X.\r\n", _balance);
}
SmhdBox::~SmhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
