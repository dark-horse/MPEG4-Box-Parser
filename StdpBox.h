/*
 * StdpBox.h
 *
 * Degradation Priority box.
 *
 */

#ifndef STDPBOX_H_
#define STDPBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class StdpBox : protected FullBox
{
public:
	StdpBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~StdpBox();
private:
	unsigned int _priorityCount;					// number of priorities
	unsigned int * _priorities;						// an array of priorities
};

} /* namespace MPEG4Player */
#endif /* STDPBOX_H_ */
