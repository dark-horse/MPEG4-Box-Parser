/*
 * TrakBox.cpp
 *
 *
 */

#include "TrakBox.h"
#include "Utils.h"

namespace MPEG4Player
{
TrakBox::TrakBox()
{
	_boxType = BoxBase::TrakBox;
}

void TrakBox::Print()
{
	printf("Box Type: Trak.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	if (_numBoxes && _boxList)
	{
		for (int i = 0; i < _numBoxes; i++)
		{
			printf("\t\tBox: %d.\r\n", i);
			_boxList[i]->Print();
		}
	}
}


TrakBox::~TrakBox()
{
}

} /* namespace MPEG4Player */
