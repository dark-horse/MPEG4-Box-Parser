/*
 * SmhdBox.h
 *
 * Sound Media Header
 */

#ifndef SMHDBOX_H_
#define SMHDBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SmhdBox : protected FullBox
{
public:
	SmhdBox();
	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~SmhdBox();
private:
	unsigned int _balance;
};

} /* namespace MPEG4Player */
#endif /* SMHDBOX_H_ */
