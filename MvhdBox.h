/*
 * MvhdBox.h
 *
 * Movie header box.
 *
 */

#ifndef MVHDBOX_H_
#define MVHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class MvhdBox : protected FullBox
{
public:
	MvhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~MvhdBox();

private:
	unsigned int _creationTime;						// number of seconds since midnight, Jan 1, 1904
	unsigned int _modificationTime;					// number of seconds since midnight, Jan 1, 1904
	unsigned int _timescale;						// number of time units in 1 second.
	unsigned int _duration;

	unsigned long long int _creationTime_64;		// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _modificationTime_64;	// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _duration_64;

	unsigned int _rate;								// fixed point 16.16 preferred rate to play the presentation (typically 1.0)
	unsigned int _volume;							// fixed point 8.8 preferred play back volume (typically 1.0 - 0x00000100 = full volume)

	unsigned int _matrix[9];						// transformation matrix for the video
	unsigned int _next_track_ID;


};

} /* namespace MPEG4Player */
#endif /* MVHDBOX_H_ */
