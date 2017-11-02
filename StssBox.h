/*
 * StssBox.h
 *
 * Sync Sample Box
 *
 */

#ifndef STSSBOX_H_
#define STSSBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StssBox : protected FullBox
{
public:
	StssBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~StssBox();
private:
	// const

	static const unsigned int EntryTblSize = 64;

	unsigned int _entry_count;
	unsigned int _entries[EntryTblSize];					// make room for 64 entries and that should be it. TODO? allow to grow?
};

} /* namespace MPEG4Player */
#endif /* STSSBOX_H_ */
