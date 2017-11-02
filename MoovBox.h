/*
 * MoovBox.h
 * Movie Box for the MP4 file.
 *
 *
 */

#ifndef MOOVBOX_H_
#define MOOVBOX_H_

#include "ContainerBox.h"

namespace MPEG4Player
{

class MoovBox : protected ContainerBox
{
public:
	MoovBox();
	virtual ~MoovBox();

	void Print();
};

} /* namespace MPEG4Player */
#endif /* MOOVBOX_H_ */
