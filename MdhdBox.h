/*
 * MdhdBox.h
 *
 * Media Header box.
 *
 */

#ifndef MDHDBOX_H_
#define MDHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class MdhdBox : protected FullBox
{
public:
	MdhdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~MdhdBox();

private:

	unsigned int _creationTime;						// number of seconds since midnight, Jan 1, 1904
	unsigned int _modificationTime;					// number of seconds since midnight, Jan 1, 1904
	unsigned int _timescale;						// number of time units in 1 second.
	unsigned int _duration;

	unsigned long long int _creationTime_64;		// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _modificationTime_64;	// number of seconds since midnight, Jan 1, 1904
	unsigned long long int _duration_64;

	char _language[3];								// ISO 639-2 language code.

};

} /* namespace MPEG4Player */
#endif /* MDHDBOX_H_ */
