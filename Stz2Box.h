/*
 * Stz2Box.h
 *
 *
 */

#ifndef STZ2BOX_H_
#define STZ2BOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class Stz2Box : protected FullBox
{
public:
	Stz2Box();
	virtual ~Stz2Box();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
	unsigned int _fieldSize;									// _fieldSize can be 4, 8, or 16;
	static const unsigned int SampleSizeTblSize = 32;			// store at most 32 field size samples
	unsigned int _samples[SampleSizeTblSize];
	unsigned int _numSamples;									// how many samples are in this track?
};

} /* namespace MPEG4Player */
#endif /* STZ2BOX_H_ */
