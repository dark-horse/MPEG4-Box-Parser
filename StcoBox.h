/*
 * StcoBox.h
 *
 * Chunk offset box.
 *
 */

#ifndef STCOBOX_H_
#define STCOBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StcoBox : protected FullBox
{
public:
	StcoBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~StcoBox();
private:
	unsigned int _entryCount;						// number of samples
	unsigned int * _chunkOffsets;					// an array of chunk offsets
};

} /* namespace MPEG4Player */
#endif /* STCOBOX_H_ */
