/*
 * SubsBox.h
 *
 * Sub sample information box
 *
 */

#ifndef SUBSBOX_H_
#define SUBSBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SubsBox : protected FullBox
{
public:
	SubsBox();
	virtual ~SubsBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
	class SubSampleEntry
	{
	public:
		SubSampleEntry() {memset (this, 0, sizeof(SubSampleEntry));}
		unsigned int _subSampleSize;
		unsigned int _subSamplePriority;
		unsigned int _discardable;

		void Print()
		{
			printf("\t\t\t\tSubSample Entry:\r\n");
			printf("\t\t\t\t\tSubSampleSize: %x.\r\n", _subSampleSize);
			printf("\t\t\t\t\tSubSamplePriority: %x.\r\n", _subSamplePriority);
			printf("\t\t\t\t\tDiscardable: %x.\r\n", _discardable);
		}
	};
	class SampleEntry
	{
	public:
		SampleEntry() {memset (this, 0, sizeof(SampleEntry));}
		unsigned int _sampleDelta;
		static const unsigned int SubSampleTblSize = 8;							// we read up to 8 sub samples
		unsigned int _subSampleCount;											// how many subsamples this entry has
		SubSampleEntry _subSamples[SubSampleTblSize];							// 8 sub samples that we keep
	};

	static const unsigned int SampleTblSize = 8;									// we read at most 8 samples.
	unsigned int _entryCount;														// how many samples are in this box.
	SampleEntry _samples[SampleTblSize];											// 8 samples that we keep.
};

} /* namespace MPEG4Player */
#endif /* SUBSBOX_H_ */
