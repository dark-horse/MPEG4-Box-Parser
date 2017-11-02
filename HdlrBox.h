/*
 * HdlrBox.h
 *
 *	media handler box.
 *
 */

#ifndef HDLRBOX_H_
#define HDLRBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class HdlrBox : protected FullBox
{
public:
	HdlrBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~HdlrBox();
private:
	char _handler_type[4];						// handler type. One of 'vide', 'soun', 'hint', 'meta'.
	char * _name;								// name of the handler. In UTF-8 format
};

} /* namespace MPEG4Player */
#endif /* HDLRBOX_H_ */
