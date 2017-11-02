/*
 * FtypBox.h
 *
 * File type and compatibility box for MPEG4 standard.
 *
 */

#ifndef FTYPBOX_H_
#define FTYPBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class FtypBox : BoxBase
{
public:
	FtypBox();
	void SetMajorBrand(char * majorBrand);
	void SetMinorVersion(int minorVersion);
	void SetCompatibleBrands(char * compBrands, int numCompBrands);

	char * GetMajorBrand();
	int GetMinorVersion();
	char * GetCompatibleBrands(int * numCompBrands);

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~FtypBox();

private:
	// Constants

	// Member Variables
	char _majorBrand[4];
	int _minorVersion;

	char * _compBrands;									// compatible brands.
	int _numCompBrands;									// number of compatible brands.

	// Functions
};

} /* namespace MPEG4Player */
#endif /* FTYPBOX_H_ */
