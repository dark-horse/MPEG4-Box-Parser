/*
 * UrlBox.cpp
 *
 *
 */

#include "UrlBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

UrlBox::UrlBox()
{
	_boxType = BoxBase::UrlBox;
	_location = NULL;
	_locationSize = 0;
}

FUNC_RES UrlBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);

	// copy the location
	unsigned int a;
	_location = (char *) malloc ((_size - 4 - 4 - 4)*sizeof(char));

	stream->ReadBytes(_location, _size - 4 - 4 - 4, &a);	// 4 is for initial size, 4 for for "url " type, 4 for version & flags, locationBytes for the bytes read.

	return SUCCESS;
}

void UrlBox::Print()
{
	printf("Box Type: Url.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	if (_location)
	{
		// TODO : maybe convert to something more printer friendly for UTF-8? At least ASCII characters will show up correctly...
		printf("\tlocation: %s.\r\n", _location);
	}
}

UrlBox::~UrlBox()
{
	if (_location)
		free(_location);
	_location = NULL;
	_locationSize = 0;
}

} /* namespace MPEG4Player */
