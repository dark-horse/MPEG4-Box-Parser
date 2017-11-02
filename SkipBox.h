/*
 * SkipBox.h
 *
 *
 */

#ifndef SKIPBOX_H_
#define SKIPBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class SkipBox : BoxBase
{
public:
	SkipBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~SkipBox();
};

} /* namespace MPEG4Player */
#endif /* SKIPBOX_H_ */
