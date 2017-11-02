/*
 * SeqParamSet.h
 *
 *
 */

#ifndef SEQPARAMSET_H_
#define SEQPARAMSET_H_

#include "MPEG4Player.h"
#include "MPEG4FileStream.h"
#include "VuiParams.h"

namespace MPEG4Player
{

class SeqParamSet
{
public:
	SeqParamSet();
	FUNC_RES Parse(char *buf, unsigned int offset, unsigned int *updatedOffset);
	virtual ~SeqParamSet();

	int GetOffsetForRefFrameBuf(unsigned int index);

	inline unsigned char GetProfileIDC() { return _profileIDC; }
	inline bool GetConstraintSet0() { return _constraintSet0; }
	inline bool GetConstraintSet1() { return _constraintSet1; }
	inline bool GetConstraintSet2() { return _constraintSet2; }
	inline unsigned char GetLevelIDC() { return _levelIDC; }
	inline unsigned char GetSeqParamSetID() { return _seqParamSetID; }
	inline unsigned char GetLog2MaxFrameNumMinus4() { return _log2MaxFrameNumMinus4; }
	inline unsigned char GetPicOrderCntType() { return _picOrderCntType; }
	inline unsigned char GetLog2MaxPicOrderCntLsbMinus4() { return _log2MaxPicOrderCntLsbMinus4; }
	inline bool GetDeltaPicOrderAlwaysZeroFlag() { return _deltaPicOrderAlwaysZeroFlag; }
	inline int GetOffsetForNonRefPic4() { return _offsetForNonRefPic; }
	inline int GetOffsetForTopToBottomField() { return _offsetForTopToBottomField; }
	inline unsigned char GetNumRefFramesInPicOrderCntCycle() { return _numRefFramesInPicOrderCntCycle; }
	inline unsigned char GetNumRefFrames() { return _numRefFrames; }
	inline bool GetGapsInFrameNumValueAllowedFlag() { return _gapsInFrameNumValueAllowedFlag; }
	inline unsigned int GetPicWidthInMBSMinus1() { return _picWidthInMBSMinus1; }
	inline unsigned int GetPicHeightInMBSMinus1() { return _picHeightInMBSMinus1; }
	inline bool GetFramMBSOnlyFlag() { return _framMBSOnlyFlag; }
	inline bool GetMBAdaptiveFrameFieldFlag() { return _mbAdaptiveFrameFieldFlag; }
	inline bool GetDirect8x8InferenceFlag() { return _direct8x8InferenceFlag; }
	inline bool GetFrameCroppingFlag() { return _frameCroppingFlag; }
	inline unsigned int GetFrameCropLeftOffset() { return _frameCropLeftOffset; }
	inline unsigned int GetFrameCropRightOffset() { return _frameCropRightOffset; }
	inline unsigned int GetFrameCropTopOffset() { return _frameCropTopOffset; }
	inline unsigned int GetFrameCropBottomOffset() { return _frameCropBottomOffset; }
	inline bool GetVuiParamsPresentFlag() { return _vuiParamsPresentFlag; }
	inline VuiParams GetVuiParams() { return _vuiParams; }
private:
	// member variables
	unsigned char _profileIDC;					// profile to which this bitstream conforms
	bool _constraintSet0;						// constraint set in clause A.2.1?
	bool _constraintSet1;						// constraint set in clause A.2.2?
	bool _constraintSet2;						// constraint set in clause A.2.3?
	unsigned char _levelIDC;					// level to which bitstream conforms
	unsigned char _seqParamSetID;				// ID for a sequence of parameters that apply to coded video sequences
	unsigned char _log2MaxFrameNumMinus4;		// Max Frame Num
	unsigned char _picOrderCntType;				// method to decode picture order count
	unsigned char _log2MaxPicOrderCntLsbMinus4;	// Max Pic Order Cnt Lsb
	bool _deltaPicOrderAlwaysZeroFlag;			// if true, then delta_pic_order_cnt in not in the slice header - assumed to be 0
	int _offsetForNonRefPic;					// calculate the picture order count of a non-reference picture
	int _offsetForTopToBottomField;				// calculate the picture order count of a bottom field in a frame
	unsigned char _numRefFramesInPicOrderCntCycle;// used for decoding process for picture order count as in 8.2.1

	// offset for offset for ref frame.
	// _numRefFramesInPicOrderCntCycle can be between 0 & 255.
	// This field is coded in Exp-Golomb; Exp-Golomb is more efficient than 8 bits only when it stores less
	// than 14. So start with a buffer that holds 16 num ref frames - this is what _offsetForRefFrameBuf is for.
	// And grow the buffer if needed - this is what _allocRefFrameExtBuff is for.
	static const unsigned int NumRefFrameBufSize = 16;
	int _offsetForRefFrameBuf[NumRefFrameBufSize];
	int *_allocOffsetForRefFrameBuf;

	unsigned char _numRefFrames;				// max no. frames that may be used for inter prediction of any picture in the sequence.
	bool _gapsInFrameNumValueAllowedFlag;		// as per subclause 7.4.3
	unsigned int _picWidthInMBSMinus1;			// width of decoded pic in units of macroblocks. Minus 1.
	unsigned int _picHeightInMBSMinus1;			// height of decoded pic in units of macroblocks. Minus 1.
	bool _framMBSOnlyFlag;						// 0: pic = coded fields / frames. 1: pic = only frame macroblocks.
	bool _mbAdaptiveFrameFieldFlag;				// 0: no switching between frames & field macroblocks. 1: possible switching.
	bool _direct8x8InferenceFlag;				// subclause 8.4.1.2
	bool _frameCroppingFlag;					// 0: frame cropping offset params not present. 1: the opposite.
	unsigned int _frameCropLeftOffset;
	unsigned int _frameCropRightOffset;
	unsigned int _frameCropTopOffset;
	unsigned int _frameCropBottomOffset;
	bool _vuiParamsPresentFlag;					// whether or not the sequence params set include vui parameters.
	VuiParams _vuiParams;						// the vui parameters struct.
};

} /* namespace MPEG4Player */
#endif /* SEQPARAMSET_H_ */
