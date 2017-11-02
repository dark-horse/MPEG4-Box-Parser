/*
 * Tkhd.h
 *
 * Track Header Class
 *
 */

#ifndef TKHD_H_
#define TKHD_H_

#include "FullBox.h"


namespace MPEG4Player
{

class TkhdBox : protected FullBox
{
public:
	TkhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~TkhdBox();
private:
	unsigned int _creationTime;						// number of seconds since midnight, Jan 1, 1904
	unsigned int _modificationTime;					// number of seconds since midnight, Jan 1, 1904
	unsigned int _track_ID;							// unique identifier for the track.
	unsigned int _duration;

	unsigned long long int _creationTime_64;		// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _modificationTime_64;	// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _duration_64;

	unsigned int _layer;
	unsigned int _alternate_group;
	unsigned int _volume;							// fixed point 8.8 preferred play back volume (typically 1.0 - 0x00000100 = full volume)

	unsigned int _matrix[9];						// transformation matrix for the video
	unsigned int _width;							// track's visual representation as fixed point 16.16 values.
	unsigned int _height;							// track's visual representation as fixed point 16.16 values.
};

} /* namespace MPEG4Player */
#endif /* TKHD_H_ */
