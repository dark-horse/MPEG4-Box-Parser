/*
 * Co64Box.h
 *
 * Chunk Large offset box.
 *
 */

#ifndef CO64BOX_H_
#define CO64BOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class Co64Box : protected FullBox
{
public:
	Co64Box();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~Co64Box();
private:
	unsigned int _entryCount;						// number of samples
	unsigned long long int * _chunkOffsets;		// an array of chunk offsets
};

} /* namespace MPEG4Player */
#endif /* STCOBOX_H_ */
