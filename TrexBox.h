/*
 * TrexBox.h
 *
 * Track Extends box.
 *
 */

#ifndef TREXBOX_H_
#define TREXBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class TrexBox : protected FullBox
{
public:
	TrexBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~TrexBox();
private:
	unsigned int _trackID;
	unsigned int _defaultSampleDescriptionIndex;
	unsigned int _defaultSampleDuration;
	unsigned int _defaultSampleSize;
	unsigned int _defaultSampleFlags;
};

} /* namespace MPEG4Player */
#endif /* TREXBOX_H_ */
