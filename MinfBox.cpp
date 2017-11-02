/*
 * MinfBox.cpp
 *
 *
 */

#include "MinfBox.h"

namespace MPEG4Player
{

MinfBox::MinfBox()
{
	_boxType = BoxBase::MinfBox;
}


void MinfBox::Print()
{
	printf("Box Type: Minf.\r\n");
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

MinfBox::~MinfBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
