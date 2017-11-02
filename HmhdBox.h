/*
 * HmhdBox.h
 *
 * Hint Media Header
 */

#ifndef HMHDBOX_H_
#define HMHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class HmhdBox : protected FullBox
{
public:
	HmhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~HmhdBox();
private:
	unsigned int _maxPDUSize;
	unsigned int _avgPDUSize;
	unsigned int _maxbitrate;
	unsigned int _avgbitrate;
};

} /* namespace MPEG4Player */
#endif /* HMHDBOX_H_ */
