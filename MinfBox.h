/*
 * MinfBox.h
 *
 *	Media information container box.
 *
 */

#ifndef MINFBOX_H_
#define MINFBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class MinfBox : protected ContainerBox
{
public:
	MinfBox();
	virtual ~MinfBox();

	void Print();
};

} /* namespace MPEG4Player */
#endif /* MINFBOX_H_ */
