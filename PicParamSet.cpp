/*
 * PicParamSet.cpp
 *
 *
 */

#include "PicParamSet.h"
#include "Utils.h"

namespace MPEG4Player
{

PicParamSet::PicParamSet()
{
	memset (this, 0, sizeof(PicParamSet));
}

FUNC_RES PicParamSet::Parse(char *buf, unsigned int offset, unsigned int *updatedOffset)
{
	unsigned int byteOffset, bitOffset;

	_picParamSetId = (unsigned char) ParseUev(buf, offset, &offset);
	_seqParamSetId = (unsigned char) ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_entropyCodedFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_picOrderPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	_numSliceGroupsMinus1 = (unsigned char) ParseUev(buf, offset, &offset);

	if (_numSliceGroupsMinus1)
	{
		_sliceGroupMapType = (unsigned char) ParseUev(buf, offset, &offset);

		if(_sliceGroupMapType == 0)
		{
			if (_numSliceGroupsMinus1 + 1 > PicParamSet::RunLenMinusOneBuffSize)
				_addRunLengthBuff = (unsigned int *) malloc ((_numSliceGroupsMinus1 + 1 - PicParamSet::RunLenMinusOneBuffSize)*sizeof(unsigned int));
			for (unsigned char i = 0; i <= _numSliceGroupsMinus1; i++)
			{
				unsigned int a = ParseUev(buf, offset, &offset);
				if (i<PicParamSet::RunLenMinusOneBuffSize)
				{
					_runLengthMinus1Buff[i] = a;
				}
				else
				{
					_addRunLengthBuff[PicParamSet::RunLenMinusOneBuffSize-i] = a;
				}
			}
		}
		else if (_sliceGroupMapType == 2)
		{
			if (_numSliceGroupsMinus1 + 1 > PicParamSet::TopLeftBuffSize)
				_addTopLeftBuff = (unsigned int *) malloc ((_numSliceGroupsMinus1 + 1 - PicParamSet::TopLeftBuffSize)*sizeof(unsigned int));

			if (_numSliceGroupsMinus1 + 1 > PicParamSet::BottomRightBuffSize)
				_addBottomRightBuff = (unsigned int *) malloc ((_numSliceGroupsMinus1 + 1 - PicParamSet::BottomRightBuffSize)*sizeof(unsigned int));
			for (unsigned char i = 0; i < _numSliceGroupsMinus1; i ++)
			{
				unsigned int topLeft = ParseUev(buf, offset, &offset);
				unsigned int bottomRight = ParseUev(buf, offset, &offset);

				if (i < PicParamSet::TopLeftBuffSize)
				{
					_topLeftBuff[i] = topLeft;
				}
				else
				{
					_addTopLeftBuff[i - PicParamSet::TopLeftBuffSize] = topLeft;
				}

				if (i < PicParamSet::BottomRightBuffSize)
				{
					_bottomRightBuff[i] = bottomRight;
				}
				else
				{
					_addBottomRightBuff[i - PicParamSet::BottomRightBuffSize] = bottomRight;
				}
			}
		}
		else if (_sliceGroupMapType == 3 || _sliceGroupMapType == 4 || _sliceGroupMapType == 5)
		{
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8
			_sliceGroupChangeDirFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
			offset ++;

			_sliceGroupRateChangeMinus1 = ParseUev(buf, offset, &offset);
		}
		else if (_sliceGroupMapType == 6)
		{
			_picSizeInMapUnitsMinus1 = ParseUev(buf, offset, &offset);

			if (_picSizeInMapUnitsMinus1 + 1 > PicParamSet::SliceGroupIDBuffSize)
				_addSliceGroupIDBuff = (unsigned char *) malloc ((_picSizeInMapUnitsMinus1 + 1 - PicParamSet::SliceGroupIDBuffSize)*sizeof(unsigned char));

			for (unsigned int i = 0; i < _picSizeInMapUnitsMinus1; i ++)
			{
				// shortcut = assume that takes at most 4 bits to code the slice group id
				unsigned char a = '\0';
				int bitsRequired;
				if (_numSliceGroupsMinus1 + 1 > 8)
					bitsRequired = 4;
				else if (_numSliceGroupsMinus1 + 1 > 4)
					bitsRequired = 3;
				else if (_numSliceGroupsMinus1 > 2)
					bitsRequired = 2;
				else
					bitsRequired = 1;

				for (int j = 0; j < bitsRequired; j++)
				{
					a = a << 1;
					byteOffset = offset >> 3;		// offset / 8
					bitOffset = offset & 0x7;		// offset % 8
					a |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
					offset ++;
				}

				if ( i < PicParamSet::SliceGroupIDBuffSize)
				{
					_sliceGroupIDBuff[i] = a;
				}
				else
				{
					_addSliceGroupIDBuff[i - PicParamSet::SliceGroupIDBuffSize] = a;
				}
			}
		}
	}

	_numRefIdxL0Minus1 = (unsigned char) ParseUev(buf, offset, &offset);
	_numRefIdxL1Minus1 = (unsigned char) ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_weightedPredFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	_weightedBiPredIdc = 0;

	for (int i = 0; i < 2; i ++)
	{
		_weightedBiPredIdc = _weightedBiPredIdc << 1;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_weightedBiPredIdc |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
	}

	_picInitQPMinus26 = (signed char) ParseSev(buf, offset, &offset);
	_picInitQSMinus26 = (signed char) ParseSev(buf, offset, &offset);
	_chromaQPIndexOffset = (signed char) ParseSev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_deblockingFilterControlPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_constrainedIntraPredFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_redundantPicCntPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	*updatedOffset = offset;
	return SUCCESS;
}


PicParamSet::~PicParamSet()
{
	if (_addRunLengthBuff)
		free (_addRunLengthBuff);
	if (_addTopLeftBuff)
		free (_addTopLeftBuff);
	if (_addBottomRightBuff)
		free(_addBottomRightBuff);
	if (_addSliceGroupIDBuff)
		free (_addSliceGroupIDBuff);
	memset (this, 0, sizeof(PicParamSet));
}

} /* namespace MPEG4Player */
