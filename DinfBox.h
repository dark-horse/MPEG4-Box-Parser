/*
 * DinfBox.h
 *
 *	Data Information Container Box
 *
 */

#ifndef DINFBOX_H_
#define DINFBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class DinfBox : protected ContainerBox
{
public:
	DinfBox();
	virtual ~DinfBox();
	void Print();
};

} /* namespace MPEG4Player */
#endif /* DINFBOX_H_ */
