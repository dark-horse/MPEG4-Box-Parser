/*
 * FullBox.cpp
 *
 *
 */

#include "FullBox.h"
#include "Utils.h"

namespace MPEG4Player
{

FullBox::FullBox()
{
}

FUNC_RES FullBox::ParseVersionFlags(MPEG4FileStream *stream)
{
	char fourChars[4];
	unsigned int a;
	FUNC_RES res = stream->ReadBytes(fourChars, 4, &a);

	unsigned int b = UtilsIntFromFourChars(fourChars);

	_version = (b & 0xFF000000) >> 24;
	_flags = b & 0x00FFFFFF;

	return res;
}

FullBox::~FullBox()
{
}

} /* namespace MPEG4Player */
