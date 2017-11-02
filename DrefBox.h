/*
 * DrefBox.h
 *
 *	Data Reference box.
 *
 */

#ifndef DREFBOX_H_
#define DREFBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class DrefBox : protected FullBox
{
public:
	DrefBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~DrefBox();
private:
	unsigned int _entryCount;						// number of Url/Urn boxes in the Dref box
	FullBox ** _urlUrnBoxes;						// an array of pointers to Url/Urn boxes
};

} /* namespace MPEG4Player */
#endif /* DREFBOX_H_ */
