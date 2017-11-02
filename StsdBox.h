/*
 * StsdBox.h
 *
 *
 */

#ifndef STSDBOX_H_
#define STSDBOX_H_

#include "FullBox.h"


namespace MPEG4Player
{

class StsdBox : protected FullBox
{
public:
	StsdBox();
	virtual ~StsdBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	inline unsigned int GetNumBoxes() { return _numBoxes;}
	inline BoxBase* GetBox(int index) { return * (_boxes + index);}

private:
	BoxBase ** _boxes;
	unsigned int _numBoxes;

};
}/* namespace MPEG4Player */
#endif /* STSDBOX_H_ */
