/*
 * VuiParams.h
 *
 *
 */

#ifndef VUIPARAMS_H_
#define VUIPARAMS_H_

#include "HRDParams.h"

#define Extended_SAR 255

namespace MPEG4Player
{

class VuiParams
{
public:
	VuiParams();
	virtual ~VuiParams();

	FUNC_RES Parse(char *buf, unsigned int offset, unsigned int *updatedOffset);

	inline bool GetAspectRatioInfoPresentFlag() { return _aspectRatioInfoPresentFlag;}
	inline unsigned char GetAspectRatioIDC() { return _aspectRatioIDC;}
	inline unsigned char GetSarWidth() { return _sarWidth;}
	inline unsigned char GetSarHeight() { return _sarHeight;}
	inline bool GetOverscanInfoPresentFlag() { return _overscanInfoPresentFlag;}
	inline bool GetOverscanAppropriateFlag() { return _overscanAppropriateFlag;}
	inline bool GetVideoSignalTypePresentFlag() { return _videoSignalTypePresentFlag;}
	inline unsigned char GetVideoFormat() { return _videoFormat;}
	inline bool GetVideoFullRangeFlag() { return _videoFullRangeFlag;}
	inline bool GetColorDescriptionPresentFlag() { return _colorDescriptionPresentFlag;}
	inline unsigned char GetColorPrimaries() { return _colorPrimaries;}
	inline unsigned char GetTransferCharacteristics() { return _transferCharacteristics;}
	inline unsigned char GetMatrixCoeff() { return _matrixCoeff;}
	inline bool GetChromaLocInfoPresentFlag() { return _chromaLocInfoPresentFlag;}
	inline unsigned char GetChromaSampleLocTypeTopField() { return _chromaSampleLocTypeTopField;}
	inline unsigned char GetChromaSampleLocTypeBottomField() { return _chromaSampleLocTypeBottomField;}
	inline bool GetTimingInfoPresentFlag() { return _timingInfoPresentFlag;}
	inline unsigned int GetNumUnitsInTick() { return _numUnitsInTick;}
	inline unsigned int GetTimeScale() { return _timeScale;}
	inline bool GetFixedFrameRateFlag() { return _fixedFrameRateFlag;}
	inline bool GetNalHRDParamsPresentFlag() { return _nalHRDParamsPresentFlag;}
	inline HRDParams GetHRDParams() { return _hrdParams;}
	inline bool GetVCLHRDParamsPresentFlag() { return _vclHRDParamsPresentFlag;}
	inline HRDParams GetVCLHRDParams() { return _vclHRDParams;}
	inline bool GetLowDelayHRDFlag() { return _lowDelayHRDFlag;}
	inline bool GetPicStructPresentFlag() { return _picStructPresentFlag;}
	inline bool GetBitstreamRestrictFlag() { return _bitstreamRestrictFlag;}
	inline bool GetMotionVectorsOverPicBoundariesFlag() { return _motionVectorsOverPicBoundariesFlag;}
	inline unsigned char GetMaxBytesPerPicDenom() {return _maxBytesPerPicDenom;}
	inline unsigned char GetMaxBitsPerMbDenom() {return _maxBitsPerMbDenom;}
	inline unsigned char GetLog2MaxMVLengthHoriz() {return _log2MaxMVLengthHoriz;}
	inline unsigned char GetLog2MaxMVLengthVert() {return _log2MaxMVLengthVert;}
	inline unsigned int GetNumReorderFrames() {return _numReorderFrames;}
	inline unsigned int GetMxDecFrameBuffering() {return _maxDecFrameBuffering;}

private:

	bool _aspectRatioInfoPresentFlag;		// whether or not aspect ratio IDC is present or not.
	unsigned char _aspectRatioIDC;			// sample aspect ratio (resolution)
	unsigned int _sarWidth;					// ratio aspect width when  AspectRatioIDC == Extended SAR
	unsigned int _sarHeight;				// ratio aspect height when  AspectRatioIDC == Extended SAR
	bool _overscanInfoPresentFlag;			// whether or not the next flag is present.
	bool _overscanAppropriateFlag;			// 0: do not display using overscan. 1: can display using overscan
	bool _videoSignalTypePresentFlag;		// _videoXXXX below are present
	unsigned char _videoFormat;				// video format (PAL/NTSC/SECAM/MAC/
	bool _videoFullRangeFlag;				// derivation formulas (see page 270 in the manual)
	bool _colorDescriptionPresentFlag;		// whether the next three fields are present or not
	unsigned char _colorPrimaries;			// ITUR BT.709 / ITUR BT.470-2 System M/System B,G / etc...
	unsigned char _transferCharacteristics; // TX Characteristics: ITUR BT.709 / ITUR BT.470-2 System M/System B,G / etc...
	unsigned char _matrixCoeff;				// Table E-5, page 273 of the manual
	bool _chromaLocInfoPresentFlag;			// whether or not the next two fields are present
	unsigned char _chromaSampleLocTypeTopField;		// location of chroma samples.
	unsigned char _chromaSampleLocTypeBottomField;	// location of chroma samples.
	bool _timingInfoPresentFlag;			// whether or not the next two fields are present.
	unsigned int _numUnitsInTick;			// 1 clock tick = numUnitsInTick / timeScale. Page 274 in the manual.
	unsigned int _timeScale;				// number of time units that pass in one second.
	bool _fixedFrameRateFlag;				// something to do with temporal difference between consecutive pics
	bool _nalHRDParamsPresentFlag;			// whether the HRD Param Structure below is present or not
	HRDParams _hrdParams;					// the HRD Param Structure
	bool _vclHRDParamsPresentFlag;			// whether the VCL HRD Params struct below is present or not
	HRDParams _vclHRDParams;				// the VCL HRD Param Structure
	bool _lowDelayHRDFlag;					// HRD Operational mode as per Annex C.
	bool _picStructPresentFlag;				// picture timing in SEI messages is present D.2.2
	bool _bitstreamRestrictFlag;			// bitsream restriction parameters are present or not
	bool _motionVectorsOverPicBoundariesFlag;// 0:

	unsigned char _maxBytesPerPicDenom;
	unsigned char _maxBitsPerMbDenom;
	unsigned char _log2MaxMVLengthHoriz;
	unsigned char _log2MaxMVLengthVert;
	unsigned int _numReorderFrames;
	unsigned int _maxDecFrameBuffering;

};

} /* namespace MPEG4Player */
#endif /* VUIPARAMS_H_ */
