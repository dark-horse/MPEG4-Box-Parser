/*
 * VuiParams.cpp
 *
 *
 */

#include "VuiParams.h"
#include "Utils.h"


namespace MPEG4Player
{

VuiParams::VuiParams()
{
	 memset (this, 0, sizeof(VuiParams));
}

FUNC_RES VuiParams::Parse(char *buf, unsigned int offset, unsigned int *updatedOffset)
{
	unsigned int byteOffset, bitOffset;
	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8

	_aspectRatioInfoPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_aspectRatioInfoPresentFlag)
	{
		_aspectRatioIDC = 0;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8

		for (int i = 0; i < 8; i ++)
		{
			_aspectRatioIDC = _aspectRatioIDC << 1;
			_aspectRatioIDC |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
			offset ++;
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8
		}

		if (_aspectRatioIDC == Extended_SAR)
		{
			// TODO: check if we need to flip the chars. Because of big-endian v. small-endian.
			_sarWidth = 0;
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8

			for (int i = 0; i < 16; i ++)
			{
				_sarWidth = _sarWidth << 1;
				_sarWidth |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
				offset ++;
				byteOffset = offset >> 3;		// offset / 8
				bitOffset = offset & 0x7;		// offset % 8
			}

			_sarHeight = 0;
			for (int i = 0; i < 16; i ++)
			{
				_sarHeight = _sarHeight << 1;
				_sarHeight |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
				offset ++;
				byteOffset = offset >> 3;		// offset / 8
				bitOffset = offset & 0x7;		// offset % 8
			}
		}
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_overscanInfoPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_overscanInfoPresentFlag)
	{
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_overscanAppropriateFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_videoSignalTypePresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if(_videoSignalTypePresentFlag)
	{
		_videoFormat = 0;
		for (int i = 0; i < 3; i++)
		{
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8
			_videoFormat = _videoFormat << 1;
			_videoFormat |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
			offset ++;
		}
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_videoFullRangeFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;

		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_colorDescriptionPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;

		if (_colorDescriptionPresentFlag)
		{
			_colorPrimaries = 0;
			for (int i = 0; i < 8; i++)
			{
				byteOffset = offset >> 3;		// offset / 8
				bitOffset = offset & 0x7;		// offset % 8
				_colorPrimaries = _colorPrimaries << 1;
				_colorPrimaries |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
				offset ++;
			}

			_transferCharacteristics = 0;
			for (int i = 0; i < 8; i++)
			{
				byteOffset = offset >> 3;		// offset / 8
				bitOffset = offset & 0x7;		// offset % 8
				_transferCharacteristics = _transferCharacteristics << 1;
				_transferCharacteristics |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
				offset ++;
			}

			_matrixCoeff = 0;
			for (int i = 0; i < 8; i++)
			{
				byteOffset = offset >> 3;		// offset / 8
				bitOffset = offset & 0x7;		// offset % 8
				_matrixCoeff = _matrixCoeff << 1;
				_matrixCoeff |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
				offset ++;
			}
		}
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_chromaLocInfoPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_chromaLocInfoPresentFlag)
	{
		_chromaSampleLocTypeTopField = (unsigned char) ParseUev(buf, offset, &offset);
		_chromaSampleLocTypeBottomField = (unsigned char) ParseUev(buf, offset, &offset);
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_timingInfoPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_timingInfoPresentFlag)
	{
		_numUnitsInTick = 0;
		for (int i = 0; i < 32; i++)
		{
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8
			_numUnitsInTick = _numUnitsInTick << 1;
			_numUnitsInTick |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
			offset ++;
		}

		_timeScale = 0;
		for (int i = 0; i < 32; i++)
		{
			byteOffset = offset >> 3;		// offset / 8
			bitOffset = offset & 0x7;		// offset % 8
			_timeScale = _timeScale << 1;
			_timeScale |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
			offset ++;
		}

		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_fixedFrameRateFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_nalHRDParamsPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_nalHRDParamsPresentFlag)
	{
		_hrdParams.Parse(buf, offset, &offset);
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_vclHRDParamsPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_vclHRDParamsPresentFlag)
	{
		_vclHRDParams.Parse(buf, offset, &offset);
	}

	if (_nalHRDParamsPresentFlag || _vclHRDParamsPresentFlag)
	{
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_lowDelayHRDFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
	}

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_picStructPresentFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_bitstreamRestrictFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
	offset ++;

	if (_bitstreamRestrictFlag)
	{
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		_motionVectorsOverPicBoundariesFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;

		_maxBytesPerPicDenom = (unsigned char) ParseUev(buf, offset, &offset);
		_maxBitsPerMbDenom = (unsigned char) ParseUev(buf, offset, &offset);
		_log2MaxMVLengthHoriz = (unsigned char) ParseUev(buf, offset, &offset);
		_log2MaxMVLengthVert = (unsigned char) ParseUev(buf, offset, &offset);
		_numReorderFrames = ParseUev(buf, offset, &offset);
		_maxDecFrameBuffering = ParseUev(buf, offset, &offset);
	}

	*updatedOffset = offset;
	return SUCCESS;
}

VuiParams::~VuiParams()
{
	 memset (this, 0, sizeof(VuiParams));
}

} /* namespace MPEG4Player */
