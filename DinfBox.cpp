/*
 * DinfBox.cpp
 *
 *
 */

#include "DinfBox.h"

namespace MPEG4Player
{

DinfBox::DinfBox()
{
	_boxType = BoxBase::DinfBox;
}

void DinfBox::Print()
{
	printf("Box Type: Dinf.\r\n");
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

DinfBox::~DinfBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
