/*
 * FullBox.h
 *
 * Multiple boxes (mvhd, etc...) extend FullBox type.
 *
 *
 */

#ifndef FULLBOX_H_
#define FULLBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class FullBox : protected BoxBase
{
public:
	FullBox();
	virtual ~FullBox();
	void Print(){};

protected:
	FUNC_RES ParseVersionFlags(MPEG4FileStream *stream);
	unsigned int _version;
	unsigned int _flags;
};

} /* namespace MPEG4Player */
#endif /* FULLBOX_H_ */
