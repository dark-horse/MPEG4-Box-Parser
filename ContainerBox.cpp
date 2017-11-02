/*
 * ContainerBox.cpp
 *
 *
 */

#include "ContainerBox.h"
#include "MvhdBox.h"
#include "TrakBox.h"
#include "UnknBox.h"
#include "TkhdBox.h"
#include "TrefBox.h"
#include "EdtsBox.h"
#include "ElstBox.h"
#include "MdiaBox.h"
#include "MdhdBox.h"
#include "HdlrBox.h"
#include "MinfBox.h"
#include "VmhdBox.h"
#include "SmhdBox.h"
#include "HmhdBox.h"
#include "NmhdBox.h"
#include "DinfBox.h"
#include "DrefBox.h"
#include "StblBox.h"
#include "StsdBox.h"
#include "SttsBox.h"
#include "SdtpBox.h"
#include "CttsBox.h"
#include "StscBox.h"
#include "StszBox.h"
#include "Stz2Box.h"
#include "StcoBox.h"
#include "Co64Box.h"
#include "StssBox.h"
#include "StshBox.h"
#include "PadbBox.h"
#include "StdpBox.h"
#include "SbgpBox.h"
#include "SgpdBox.h"
#include "SubsBox.h"
#include "FreeBox.h"
#include "SkipBox.h"
#include "UdtaBox.h"
#include "Utils.h"

namespace MPEG4Player
{

ContainerBox::ContainerBox()
{
	_boxList = NULL;
	_numBoxes = 0;
	_allocBoxListSize = 0;
}

// the workhorse
FUNC_RES ContainerBox::ParseBox(MPEG4FileStream *stream)
{

	FUNC_RES res = ParseBoxHeader(stream);

	if (res != SUCCESS)
	{
		return res;
	}

	unsigned long long int bytesLeftInBox = _isLargeBox ? _largeSize - 4 - 4 - 8 : _size - 4 - 4;

	Print();

	_numBoxes = 0;
	_allocBoxListSize = 8;
	_boxList = (BoxBase **) malloc (_allocBoxListSize * sizeof(BoxBase *));

	while (bytesLeftInBox)
	{
		printf("DEBUG COntainer Parse. bytesLeftInBox are: 0x%x\r\n", bytesLeftInBox);
		printf("DEBUG Container Parse stream offset is: 0x%x.\r\n", stream->GetOffset());
		char fourChars[4];
		unsigned int a;
		stream->ReadBytes(fourChars, 4, &a);
		unsigned int size = UtilsIntFromFourChars(fourChars);
		printf("DEBUG Container Parse stream offset is: 0x%x.\r\n", stream->GetOffset());
		stream->ReadBytes(fourChars, 4, &a);

		BoxBase * box = NULL;

		printf("DEBUG: we got these chars: %c%c%c%c\r\n", fourChars[0],fourChars[1],fourChars[2],fourChars[3]);
		printf("DEBUG: we got these chars: %x%x%x%x\r\n", (int)fourChars[0],(int)fourChars[1],(int)fourChars[2],(int)fourChars[3]);

		if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "mvhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::MvhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "trak")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::TrakBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "tkhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::TkhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "edts")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::EdtsBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "elst")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::ElstBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "mdia")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::MdiaBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "mdhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::MdhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "hdlr")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::HdlrBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "minf")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::TrakBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "vmhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::VmhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "smhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SmhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "hmhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::HmhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "nmhd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::NmhdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "dinf")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::DinfBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "dref")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::DrefBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stbl")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StblBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stsd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StsdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stts")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SttsBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "ctts")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::CttsBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stsc")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StscBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stsz")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StszBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stz2")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::Stz2Box());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stco")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StcoBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "co64")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::Co64Box());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stss")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StssBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stsh")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StshBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "padb")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::PadbBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "stdp")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::StdpBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "sdtp")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SdtpBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "sbgp")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SbgpBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "sgpd")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SgpdBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "subs")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SubsBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "free")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::FreeBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "skip")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::SkipBox());
		}
		else if ( (* ((unsigned int *) fourChars)) == (* ((unsigned int *) "udta")))
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::UdtaBox());
		}
		else
		{
			box = reinterpret_cast<BoxBase *> (new MPEG4Player::UnknBox(fourChars));
		}



		box->Initialize(stream->GetOffset() - 4 - 4, size, 0);
		box->ParseBox(stream);

		printf("DEBUG we just got the following box:\r\n");
		box->Print();

		bytesLeftInBox -= box->IsLargeBox() ? box->GetLargeSize() : box->GetSize();


		if(_boxList && _allocBoxListSize == _numBoxes)
		{
			_allocBoxListSize = _allocBoxListSize * 2;
			_boxList = (BoxBase **) realloc (_boxList, _allocBoxListSize * sizeof(BoxBase*));
		}

		if (_boxList)
		{
			_boxList[_numBoxes] = box;
		}
		_numBoxes ++;
	}

	return SUCCESS;
}

void ContainerBox::GetChildren(BoxBase *** boxList, int * numBoxes)
{
	*boxList = _boxList;
	*numBoxes = _numBoxes;
}

ContainerBox::~ContainerBox()
{
	if (_boxList)
	{
		for (int i = 0; i < _numBoxes; i ++)
		{
			delete _boxList[i];
		}
		free (_boxList);
	}

	_boxList = NULL;
	_numBoxes = 0;
	_allocBoxListSize = 0;
}

} /* namespace MPEG4Player */
