/*
 * M4dsBox.h
 *
 * MPEG4 Descriptor Box
 *
 */

#ifndef M4DSBOX_H_
#define M4DSBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class M4dsBox : protected BoxBase
{
public:
	M4dsBox();
	virtual ~M4dsBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
};


} /* namespace MPEG4Player */
#endif /* M4DSBOX_H_ */
