/*
 * UnknBox.h
 *
 * Unknown box
 *
 */

#include "BoxBase.h"

#ifndef UNKNBOX_H_
#define UNKNBOX_H_

namespace MPEG4Player
{

class UnknBox : protected BoxBase
{
public:
	UnknBox(char *token);
	virtual ~UnknBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();
private:
	char _token[4];					// if we don't know the type of this box, at least copy the "xxxx" token
};

} /* namespace MPEG4Player */
#endif /* UNKNBOX_H_ */
