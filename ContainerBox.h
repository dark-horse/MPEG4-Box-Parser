/*
 * ContainerBox.h
 *
 * Container boxes (MOOV, TRAK, MDIA, EDTS, MINF, DINF)
 *
 */

#ifndef CONTAINERBOX_H_
#define CONTAINERBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class ContainerBox : protected BoxBase
{
public:
	ContainerBox();
	virtual ~ContainerBox();

	// Parsing
	FUNC_RES ParseBox(MPEG4FileStream *stream);
	void GetChildren(BoxBase *** boxList, int * numBoxes);

protected:
	int _numBoxes;						// the number of boxes inside the moov box.
	int _allocBoxListSize;				// the size of box list array
	BoxBase ** _boxList;				// an array of pointers to boxes
};

} /* namespace MPEG4Player */
#endif /* CONTAINERBOX_H_ */
