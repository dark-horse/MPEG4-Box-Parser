/*
 * FtypBox.cpp
 *
 */

#include "FtypBox.h"
#include "Utils.h"
#include <stdlib.h>

namespace MPEG4Player
{

FtypBox::FtypBox()
{
	memset(_majorBrand,0, sizeof(_majorBrand));
	_minorVersion = 0;
	_compBrands = NULL;
	_numCompBrands = 0;

	_boxType = BoxBase::FtypBox;
}

void FtypBox::SetMajorBrand(char * majorBrand)
{
	memcpy (_majorBrand /*dest*/, majorBrand /*src*/, 4);
}

void FtypBox::SetMinorVersion(int minorVersion)
{
	_minorVersion = minorVersion;
}

void FtypBox::SetCompatibleBrands(char * compBrands, int numCompBrands)
{
	int numBytes = 4 * numCompBrands;
	_compBrands = (char*) malloc(numBytes);
	memcpy (_compBrands /*dest*/, compBrands /*src*/, 4 * numCompBrands /*num*/);
	_numCompBrands = numCompBrands;
}

char * FtypBox::GetMajorBrand()
{
	return _majorBrand;
}

int FtypBox::GetMinorVersion()
{
	return _minorVersion;
}

char * FtypBox::GetCompatibleBrands(int * numCompBrands)
{
	*numCompBrands = _numCompBrands;
	return _compBrands;
}

FUNC_RES FtypBox::ParseBox(MPEG4FileStream *stream)
{

	char fourChars[4];
	unsigned int a;
	unsigned int minorVersion;

	stream->ReadBytes(fourChars, 4, &a);
	SetMajorBrand(fourChars);

	stream->ReadBytes(fourChars, 4, &a);
	minorVersion = UtilsIntFromFourChars(fourChars);

	SetMinorVersion(minorVersion);

	// see if there are compatible brands left in the header
	int size = _size - (4 + 4 + 4 + 4);
	if (size > 0)
	{
		char buff[size];
		stream->ReadBytes(buff, size, &a);
		SetCompatibleBrands(buff, size / 4);
	}

	return SUCCESS;
}
void FtypBox::Print()
{
	printf("Box Type: Ftyp.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);

	printf("\tmajor brand: %c", *_majorBrand);printf("%c", *(_majorBrand+1));printf("%c", *(_majorBrand+2));printf("%c.\r\n", *(_majorBrand+3));
	printf("\tminor version: 0x%x.\r\n", _minorVersion);

	printf("\tcompatible brands:\r\n");
	for (int i = 0; i < _numCompBrands; i++)
	{
		printf("\t\t %c", *(_compBrands+i*4));printf("%c", *(_compBrands+i*4+1));printf("%c", *(_compBrands+i*4+2));printf("%c\r\n", *(_compBrands+i*4+3));
	}
}

FtypBox::~FtypBox()
{
	if (_compBrands)
		free (_compBrands);
	_compBrands = NULL;
	_numCompBrands = 0;
}

} /* namespace MPEG4Player */
