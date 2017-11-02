/*
 * DrefBox.cpp
 *
 *
 */

#include "DrefBox.h"
#include "Utils.h"
#include "UrlBox.h"
#include "UrnBox.h"
#include <stdlib.h>

namespace MPEG4Player
{

DrefBox::DrefBox()
{
	_boxType = BoxBase::DrefBox;
	_urlUrnBoxes = NULL;
}

FUNC_RES DrefBox::ParseBox(MPEG4FileStream *stream)
{
	ParseVersionFlags(stream);
	unsigned int a;
	char fourChars[4];

	// read pre_defined.
	stream->ReadBytes(fourChars, 4, &a);
	_entryCount = UtilsIntFromFourChars(fourChars);
	if (_entryCount == 0)
		return SUCCESS;
	
	_urlUrnBoxes = (FullBox **) malloc(sizeof(FullBox*) * _entryCount);
	
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		unsigned long long int fileOffset;
		unsigned int size;

		fileOffset = stream->GetOffset();

		stream->ReadBytes(fourChars, 4, &a);
		size = UtilsIntFromFourChars(fourChars);

		stream->ReadBytes(fourChars, 4, &a);
		if (!strncmp("url ", fourChars, 4))
		{
			MPEG4Player::UrlBox * urlBox = new MPEG4Player::UrlBox();
			(reinterpret_cast<BoxBase*> (urlBox))->Initialize(fileOffset, size, 0);		// this cast here sucks!
			urlBox->ParseBox(stream);
			_urlUrnBoxes[i] = reinterpret_cast<FullBox*> (urlBox);
		}
		else if (!strncmp("urn ", fourChars, 4))
		{
			MPEG4Player::UrnBox * urnBox = new MPEG4Player::UrnBox();
			(reinterpret_cast<BoxBase*> (urnBox))->Initialize(fileOffset, size, 0);		// this cast here sucks!
			urnBox->ParseBox(stream);
			_urlUrnBoxes[i] = reinterpret_cast<FullBox*>  (urnBox);
		}
	}

	return SUCCESS;
}

void DrefBox::Print()
{
	printf("Box Type: Dref.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf("\tversion: \t0x%08X.\r\n", _version);
	printf("\tflags: 	\t0x%08X.\r\n", _flags);
	printf("\tentry count: 0x%08X.\r\n", _entryCount);
	if (_urlUrnBoxes == NULL)
		return;
	printf("\tDref Url Urn Boxes:\r\n");
	for (unsigned int i = 0; i < _entryCount; i++)
	{
		if(_urlUrnBoxes[i])
			_urlUrnBoxes[i]->Print();
	}
}

DrefBox::~DrefBox()
{
	if (_urlUrnBoxes)
	{
		for (unsigned int i = 0; i < _entryCount; i++)
		{
			if(_urlUrnBoxes[i])
				delete (_urlUrnBoxes[i]);
			_urlUrnBoxes[i] = NULL;	
		}
		free(_urlUrnBoxes);
	}
	_urlUrnBoxes = NULL;
}

} /* namespace MPEG4Player */
