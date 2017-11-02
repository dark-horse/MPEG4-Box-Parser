/*
 * MoovBox.cpp
 *
 *
 */

#include "MoovBox.h"
#include "MvhdBox.h"
#include "TrakBox.h"
#include "UnknBox.h"
#include "Utils.h"

namespace MPEG4Player
{

MoovBox::MoovBox()
{
	_boxType = BoxBase::MoovBox;
}

void MoovBox::Print()
{
	printf("Box Type: Moov.\r\n");
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


MoovBox::~MoovBox()
{
}

} /* namespace MPEG4Player */
