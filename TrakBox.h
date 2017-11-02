/*
 * TrakBox.h
 *
 * Container box for a single track in the presentation.
 *
 */

#ifndef TRAKBOX_H_
#define TRAKBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class TrakBox : protected ContainerBox
{
public:
	TrakBox();
	virtual ~TrakBox();

	void Print();
};

} /* namespace MPEG4Player */
#endif /* TRAKBOX_H_ */
