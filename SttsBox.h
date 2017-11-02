/*
 * SttsBox.h
 *
 *	Time to Sample box.
 *
 */

#ifndef STTSBOX_H_
#define STTSBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SttsBox : protected FullBox
{
public:
	SttsBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~SttsBox();
private:
	unsigned int _entryCount;						// number of samples
	unsigned int * _samples;						// an array of sample count + sample delta
};

} /* namespace MPEG4Player */
#endif /* STTSBOX_H_ */
