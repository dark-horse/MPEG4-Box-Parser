/*
 * PdinBox.cpp
 *
 *
 */

#include "PdinBox.h"
#include "Utils.h"

namespace MPEG4Player
{

PdinBox::PdinBox()
{
	memset (this, 0, sizeof(PdinBox));
	_boxType = BoxBase::PdinBox;
}

FUNC_RES PdinBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);

	unsigned int leftToParse = _size - 4 - 4 - 4; // 4 for size, 4 for "pdin", 4 for version / flags.

	unsigned int i = 0;

	while (leftToParse > 0)
	{
		char fourChars[4];
		unsigned int numBytesRead;
		unsigned int rate;
		unsigned int initialDelay;

		stream->ReadBytes(fourChars, 4, &numBytesRead);
		rate = UtilsIntFromFourChars(fourChars);
		leftToParse -= 4;

		stream->ReadBytes(fourChars, 4, &numBytesRead);
		initialDelay = UtilsIntFromFourChars(fourChars);
		leftToParse -= 4;

		if (i < PdinBox::DownloadInfoBufferSize)
		{
			_entries[i]._rate = rate;
			_entries[i]._initialDelay = initialDelay;
		}
		_entryCount ++;
		i++;
	}

	return SUCCESS;
}


void PdinBox::Print()
{
	printf("Box Type: Pdin.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentries: %d.\r\n", _entryCount);
	if (_entryCount)
	{

		for (unsigned int i = 0; i < _entryCount && i < PdinBox::DownloadInfoBufferSize; i++)
		{
			printf("\t\tentry: %d. Rate %d Initial Delay %d.\r\n", i, _entries[i]._rate, _entries[i]._initialDelay);
		}
	}
}



PdinBox::~PdinBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
