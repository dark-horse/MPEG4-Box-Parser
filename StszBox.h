/*
 * StszBox.h
 *
 * Sample Size Box
 *
 */

#ifndef STSZBOX_H_
#define STSZBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StszBox : protected FullBox
{
public:
	StszBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();


	virtual ~StszBox();
private:
	static const unsigned int EntryTblSize = 64;

	unsigned int _default_size;
	unsigned int _sample_count;
	unsigned int _sample_sizes[EntryTblSize];						// make room for 64 entries and that should be it. TODO? allow to grow?

};

} /* namespace MPEG4Player */
#endif /* STSZBOX_H_ */
