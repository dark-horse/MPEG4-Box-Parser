/*
 * EdtsBox.h
 *
 *	Edit List Container Box
 *
 */

#ifndef EDTSBOX_H_
#define EDTSBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class EdtsBox : protected ContainerBox
{
public:
	EdtsBox();
	virtual ~EdtsBox();
	void Print();
};

} /* namespace MPEG4Player */
#endif /* EDTSBOX_H_ */
