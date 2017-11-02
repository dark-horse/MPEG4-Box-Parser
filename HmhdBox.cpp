/*
 * HmhdBox.cpp
 *
 *
 */

#include "HmhdBox.h"
#include "Utils.h"

namespace MPEG4Player
{

HmhdBox::HmhdBox()
{
	_boxType = BoxBase::HmhdBox;
}

FUNC_RES HmhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char twoChars[2];
	char fourChars[4];

	stream->ReadBytes(twoChars, 2, &a);
	_maxPDUSize = UtilsIntFromTwoChars(twoChars);

	stream->ReadBytes(twoChars, 2, &a);
	_avgPDUSize = UtilsIntFromTwoChars(twoChars);

	stream->ReadBytes(fourChars, 4, &a);
	_maxbitrate = UtilsIntFromFourChars(fourChars);

	stream->ReadBytes(fourChars, 4, &a);
	_avgbitrate = UtilsIntFromFourChars(fourChars);

	// read the reserved int
	stream->ReadBytes(fourChars, 4, &a);

	return SUCCESS;
}

void HmhdBox::Print()
{
	printf("Box Type: Hmhd.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tmaxPDUSize: 0x%08X.\r\n", _maxPDUSize);
	printf("\tavgPDUSize: 0x%08X.\r\n", _avgPDUSize);
	printf("\tmaxbitRate: 0x%08X.\r\n", _maxbitrate);
	printf("\tavgbitRate: 0x%08X.\r\n", _avgbitrate);
}

HmhdBox::~HmhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
