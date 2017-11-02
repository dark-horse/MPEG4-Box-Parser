/*
 * MdatBox.h
 *
 *
 */

#ifndef MDATBOX_H_
#define MDATBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class MdatBox : BoxBase
{
public:
	MdatBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~MdatBox();
};

} /* namespace MPEG4Player */
#endif /* MDATBOX_H_ */
