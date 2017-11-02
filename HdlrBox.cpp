/*
 * HdlrBox.cpp
 *
 *
 */

#include "HdlrBox.h"
#include <stdlib.h>

namespace MPEG4Player
{

HdlrBox::HdlrBox()
{
	_boxType = BoxBase::HdlrBox;
	_name = NULL;
}

FUNC_RES HdlrBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read pre_defined.
	stream->ReadBytes(fourChars, 4, &a);

	stream->ReadBytes(_handler_type, 4, &a);

	// read reserved 3 times
	stream->ReadBytes(fourChars, 4, &a);
	stream->ReadBytes(fourChars, 4, &a);
	stream->ReadBytes(fourChars, 4, &a);

	// skip the name part
	unsigned long long int offset = _size - 4 - 4 - 4; // 4 for size, 4 for box type, 4 for version & flags
	offset -= 4 + 4 + 4 * 3; // 4 for pre defined, 4 for handler type, 4 * 3 for 3 reserved ints.
	return stream->Seek(offset);
}

void HdlrBox::Print()
{
	printf("Box Type: HDLR.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\thandler_type: %c%c%c%c.\r\n", _handler_type[0],_handler_type[1],_handler_type[2],_handler_type[3]);
}

HdlrBox::~HdlrBox()
{
	if (_name)
		free(_name);
	_name = NULL;
}

} /* namespace MPEG4Player */
