/*
 * PaspBox.h
 *
 * Pixel Aspect Ratio Box
 *
 */

#ifndef PASPBOX_H_
#define PASPBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class PaspBox : protected BoxBase
{
public:
	PaspBox();
	virtual ~PaspBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
	unsigned int _hSpacing;
	unsigned int _vSpacing;
};


} /* namespace MPEG4Player */
#endif /* PASPBOX_H_ */
