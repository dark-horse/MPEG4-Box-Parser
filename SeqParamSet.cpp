/*
 * SeqParamSet.cpp
 *
 *
 */

#include <stdlib.h>
#include "SeqParamSet.h"
#include "Utils.h"

namespace MPEG4Player
{
SeqParamSet::SeqParamSet()
{
	memset (this, 0, sizeof(SeqParamSet));
}

FUNC_RES SeqParamSet::Parse(char *buf, unsigned int offset, unsigned int *updatedOffset)
{

	unsigned int byteOffset, bitOffset;

	_profileIDC = (unsigned char) buf[offset];
	offset += 8;

	_constraintSet0 = ((unsigned char) buf[offset]) & 0x80;
	_constraintSet1 = ((unsigned char) buf[offset]) & 0x40;
	_constraintSet2 = ((unsigned char) buf[offset]) & 0x20;
	offset += 8;

	_levelIDC = (unsigned char) buf[offset];
	offset +=8;

	_seqParamSetID = (unsigned char) ParseUev(buf, offset, &offset);

	_log2MaxFrameNumMinus4 = (unsigned char) ParseUev(buf, offset, &offset);
	offset = *updatedOffset;

	_picOrderCntType = (unsigned char) ParseUev(buf, offset, &offset);
	offset = *updatedOffset;

	if (_picOrderCntType == 0)
	{
		_log2MaxPicOrderCntLsbMinus4 = (unsigned char) ParseUev(buf, offset, &offset);
		offset = *updatedOffset;
	}
	else if (_picOrderCntType == 1)
	{
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8

		_deltaPicOrderAlwaysZeroFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;

		_offsetForNonRefPic = (unsigned char) ParseSev(buf, offset, &offset);
		_offsetForTopToBottomField = (unsigned char) ParseSev(buf, offset, &offset);
		_numRefFramesInPicOrderCntCycle = (unsigned char) ParseUev(buf, offset, &offset);

		if (_numRefFramesInPicOrderCntCycle > SeqParamSet::NumRefFrameBufSize)
		{
			_allocOffsetForRefFrameBuf = (int *) malloc ((SeqParamSet::NumRefFrameBufSize-_numRefFramesInPicOrderCntCycle) * sizeof(int));
		}

		for (unsigned int i = 0; i < _numRefFramesInPicOrderCntCycle; i ++)
		{
			int a = ParseSev(buf, offset, &offset);
			if (i < SeqParamSet::NumRefFrameBufSize)
			{
				_offsetForRefFrameBuf[i] = a;
			}
			else
			{
				_allocOffsetForRefFrameBuf[i - SeqParamSet::NumRefFrameBufSize] = a;
			}
		}
	}

	_numRefFrames = (unsigned char) ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_gapsInFrameNumValueAllowedFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	_picWidthInMBSMinus1 = ParseUev(buf, offset, &offset);
	_picHeightInMBSMinus1 = ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_framMBSOnlyFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_mbAdaptiveFrameFieldFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_direct8x8InferenceFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_frameCroppingFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;


	_frameCropLeftOffset = ParseUev(buf, offset, &offset);
	_frameCropRightOffset = ParseUev(buf, offset, &offset);
	_frameCropTopOffset = ParseUev(buf, offset, &offset);
	_frameCropBottomOffset = ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_vuiParamsPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_vuiParamsPresentFlag)
	{
		_vuiParams.Parse(buf, offset, &offset);
	}

	*updatedOffset = offset;

	return SUCCESS;
}

int SeqParamSet::GetOffsetForRefFrameBuf(unsigned int index)
{
	if (_numRefFramesInPicOrderCntCycle == 0)
		return 0;
	if (index < SeqParamSet::NumRefFrameBufSize)
	{
		return _offsetForRefFrameBuf[index];
	}
	else
	{
		return _allocOffsetForRefFrameBuf[index - SeqParamSet::NumRefFrameBufSize];
	}
}

SeqParamSet::~SeqParamSet()
{
	if (_allocOffsetForRefFrameBuf)
		free (_allocOffsetForRefFrameBuf);
	memset (this, 0, sizeof(SeqParamSet));
}

} /* namespace MPEG4Player */
