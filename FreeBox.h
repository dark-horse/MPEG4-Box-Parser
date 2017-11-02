/*
 * FreeBox.h
 *
 *
 */

#ifndef FREEBOX_H_
#define FREEBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class FreeBox : BoxBase
{
public:
	FreeBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~FreeBox();
};

} /* namespace MPEG4Player */
#endif /* FREEBOX_H_ */
