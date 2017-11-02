/*
 * BtrtBox.h
 *
 *	Bit rate box.
 *
 */

#ifndef BTRTBOX_H_
#define BTRTBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class BtrtBox : protected BoxBase
{
public:
	BtrtBox();
	virtual ~BtrtBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
	unsigned int _bufferSizeDB;
	unsigned int _maxBitRate;
	unsigned int _avgBitRate;
};

} /* namespace MPEG4Player */
#endif /* BTRTBOX_H_ */
