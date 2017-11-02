/*
 * StshBox.h
 *
 * Shadow Sync sample table
 *
 */

#ifndef STSHBOX_H_
#define STSHBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StshBox : protected FullBox
{
public:
	StshBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~StshBox();
private:
	static const unsigned int EntryTblSize = 64;

	unsigned int _entry_count;
	unsigned int _shadowed_sample_entries[EntryTblSize];					// make room for 64 entries and that should be it. TODO? allow to grow?
	unsigned int _sync_sample_entries[EntryTblSize];						// make room for 64 entries and that should be it. TODO? allow to grow?
};

} /* namespace MPEG4Player */
#endif /* STSHBOX_H_ */
