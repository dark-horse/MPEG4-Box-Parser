/*
 * PicParamSet.h
 *
 * The picture parameter set.
 *
 */

#ifndef PICPARAMSET_H_
#define PICPARAMSET_H_

#include "MPEG4Player.h"

namespace MPEG4Player
{

class PicParamSet
{
public:
	PicParamSet();
	virtual ~PicParamSet();

	FUNC_RES Parse(char *buf, unsigned int offset, unsigned int *updatedOffset);

	inline unsigned char GetPicParamSetId() { return _picParamSetId;}
	inline unsigned char GetSeqParamSetId() { return _seqParamSetId;}
	inline bool GetEntropyCodedFlag() { return _entropyCodedFlag;}
	inline bool GetPicOrderPresentFlag() { return _picOrderPresentFlag;}

	inline unsigned char GetNumSliceGroupsMinus1() { return _numSliceGroupsMinus1;}
	inline unsigned char GetSliceGroupMapType() { return _sliceGroupMapType;}

	inline unsigned int GetRunLengthMinusOne(unsigned int index)
	{
		if (index < RunLenMinusOneBuffSize)
		{
			return _runLengthMinus1Buff[index];
		}
		else
		{
			return _addRunLengthBuff[index - RunLenMinusOneBuffSize];
		}
	}

	inline unsigned int GetTopLeft(unsigned int index)
	{
		if (index < TopLeftBuffSize)
		{
			return _topLeftBuff[index];
		}
		else
		{
			return _addTopLeftBuff[index - TopLeftBuffSize];
		}
	}

	inline unsigned int GetBottomRight(unsigned int index)
	{
		if (index < BottomRightBuffSize)
		{
			return _bottomRightBuff[index];
		}
		else
		{
			return _addBottomRightBuff[index - BottomRightBuffSize];
		}
	}

	inline bool GetSliceGroupChangeDirFlag() { return _sliceGroupChangeDirFlag;}
	inline unsigned int GetSliceGroupRateChangeMinus1() { return _sliceGroupRateChangeMinus1;}
	inline unsigned int GetPicSizeInMapUnitsMinus1() { return _picSizeInMapUnitsMinus1;}

	inline unsigned char GetSliceGroupId(unsigned int index)
	{
		if (index < SliceGroupIDBuffSize)
		{
			return _sliceGroupIDBuff[index];
		}
		else
		{
			return _addSliceGroupIDBuff[index - SliceGroupIDBuffSize];
		}
	}


	inline unsigned char GetNumRefIdxL0Minus1() { return _numRefIdxL0Minus1;}
	inline unsigned char GetNumRefIdxL1Minus1() { return _numRefIdxL1Minus1;}
	inline bool GetWeightedPredFlag() { return _weightedPredFlag;}
	inline signed char GetPicInitQPMinus26() { return _picInitQPMinus26;}
	inline signed char GetPicInitQSMinus26() { return _picInitQSMinus26;}
	inline signed char GetChromaQPIndexOffset() { return _chromaQPIndexOffset;}
	inline bool GetDeblockingFilterControlPresentFlag() { return _deblockingFilterControlPresentFlag;}
	inline bool GetConstrainedIntraPredFlagg() { return _constrainedIntraPredFlag;}
	inline bool GetRedundantPicCntPresentFlag() { return _redundantPicCntPresentFlag;}

private:
	unsigned char _picParamSetId;				// pic param set that is referred to in the slide header.
	unsigned char _seqParamSetId;				// the active sequence parameter set.
	bool _entropyCodedFlag;						// which entropy decoded method is to be applied for syntax elements (page 69 in the manual)
	bool _picOrderPresentFlag;					// 1=pic order count related syntax elements are present in the slice header as per subclause 7.3.3
	unsigned char _numSliceGroupsMinus1;		// number of slice groups for a picture
	unsigned char _sliceGroupMapType;			// mapping of slice group map units to slice groups (page 69 in the manual).


	// _runLengthMinus1
	static const unsigned int RunLenMinusOneBuffSize = 16;
	unsigned int _runLengthMinus1Buff[RunLenMinusOneBuffSize];
	unsigned int *_addRunLengthBuff;

	// top left
	static const unsigned int TopLeftBuffSize = 16;
	unsigned int _topLeftBuff[TopLeftBuffSize];
	unsigned int *_addTopLeftBuff;

	// bottom right
	static const unsigned int BottomRightBuffSize = 16;
	unsigned int _bottomRightBuff[BottomRightBuffSize];
	unsigned int *_addBottomRightBuff;

	bool _sliceGroupChangeDirFlag;				// identifies the refined map type when slice group map type is 3, 4, or 5;
	unsigned int _sliceGroupRateChangeMinus1;	// the multiple in number of slice group map units by which the size of a slice group can change from one pic to next.
	unsigned int _picSizeInMapUnitsMinus1;		// number of slice group map units in the picture

	// slice group id
	static const unsigned int SliceGroupIDBuffSize = 16;
	unsigned char _sliceGroupIDBuff[SliceGroupIDBuffSize];
	unsigned char *_addSliceGroupIDBuff;

	unsigned char _numRefIdxL0Minus1;			// page 69
	unsigned char _numRefIdxL1Minus1;			// page 69
	bool _weightedPredFlag;						// 1: weigthed prediction shall be applied to P and SP slices
	unsigned char _weightedBiPredIdc;			// page 69
	signed char _picInitQPMinus26;				// initial value minus 26 of the SliceQPY for each slice
	signed char _picInitQSMinus26;				// initial value minus 26 of the SliceQSY for all macroblocks in SP or SI slices.
	signed char _chromaQPIndexOffset;			// offset that shall be added to QPY and QSY for addressing the table of QPC values.
	bool _deblockingFilterControlPresentFlag;	// 1: set of syntax elements controlling the characteristics of the deblocking filter is present in the slice header.
	bool _constrainedIntraPredFlag;				// page 69 +70
	bool _redundantPicCntPresentFlag;			// page 69 + 70

};

} /* namespace MPEG4Player */
#endif /* PICPARAMSET_H_ */
