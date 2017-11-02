/*
 * UrnBox.cpp
 *
 *
 */

#include "UrnBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

UrnBox::UrnBox()
{
	_boxType = BoxBase::UrnBox;
	_name = NULL;
	_nameSize = 0;
	_location = NULL;
	_locationSize = 0;
}

FUNC_RES UrnBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);

	// copy the name.
	unsigned int nameBytes;
	_name = UrnBox::CopyUTF8String(stream, &_nameSize, &nameBytes);
	// copy the location
	unsigned int locationBytes;
	_location = CopyUTF8String(stream, &_locationSize, &locationBytes);

	stream->Seek(_size - 4 - 4 - 4 - nameBytes - locationBytes);	// 4 is for initial size, 4 for for "url " type, 4 for version & flags, locationBytes for the bytes read.

	return SUCCESS;
}

void UrnBox::Print()
{
	printf("Box Type: Urn.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	if (_name)
	{
		// TODO : maybe convert to something more printer friendly for UTF-8? At least ASCII characters will show up correctly...
		printf("\tname: %s.\r\n", _name);
	}

	if (_location)
	{
		// TODO : maybe convert to something more printer friendly for UTF-8? At least ASCII characters will show up correctly...
		printf("\tlocation: %s.\r\n", _location);
	}

}


char * UrnBox::CopyUTF8String(MPEG4Player::MPEG4FileStream *stream, unsigned int * bytesAllocated, unsigned int * copiedBytes)
{
	unsigned int buffSize = 256;
	char * buff = (char *) malloc (buffSize * sizeof(char));

	unsigned int i = 0;
	while (TRUE)
	{
		char a;
		char *b;

		unsigned int numBytesRead;

		if(buff && i == buffSize - 1)
		{
			buffSize = buffSize * 2;
			buff = (char *) realloc (buff, buffSize * sizeof(char));
		}

		if (buff)
			b = buff + i;
		else
			b = &a;

		stream->ReadBytes(b, 1, &numBytesRead);

		if (! (*b))
			break;

		i++;
	}

	*bytesAllocated = buffSize;
	*copiedBytes = i;
	return buff;
}


UrnBox::~UrnBox()
{
	if (_name)
		free(_name);
	_name = NULL;
	_nameSize = 0;

	if (_location)
		free(_location);
	_location = NULL;
	_locationSize = 0;
}

} /* namespace MPEG4Player */
