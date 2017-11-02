/*
 * AvccBox.cpp
 *
 *
 */

#include "AvccBox.h"
#include "Utils.h"

namespace MPEG4Player
{

AvccBox::AvccBox()
{
	_boxType = BoxBase::AvccBox;
	_AVCDecoderConfigurationRecordParsed = FALSE;
}

FUNC_RES AvccBox::AVCDecoderConfigurationRecord::Parse(MPEG4FileStream *stream)
{
	char oneChar[1];
	unsigned int a;

	stream->ReadBytes(oneChar, 1, &a);
	_configurationVersion = (unsigned char) oneChar[0];

	stream->ReadBytes(oneChar, 1, &a);
	_AVCProfileIndication = (unsigned char) oneChar[0];

	stream->ReadBytes(oneChar, 1, &a);
	_profileCompatibility = (unsigned char) oneChar[0];

	stream->ReadBytes(oneChar, 1, &a);
	_AVCLevelIndication = (unsigned char) oneChar[0];

	stream->ReadBytes(oneChar, 1, &a);
	_lengthMinus1 = (unsigned char) oneChar[0];
	_lengthMinus1 &= 0x3;

	stream->ReadBytes(oneChar, 1, &a);
	_numSeqParamSets = (unsigned char) oneChar[0];
	_numSeqParamSets &= 0x1F;

	unsigned int bufSize = 128;
	char * buf = (char *) malloc (bufSize * sizeof(char));
	for (unsigned char i = 0; i < _numSeqParamSets; i ++)
	{
		char twoChars[2];
		stream->ReadBytes(twoChars, 2, &a);
		unsigned int seqParamLength = UtilsIntFromTwoChars(twoChars);
		if (seqParamLength > bufSize)
		{
			bufSize = seqParamLength;
			buf = (char *) malloc (bufSize * sizeof(char));
		}
		stream->ReadBytes(buf, bufSize, &a);
		unsigned int seqParamSetOffset;
		if (i < AvccBox::AVCDecoderConfigurationRecord::SeqParamSetBuffSize)
		{
			_seqParamSetBuff[i] = SeqParamSet();
			_seqParamSetBuff[i].Parse(buf, 0, &seqParamSetOffset);
		}
		else
		{
			_addSeqParamSetBuff[i - AvccBox::AVCDecoderConfigurationRecord::SeqParamSetBuffSize] = SeqParamSet();
			_addSeqParamSetBuff[i - AvccBox::AVCDecoderConfigurationRecord::SeqParamSetBuffSize].Parse(buf, 0, &seqParamSetOffset);
		}
	}

	stream->ReadBytes(oneChar, 1, &a);
	_numPicParamSets = (unsigned char) oneChar[0];

	for (unsigned char i = 0; i < _numPicParamSets; i ++)
	{
		char twoChars[2];
		stream->ReadBytes(twoChars, 2, &a);
		unsigned int picParamLength = UtilsIntFromTwoChars(twoChars);
		if (picParamLength > bufSize)
		{
			bufSize = picParamLength;
			buf = (char *) malloc (bufSize * sizeof(char));
		}
		stream->ReadBytes(buf, bufSize, &a);
		unsigned int picParamSetOffset;
		if (i < AvccBox::AVCDecoderConfigurationRecord::PicParamSetBuffSize)
		{
			_picParamSetBuff[i] = PicParamSet();
			_picParamSetBuff[i].Parse(buf, 0, &picParamSetOffset);
		}
		else
		{
			_addPicParamSetBuff[i - AvccBox::AVCDecoderConfigurationRecord::PicParamSetBuffSize] = PicParamSet();
			_addPicParamSetBuff[i - AvccBox::AVCDecoderConfigurationRecord::PicParamSetBuffSize].Parse(buf, 0, &picParamSetOffset);
		}
	}

	return SUCCESS;
}

FUNC_RES AvccBox::Parse(MPEG4FileStream *stream)
{
	_AVCDecoderConfRec = AVCDecoderConfigurationRecord();

	_AVCDecoderConfRec.Parse(stream);

	_AVCDecoderConfigurationRecordParsed = TRUE;
	return SUCCESS;
}


AvccBox::~AvccBox()
{
	_AVCDecoderConfigurationRecordParsed = FALSE;
}

} /* namespace MPEG4Player */
