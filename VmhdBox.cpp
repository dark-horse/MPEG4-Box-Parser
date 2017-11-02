/*
 * VmhdBox.cpp
 *
 *
 */

#include "VmhdBox.h"
#include "Utils.h"

namespace MPEG4Player
{

VmhdBox::VmhdBox()
{
	_boxType = BoxBase::VmhdBox;
}

FUNC_RES VmhdBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char twoChars[2];

	stream->ReadBytes(twoChars, 2, &a);
	_graphicsMode = UtilsIntFromTwoChars(twoChars);

	stream->ReadBytes(twoChars, 2, &a);
	_opColor[0] = UtilsIntFromTwoChars(twoChars);

	stream->ReadBytes(twoChars, 2, &a);
	_opColor[1] = UtilsIntFromTwoChars(twoChars);

	stream->ReadBytes(twoChars, 2, &a);
	_opColor[2] = UtilsIntFromTwoChars(twoChars);

	return SUCCESS;
}

void VmhdBox::Print()
{
	printf("Box Type: VHMD.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tgraphicsMode: %x.\r\n", _graphicsMode);

	printf("\topColors: %x; %x; %x\r\n", _opColor[0], _opColor[1], _opColor[2]);
}

VmhdBox::~VmhdBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
