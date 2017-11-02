/*
 * SgpdBox.h
 *
 *	Sample Table Box
 *
 */

#ifndef SGPDBOX_H_
#define SGPDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SgpdBox : protected FullBox
{
public:
	SgpdBox();
	virtual ~SgpdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);
	void Print();

};

} /* namespace MPEG4Player */
#endif /* SGPDBOX_H_ */
