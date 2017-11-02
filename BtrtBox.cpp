/*
 * BtrtBox.cpp
 *
 *
 */

#include "BtrtBox.h"
#include "Utils.h"

namespace MPEG4Player
{

BtrtBox::BtrtBox()
{
	_boxType = BoxBase::BtrtBox;
}

FUNC_RES BtrtBox::ParseBox(MPEG4FileStream *stream)
{
	char fourChars[4];
	unsigned int a;

	stream->ReadBytes(fourChars, 4, &a);
	_bufferSizeDB = UtilsIntFromFourChars(fourChars);

	stream->ReadBytes(fourChars, 4, &a);
	_maxBitRate = UtilsIntFromFourChars(fourChars);

	stream->ReadBytes(fourChars, 4, &a);
	_avgBitRate = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void BtrtBox::Print()
{
	printf("Box Type: Btrt.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);

	printf("\t_bufferSizeDB: 	\t0x%08X.\r\n", _bufferSizeDB);
	printf("\t_maxBitRate: 	\t0x%08X.\r\n", _maxBitRate);
	printf("\t_avgBitrate: 	\t0x%08X.\r\n", _avgBitRate);
}


BtrtBox::~BtrtBox()
{
}

} /* namespace MPEG4Player */
