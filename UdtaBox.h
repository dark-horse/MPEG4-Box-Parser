/*
 * UdtaBox.h
 *
 *
 */

#ifndef UDTABOX_H_
#define UDTABOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class UdtaBox : protected BoxBase
{
public:
	UdtaBox();
	virtual ~UdtaBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);
	void Print();
};

} /* namespace MPEG4Player */
#endif /* UDTABOX_H_ */
