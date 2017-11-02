/*
 * AvccBox.h
 *
 * Box that contains the AVC Configuration. For AVC type streams.
 *
 */

#ifndef AVCCBOX_H_
#define AVCCBOX_H_

#include "BoxBase.h"
#include "SeqParamSet.h"
#include "PicParamSet.h"

namespace MPEG4Player
{

class AvccBox : BoxBase

{
public:
	AvccBox();
	virtual ~AvccBox();

	FUNC_RES Parse(MPEG4FileStream *stream);

	class AVCDecoderConfigurationRecord
	{
	public:
		AVCDecoderConfigurationRecord() {memset(this, 0, sizeof(AVCDecoderConfigurationRecord));}
		virtual ~AVCDecoderConfigurationRecord()
		{
			if (_addSeqParamSetBuff)
				free (_addSeqParamSetBuff);
			if (_addPicParamSetBuff)
				free (_addPicParamSetBuff);
			memset (this, 0, sizeof(AVCDecoderConfigurationRecord));
		}

		FUNC_RES Parse(MPEG4FileStream *stream);

		inline unsigned char GetConfigurationVersion() { return _configurationVersion;}
		inline unsigned char GetAVCProfileIndication() { return _AVCProfileIndication;}
		inline unsigned char GetProfileCompatibility() { return _profileCompatibility;}
		inline unsigned char GetAVCLevelIndication() { return _AVCLevelIndication;}
		inline unsigned char GetLengthMinus1() { return _lengthMinus1;}

		inline unsigned char GetNumSeqParamSets() { return _numSeqParamSets;}
		inline SeqParamSet GetSeqParamSet (unsigned int index)
		{
			if (index < SeqParamSetBuffSize)
			{
				return _seqParamSetBuff[index];
			}
			else
			{
				return _addSeqParamSetBuff[index-SeqParamSetBuffSize];
			}
		}

		inline unsigned char GetNumPicParamSets() { return _numPicParamSets;}
		inline PicParamSet GetPicParamSet (unsigned int index)
		{
			if (index < PicParamSetBuffSize)
			{
				return _picParamSetBuff[index];
			}
			else
			{
				return _addPicParamSetBuff[index-PicParamSetBuffSize];
			}
		}


	private:
		unsigned char _configurationVersion;
		unsigned char _AVCProfileIndication;
		unsigned char _profileCompatibility;
		unsigned char _AVCLevelIndication;
		unsigned char _lengthMinus1;

		unsigned char _numSeqParamSets;
		static const unsigned int SeqParamSetBuffSize = 8;
		SeqParamSet _seqParamSetBuff[SeqParamSetBuffSize];
		SeqParamSet *_addSeqParamSetBuff;

		unsigned char _numPicParamSets;
		static const unsigned int PicParamSetBuffSize = 8;
		PicParamSet _picParamSetBuff[PicParamSetBuffSize];
		PicParamSet *_addPicParamSetBuff;
	};

	bool GetAVCDecoderConfigurationRecordParsed() { return _AVCDecoderConfigurationRecordParsed;}
	AVCDecoderConfigurationRecord GetAVCDecoderConfigurationRecord() {return _AVCDecoderConfRec;}

private:
	bool _AVCDecoderConfigurationRecordParsed;
	AVCDecoderConfigurationRecord _AVCDecoderConfRec;
};

} /* namespace MPEG4Player */
#endif /* AVCCBOX_H_ */
