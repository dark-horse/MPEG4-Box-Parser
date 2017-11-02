/*
 * UrlBox.h
 *
 *	Url box.
 *
 */

#ifndef URLBOX_H_
#define URLBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class UrlBox : protected FullBox
{
public:
	UrlBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~UrlBox();
private:
	char * _location;								// location of the URL. In UTF-8 format
	unsigned int _locationSize;						// size of the _location buffer. In bytes.
};

} /* namespace MPEG4Player */
#endif /* URLBOX_H_ */
