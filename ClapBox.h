/*
 * ClapBox.h
 *
 *
 */

#ifndef CLAPBOX_H_
#define CLAPBOX_H_
#include "BoxBase.h"

namespace MPEG4Player
{

class ClapBox : protected BoxBase
{
public:
	ClapBox();
	virtual ~ClapBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

private:
	unsigned int _cleanApertureWidthN;
	unsigned int _cleanApertureWidthD;

	unsigned int _cleanApertureHeightN;
	unsigned int _cleanApertureHeightD;

	unsigned int _horizOffN;
	unsigned int _horizOffD;

	unsigned int _vertOffN;
	unsigned int _vertOffD;
};

} /* namespace MPEG4Player */
#endif /* CLAPBOX_H_ */
