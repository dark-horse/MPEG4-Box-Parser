/*
 * SbgpBox.h
 *
 * Sample to Group box.
 *
 */

#ifndef STGPBOX_H_
#define STGPBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SbgpBox : protected FullBox
{
public:
	SbgpBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~SbgpBox();
private:
	unsigned int _entryCount;						// number of entries
	unsigned int * _entries;						// an array of sample count / group description indexes
};

} /* namespace MPEG4Player */
#endif /* STBGBOX_H_ */
