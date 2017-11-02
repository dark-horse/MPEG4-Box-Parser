/*
 * VmhdBox.h
 *
 *	Video media header
 *
 */

#ifndef VMHDBOX_H_
#define VMHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class VmhdBox : protected FullBox
{
public:
	VmhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();
	virtual ~VmhdBox();
private:
	unsigned int _graphicsMode;
	unsigned int _opColor[3];
};

} /* namespace MPEG4Player */
#endif /* VMHDBOX_H_ */
