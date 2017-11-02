/*
 * MfhdBox.h
 *
 * Movie Fragment Header box.
 *
 */

#ifndef MFHDBOX_H_
#define MFHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class MfhdBox : protected FullBox
{
public:
	MfhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~MfhdBox();
private:
	unsigned int _sequenceNumber;
};

} /* namespace MPEG4Player */
#endif /* MFHDBOX_H_ */
