/*
 * MdiaBox.h
 *
 * Media Box. Container for the objects which declare information about the media within a track
 *
 */

#ifndef MDIABOX_H_
#define MDIABOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class MdiaBox : protected ContainerBox
{
public:
	MdiaBox();
	virtual ~MdiaBox();
	void Print();
};

} /* namespace MPEG4Player */
#endif /* MDIABOX_H_ */
