/*
 * PadbBox.cpp
 *
 *
 */

#include "PadbBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

PadbBox::PadbBox()
{
	_boxType = BoxBase::PadbBox;
	_paddingBits = NULL;
}

FUNC_RES PadbBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];
	char oneChar;

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_sampleCount = UtilsIntFromFourChars(fourChars);
	if (_sampleCount == 0)
		return SUCCESS;
	
	_paddingBits = (unsigned int *) malloc(sizeof(unsigned int) * _sampleCount * 2);
	
	for (unsigned int i = 0; i < _sampleCount; i++)
	{
		// chunk Offsets
		stream->ReadBytes(&oneChar, 1, &a);
		_paddingBits[i*2]   = (((unsigned int) oneChar) >> 4) & 0x00000008;
		_paddingBits[i*2+1] = (((unsigned int) oneChar))      & 0x00000008;
	}

	return SUCCESS;
}

void PadbBox::Print()
{
	printf("Box Type: Padb.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	printf("\tsample count: 0x%08X.\r\n", _sampleCount);
	if (_paddingBits == NULL)
		return;
	printf("\tpadding Bits:\r\n");
	for (unsigned int i = 0; i < _sampleCount; i++)
	{
		printf("\t\tsample %d: pad1 0x%08X\tpad2 0x%08X.\r\n", i, _paddingBits[i*2], _paddingBits[i*2]+1);
	}
}

PadbBox::~PadbBox()
{
	if (_paddingBits)
	{
		free(_paddingBits);
	}
	_paddingBits = NULL;
}

} /* namespace MPEG4Player */
