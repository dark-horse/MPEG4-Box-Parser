/*
 * StdpBox.cpp
 *
 *
 */

#include "StdpBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

StdpBox::StdpBox()
{
	_boxType = BoxBase::StdpBox;
	_priorities = NULL;
}

FUNC_RES StdpBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];
	char twoChars[2];

	// read entry count.
	stream->ReadBytes(fourChars, 4, &a);
	_priorityCount = UtilsIntFromFourChars(fourChars);
	if (_priorityCount == 0)
		return SUCCESS;
	
	_priorities = (unsigned int *) malloc(sizeof(unsigned int) * _priorityCount * 2);
	
	for (unsigned int i = 0; i < _priorityCount; i++)
	{
		// chunk Offsets
		stream->ReadBytes(twoChars, 2, &a);
		_priorities[i] = UtilsIntFromTwoChars(twoChars);
	}

	return SUCCESS;
}

void StdpBox::Print()
{
	printf("Box Type: Stdp.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tsample count: 0x%08X.\r\n", _priorityCount);
	if (_priorities == NULL)
		return;
	printf("\tpriorities:\r\n");
	for (unsigned int i = 0; i < _priorityCount; i++)
	{
		printf("\t\tpriority %d: priority 0x%08X.\r\n", i, _priorities[i]);
	}
}

StdpBox::~StdpBox()
{
	if (_priorities)
	{
		free(_priorities);
	}
	_priorities = NULL;
}

} /* namespace MPEG4Player */
