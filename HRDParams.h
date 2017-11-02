/*
 * HRDParams.h
 *
 *
 */

#ifndef HRDPARAMS_H_
#define HRDPARAMS_H_

#include "MPEG4FileStream.h"

namespace MPEG4Player
{

class HRDParams
{
public:
	HRDParams();
	virtual ~HRDParams();
	FUNC_RES Parse(char *buf, unsigned int offset, unsigned int *updatedOffset);

	class SchedSellDX
	{
	public:
		SchedSellDX() {}
		SchedSellDX(unsigned int bitRateValueMinus1, unsigned int cpbSizeValueMinus1, bool cbrFlag)
		{
			_bitRateValueMinus1 = bitRateValueMinus1;
			_cpbSizeValueMinus1 = cpbSizeValueMinus1;
			_cbrFlag = cbrFlag;
		}
		virtual ~SchedSellDX() {memset(this, 0, sizeof(SchedSellDX));}

		unsigned char GetBitRateValueMinus1() {return _bitRateValueMinus1;}
		unsigned char GetCPBSizeValueMinus1() {return _cpbSizeValueMinus1;}
		bool GetCBRFlag() {return _cbrFlag;}

	private:
		unsigned int _bitRateValueMinus1;
		unsigned int _cpbSizeValueMinus1;
		bool _cbrFlag;
	};

	inline unsigned char GetCPBCntMinus1() {return _cpbCntMinus1;}
	inline unsigned char GetBitRate() {return _bitRate;}
	inline unsigned char GetCPBSizeScale() {return _cpbSizeScale;}
	inline SchedSellDX GetSchedSellDX(int index) { return _schedSellDXBuff[index];}

	inline unsigned char GetInitialCPBRemovalDelayMinus1() {return _initialCPBRemovalDelayMinus1;}
	inline unsigned char GetCpbRemovalDelayMinus1() {return _cpbRemovalDelayMinus1;}
	inline unsigned char GetDpbOutputDelayLengthMinus1() {return _dpbOutputDelayLengthMinus1;}
	inline unsigned char GetTimeOffsetLength() {return _timeOffsetLength;}

private:
	unsigned char _cpbCntMinus1;		// the number of alternative CPB specifications in bitstream (????)
	unsigned char _bitRate;				// maximum input bit rate
	unsigned char _cpbSizeScale;		// CPB size of the ith CPB

	// SchedSellDx stuff
	static const int SchedSellDXBuffSize = 32;
	SchedSellDX _schedSellDXBuff[SchedSellDXBuffSize];

	unsigned char _initialCPBRemovalDelayMinus1;	// length in bits of initial cbp removal delay
	unsigned char _cpbRemovalDelayMinus1;			// length in bits of cpb removal delay syntax element
	unsigned char _dpbOutputDelayLengthMinus1;		// length in bits of dpb output delay length syntax element
	unsigned char _timeOffsetLength;				// length in bits of time offset syntax element.

};

} /* namespace MPEG4Player */
#endif /* HRDPARAMS_H_ */
