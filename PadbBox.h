/*
 * PadbBox.h
 *
 * Padding Bits box.
 *
 */

#ifndef PADBBOX_H_
#define PADBBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class PadbBox : protected FullBox
{
public:
	PadbBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~PadbBox();
private:
	unsigned int _sampleCount;						// number of samples
	unsigned int * _paddingBits;					// an array of padding bits (pad1 + pad2)
};

} /* namespace MPEG4Player */
#endif /* PADBBOX_H_ */
