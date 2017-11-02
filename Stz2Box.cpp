/*
 * Stz2Box.cpp
 *
 *
 */

#include "Stz2Box.h"
#include "Utils.h"

namespace MPEG4Player
{
Stz2Box::Stz2Box()
{
	memset (this, 0, sizeof (TrefBox));
	_boxType = BoxBase::Stz2Box;
}

FUNC_RES Stz2Box::ParseBox(MPEG4FileStream *stream)
{
	char fourChars[4];
	unsigned int bytesLeft = _size - 4 - 4;			// 4 for size, 4 for 'stz2' token
	unsigned int a;

	stream->ReadBytes(fourChars, 4, &a);
	bytesLeft -= 4;

	fourChars[0] = fourChars[3];
	fourChars[3] = '\0';

	// _fieldSize can be one of 4 / 8 / 16.
	_fieldSize = UtilsIntFromFourChars(fourChars);

	// _numSamples
	stream->ReadBytes(fourChars, 4, &a);
	bytesLeft -= 4;

	_numSamples = UtilsIntFromFourChars(fourChars);

	unsigned int samplesRead = 0;

	while (bytesLeft && samplesRead < _numSamples)
	{
		if (samplesRead < SampleSizeTblSize)
		{
			if (_fieldSize == 4)
			{
				char oneChar, fourChars[4];
				unsigned int a;
				stream->ReadBytes(&oneChar, 1, &a);
				bytesLeft--;

				// oneChar contains two sample sizes: one sample size in the first 4 bits, the other sample size in the last 4 bits.
				// the sizes are in big endian notation....

				// get the first sample size - the one in the first 4 bits.
				fourChars[0] = oneChar; fourChars[1] = '\0'; fourChars[2] = '\0'; fourChars[3] = '\0';

				a = * reinterpret_cast<unsigned int *> (fourChars);
				a = a & 0xF0000000;
				a = a >> 28;
				_samples[samplesRead] = a;
				samplesRead ++;

				// get the second sample size - the one in the last 4 bits.
				// but only if we haven't read all the samples yet.
				if (samplesRead < _numSamples)
				{
					a = * reinterpret_cast<unsigned int *> (fourChars);
					a = a & 0x0F000000;
					a = a >> 24;
					_samples[samplesRead] = a;
					samplesRead ++;
				}
			}
			else if (_fieldSize == 8)
			{
				char oneChar, twoChars[2];
				stream->ReadBytes(&oneChar, 1, &a);
				bytesLeft--;

				twoChars[0] = oneChar;
				twoChars[1] = '\0';
				_samples[samplesRead] = UtilsIntFromTwoChars(twoChars);
				samplesRead ++;
			}
			else if (_fieldSize == 16)
			{
				char twoChars[2];
				stream->ReadBytes(twoChars, 2, &a);
				bytesLeft -= 2;
				_samples[samplesRead] = UtilsIntFromTwoChars(twoChars);
				samplesRead ++;
			}
			else
			{
				// TODO: error condition
			}
		}
		else
		{
			// we are not parsing more than 32 sample sizes
			stream->Seek(bytesLeft);
			bytesLeft = 0;
		}
	}

	return SUCCESS;
}

void Stz2Box::Print()
{
	printf("Box Type: Stz2.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tfield size: 0x%08X.\r\n", _fieldSize);
	printf("\tsample count: 0x%08X.\r\n", _numSamples);

	for (unsigned int i = 0; i < _numSamples && i < SampleSizeTblSize; i++)
	{
		printf("\tsample count: 0x%08X \tsamples size 0x%08X\r\n", i, _samples[i]);
	}
}

Stz2Box::~Stz2Box()
{
	memset (this, 0, sizeof(Stz2Box));
}

} /* namespace MPEG4Player */
