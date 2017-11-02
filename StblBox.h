/*
 * StblBox.h
 *
 *
 */

#ifndef STBLBOX_H_
#define STBLBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class StblBox : protected ContainerBox
{
public:
	StblBox();
	virtual ~StblBox();

	void Print();
};

} /* namespace MPEG4Player */
#endif /* STBLBOX_H_ */
