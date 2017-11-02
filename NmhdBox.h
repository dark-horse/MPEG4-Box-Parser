/*
 * NmhdBox.h
 *
 * Null Media header
 *
 */

#ifndef NMHDBOX_H_
#define NMHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class NmhdBox : protected FullBox
{
public:
	NmhdBox();
	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~NmhdBox();
};

} /* namespace MPEG4Player */
#endif /* NMHDBOX_H_ */
