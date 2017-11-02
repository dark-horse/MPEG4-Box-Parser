/*
 * EdtsBox.cpp
 *
 *
 */

#include "EdtsBox.h"

namespace MPEG4Player
{

EdtsBox::EdtsBox()
{
	_boxType = BoxBase::EdtsBox;
}

void EdtsBox::Print()
{
	printf("Box Type: Edts.\r\n");
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

EdtsBox::~EdtsBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace MPEG4Player */
