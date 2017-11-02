/*
 * StblBox.cpp
 *
 *
 */

#include "StblBox.h"

namespace MPEG4Player
{

StblBox::StblBox()
{
	_boxType = BoxBase::StblBox;
}

void StblBox::Print()
{
	printf("Box Type: Stbl.\r\n");
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

StblBox::~StblBox()
{
}

} /* namespace MPEG4Player */
