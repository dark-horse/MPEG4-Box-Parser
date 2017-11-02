/*
 * CttsBox.h
 *
 * Composition time to sample
 *
 */

#ifndef CTTSBOX_H_
#define CTTSBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class CttsBox : protected FullBox
{
public:
	CttsBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~CttsBox();
private:

	static const unsigned int EntryTblSize = 64;

	unsigned int _entry_count;
	unsigned int _count_entries[EntryTblSize];					// make room for 64 entries and that should be it. TODO? allow to grow?
	unsigned int _sample_entries[EntryTblSize];					// make room for 64 entries and that should be it. TODO? allow to grow?
};

} /* namespace MPEG4Player */
#endif /* CTTSBOX_H_ */
