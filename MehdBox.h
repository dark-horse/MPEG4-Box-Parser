/*
 * MehdBox.h
 *
 * Move Extends box.
 *
 */

#ifndef MEHDBOX_H_
#define MEHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class MehdBox : protected FullBox
{
public:
	MehdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~MehdBox();
private:
		typedef union _Duration
		{
			unsigned int 			_duration32;
			unsigned long long int 	_duration64;
		} Duration;
		
		Duration _fragmentDuration;
};

} /* namespace MPEG4Player */
#endif /* MEHDBOX_H_ */
