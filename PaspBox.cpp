/*
 * PaspBox.cpp
 *
 *
 */

#include "PaspBox.h"

namespace MPEG4Player
{

PaspBox::PaspBox()
{
	_boxType = BoxBase::PaspBox;
}

FUNC_RES PaspBox::ParseBox(MPEG4FileStream *stream)
{
	char fourChars[4];
	unsigned int a;

	// hSpacing
	stream->ReadBytes(fourChars, 4, &a);
	_hSpacing = UtilsIntFromFourChars(fourChars);

	// vSpacing
	stream->ReadBytes(fourChars, 4, &a);
	_vSpacing = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void PaspBox::Print()
{
	printf("Box Type: PASP.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\thSpacing: %08X.\r\n",_hSpacing);
	printf("\tvSpacing: %08X.\r\n",_vSpacing);
}

PaspBox::~PaspBox()
{
}

} /* namespace MPEG4Player */
