/*
 * SubsBox.cpp
 *
 *
 */

#include "SubsBox.h"
#include "Utils.h"

namespace MPEG4Player
{

SubsBox::SubsBox()
{
	memset (this, 0, sizeof(SubsBox));
	_boxType = BoxBase::SubsBox;
}

FUNC_RES SubsBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);

	char oneChar, fourChars[4], twoChars[2];
	unsigned int a;
	stream->ReadBytes(fourChars, 4, &a);

	_entryCount = UtilsIntFromFourChars(fourChars);

	for (unsigned int i = 0; i < _entryCount; i++)
	{
		unsigned int sampleDelta, subSampleCount;
		stream->ReadBytes(fourChars, 4, &a);
		stream->ReadBytes(twoChars, 2, &a);
		sampleDelta = UtilsIntFromFourChars(fourChars);
		subSampleCount = UtilsIntFromTwoChars(twoChars);

		if (i < SampleTblSize)
		{
			_samples[i]._sampleDelta = sampleDelta;
			_samples[i]._subSampleCount = subSampleCount;
			for (unsigned int j = 0; j < subSampleCount; j++)
			{
				unsigned int subSampleSize, subSamplePriority, discardable;
				if (_version == 1)
				{
					stream->ReadBytes(twoChars, 2, &a);
					subSampleSize = UtilsIntFromTwoChars(twoChars);
				}
				else
				{
					stream->ReadBytes(fourChars, 4, &a);
					subSampleSize = UtilsIntFromFourChars(fourChars);
				}

				stream->ReadBytes(&oneChar, 1, &a);
				twoChars[0] = oneChar; twoChars[1] = '\0';
				subSamplePriority = UtilsIntFromTwoChars(twoChars);

				stream->ReadBytes(&oneChar, 1, &a);
				twoChars[0] = oneChar; twoChars[1] = '\0';
				discardable = UtilsIntFromTwoChars(twoChars);

				// read the reserved 4 bytes
				stream->ReadBytes(fourChars, 4, &a);

				if (j < SampleEntry::SubSampleTblSize)
				{
					SubSampleEntry sse = _samples[i]._subSamples[j];
					sse._subSampleSize = subSampleSize;
					sse._subSamplePriority = subSamplePriority;
					sse._discardable = discardable;
				}
			}
		}
	}

	return SUCCESS;
}

void SubsBox::Print()
{
	printf("Box Type: Subs.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);

	for (unsigned int i = 0; i < _entryCount && i < SampleTblSize; i++)
	{
		printf("\t\tsample: 0x%08X:\r\n", i);
		printf("\t\t\tsample Delta: 0x%08X:\r\n", _samples[i]._sampleDelta);
		printf("\t\t\tsub sample count: 0x%08X:\r\n", _samples[i]._subSampleCount);
		for (unsigned int j = 0; j < _samples[i]._subSampleCount && j < SampleEntry::SubSampleTblSize; j++)
		{
			printf("\t\t\tSub sample: 0x%08X:\r\n", j);
			_samples[i]._subSamples[j].Print();
		}
	}
}

SubsBox::~SubsBox()
{
}

} /* namespace MPEG4Player */
