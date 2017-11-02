/*
 * StscBox.h
 *
 *	Sample to Chunk box.
 *
 */

#ifndef STSCBOX_H_
#define STSCBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StscBox : protected FullBox
{
public:
	StscBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~StscBox();
private:
	unsigned int _entryCount;						// number of samples
	unsigned int * _chunks;							// an array of chunks
};

} /* namespace MPEG4Player */
#endif /* STSCBOX_H_ */
