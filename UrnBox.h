/*
 * UrnBox.h
 *
 *	Urn box.
 *
 */

#ifndef URNBOX_H_
#define URNBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class UrnBox : protected FullBox
{
public:
	UrnBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~UrnBox();
private:
	char * _name;									// name of the URN. In UTF-8 format
	unsigned int _nameSize;							// size of the _name buffer. In bytes
	char * _location;								// location of the URN. In UTF-8 format
	unsigned int _locationSize;						// size of the _location buffer. In bytes.

	char * CopyUTF8String(	MPEG4FileStream *stream,						// copies bytes from the stream until the end of UTF8 string.
							unsigned int * bytesAllocated,
							unsigned int * copiedBytes);
};

} /* namespace MPEG4Player */
#endif /* URNBOX_H_ */
