/*
 * HRDParams.cpp
 *
 *
 */

#include <string.h>

#include "HRDParams.h"
#include "Utils.h"

namespace MPEG4Player
{

HRDParams::HRDParams()
{
	memset (this, 0, sizeof(HRDParams));
}

FUNC_RES HRDParams::Parse(char *buf, unsigned int offset, unsigned int *updatedOffset)
{

	unsigned int byteOffset, bitOffset;

	_cpbCntMinus1 = (unsigned char) ParseUev(buf, offset, &offset);

	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	_bitRate = 0;
	for (int i = 0; i < 4; i ++)
	{
		_bitRate = _bitRate << 1;
		_bitRate |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	_cpbSizeScale = 0;
	for (int i = 0; i < 4; i ++)
	{
		_cpbSizeScale = _cpbSizeScale << 1;
		_cpbSizeScale |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	for (unsigned char i = 0; i < _cpbCntMinus1; i++)
	{
		unsigned int bitRateValueMinus1 = ParseUev(buf, offset, &offset);
		unsigned int cpbSizeValueMinus1 = ParseUev(buf, offset, &offset);
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
		bool cbrFlag = (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;

		_schedSellDXBuff[i] = SchedSellDX(bitRateValueMinus1, cpbSizeValueMinus1, cbrFlag);
	}

	_initialCPBRemovalDelayMinus1 = 0;
	byteOffset = offset >> 3;		// offset / 8
	bitOffset = offset & 0x7;		// offset % 8
	for (int i = 0; i < 5; i ++)
	{
		_initialCPBRemovalDelayMinus1 = _initialCPBRemovalDelayMinus1 << 1;
		_initialCPBRemovalDelayMinus1 |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	_cpbRemovalDelayMinus1 = 0;
	for (int i = 0; i < 5; i ++)
	{
		_cpbRemovalDelayMinus1 = _cpbRemovalDelayMinus1 << 1;
		_cpbRemovalDelayMinus1 |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	_dpbOutputDelayLengthMinus1 = 0;
	for (int i = 0; i < 5; i ++)
	{
		_dpbOutputDelayLengthMinus1 = _dpbOutputDelayLengthMinus1 << 1;
		_dpbOutputDelayLengthMinus1 |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	_timeOffsetLength = 0;
	for (int i = 0; i < 5; i ++)
	{
		_timeOffsetLength = _timeOffsetLength << 1;
		_timeOffsetLength |= (((unsigned char) buf[byteOffset]) >> bitOffset) & 0x1;
		offset ++;
		byteOffset = offset >> 3;		// offset / 8
		bitOffset = offset & 0x7;		// offset % 8
	}

	*updatedOffset = offset;

	return SUCCESS;
}



HRDParams::~HRDParams()
{
	memset (this, 0, sizeof(HRDParams));
}

} /* namespace MPEG4Player */
