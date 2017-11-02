/*
 * ClapBox.cpp
 *
 *
 */

#include "ClapBox.h"
#include "Utils.h"

namespace MPEG4Player
{

ClapBox::ClapBox()
{
	_boxType = BoxBase::ClapBox;
}

FUNC_RES ClapBox::ParseBox(MPEG4FileStream *stream)
{
	char fourChars[4];
	unsigned int a;

	// _cleanApertureWidthN
	stream->ReadBytes(fourChars, 4, &a);
	_cleanApertureWidthN = UtilsIntFromFourChars(fourChars);

	// _cleanApertureWidthD
	stream->ReadBytes(fourChars, 4, &a);
	_cleanApertureWidthD = UtilsIntFromFourChars(fourChars);

	// _cleanApertureHeightN
	stream->ReadBytes(fourChars, 4, &a);
	_cleanApertureHeightN = UtilsIntFromFourChars(fourChars);

	// _cleanApertureHeightD
	stream->ReadBytes(fourChars, 4, &a);
	_cleanApertureHeightD = UtilsIntFromFourChars(fourChars);

	// _horizOffN
	stream->ReadBytes(fourChars, 4, &a);
	_horizOffN = UtilsIntFromFourChars(fourChars);

	// _horizOffD
	stream->ReadBytes(fourChars, 4, &a);
	_horizOffD = UtilsIntFromFourChars(fourChars);

	// _vertOffN
	stream->ReadBytes(fourChars, 4, &a);
	_vertOffN = UtilsIntFromFourChars(fourChars);

	// _vertOffD
	stream->ReadBytes(fourChars, 4, &a);
	_vertOffD = UtilsIntFromFourChars(fourChars);

	return SUCCESS;
}

void ClapBox::Print()
{
	printf("Box Type: PASP.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tcleanApertureWidthN: %08X.\r\n",_cleanApertureWidthN);
	printf("\tcleanApertureWidthD: %08X.\r\n",_cleanApertureWidthD);
	printf("\tcleanApertureHeightN: %08X.\r\n",_cleanApertureHeightN);
	printf("\tcleanApertureHeightD: %08X.\r\n",_cleanApertureHeightD);
	printf("\thorizOffN: %08X.\r\n",_horizOffN);
	printf("\thorizOffD: %08X.\r\n",_horizOffD);
	printf("\tvertOffN: %08X.\r\n",_vertOffN);
	printf("\tvertOffD: %08X.\r\n",_vertOffD);
}

ClapBox::~ClapBox()
{
}
} /* namespace MPEG4Player */
