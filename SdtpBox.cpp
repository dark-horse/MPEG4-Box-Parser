/*
 * SdtpBox.cpp
 *
 *
 */

#include "SdtpBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

SdtpBox::SdtpBox()
{
	_boxType = BoxBase::SdtpBox;
	_depends = NULL;
}

FUNC_RES SdtpBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_sampleCount = UtilsIntFromFourChars(fourChars);
	if (_sampleCount == 0)
		return SUCCESS;
	
	_depends = (char *) malloc(sizeof(char) * _sampleCount);

	stream->ReadBytes(_depends, _sampleCount, &a);

	return SUCCESS;
}

void SdtpBox::Print()
{
	printf("Box Type: Stdp.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tsample count: 0x%08X.\r\n", _sampleCount);
	if (_depends == NULL)
		return;
	printf("\tdepends:\r\n");
	for (unsigned int i = 0; i < _sampleCount; i++)
	{
		printf("\t\tsample %d:", i);
		PrintDependencyInfo(_depends[i]);
		printf(".\r\n");
	}
}

void SdtpBox::PrintDependencyInfo(char dep)
{
	char a;
	
	// sample depends on bit
	a = dep & ((char) 0x30);
	if (!a)
	{
		printf (" depends on is not specified;");
	}
	else if (a == (char) 0x20)
	{
		printf(" does not depend on others;");
	}
	else if (a == (char) 0x10)
	{
		printf(" depends on others;");
	}
	
	// sample is depended on
	a = dep & ((char) 0xC);
	if (!a)
	{
		printf (" sample is depended on is not specified;");
	}
	else if (a == (char) 8)
	{
		printf (" no other samples depend on this one;");
	}
	else if (a == (char) 4)
	{
		printf (" other samples may depend on this one;");
	}
	
	// sample has redundancy bit
	a = dep &((char) 0x3);
	if (!a)
	{
		printf (" is unknown whether there is redundant coding in this sample.");
	}
	else if (a == (char) 0x2)
	{
		printf (" there is no redundant coding in this sample.");
	}
	else if (a == (char) 0x1)
	{
		printf (" there is redundant coding in this sample.");
	}
}

SdtpBox::~SdtpBox()
{
	if (_depends)
	{
		free(_depends);
	}
	_depends = NULL;
}

} /* namespace MPEG4Player */
