/*
 * MPEG4Parser.cpp
 *
 *
 */

#include "MPEG4Parser.h"
#include "Utils.h"
#include "FtypBox.h"
#include "MoovBox.h"
#include "MdatBox.h"
#include "UnknBox.h"

namespace MPEG4Player
{

MPEG4Parser::MPEG4Parser()
{
	memset (this, 0, sizeof(MPEG4Parser));

}

FUNC_RES MPEG4Parser::Initialize(LPSTR fileName)
{
	if (strlen(fileName) == 0 )
	{
		return ERR_FILE_OPEN;
	}

	return _stream.Initialize(fileName);
}

//
// the work horse.
// assumes that the file stream has been properly initialized.
//
// returns a pointer to an array of pointers. Thus, the triple indirection...
//
FUNC_RES MPEG4Parser::Parse(BoxBase *** boxList, int *numBoxes)
{
	unsigned int size = 0;
	unsigned int a;
	char fourChars [4];
	unsigned long long int fileOffset = 0;

	// the result of parsing. Start with 1 box pointers. If we need more, we will grow the list.
	int listSize = 1;
	BoxBase ** list = (BoxBase**) malloc(listSize * sizeof(BoxBase*));
	int listIndex = 0;

	while (!_stream.Eof())
	{
		fileOffset = _stream.GetOffset();

		// the first 4 bytes in the box are the size.
		_stream.ReadBytes(fourChars, 4, &a);

		size = UtilsIntFromFourChars(fourChars);

		// next four bytes in the box are the box type
		_stream.ReadBytes(fourChars, 4, &a);

		BoxBase * bb = NULL;
		if (!strncmp("ftyp", fourChars, 4))
		{
			bb = reinterpret_cast <BoxBase*> (new FtypBox());
		}
		else if (!strncmp("moov", fourChars, 4))
		{
			bb = reinterpret_cast <BoxBase*> (new MoovBox());
		}
		else if (!strncmp("mdat", fourChars, 4))
		{
			bb = reinterpret_cast <BoxBase*> (new MdatBox());
		}
		else
		{
			bb = reinterpret_cast <BoxBase*> (new UnknBox(fourChars));
		}

		bb->Initialize(fileOffset, size, 0);
		bb->ParseBox(&_stream);

		if (listIndex == listSize - 1)
		{
			// grow the list.
			listSize = listSize * 2;
			list = (BoxBase**) realloc(list, listSize * sizeof(BoxBase*));
		}

		*(list + listIndex) = bb;
		listIndex ++;
	}

	*boxList = list;
	*numBoxes = listIndex;

	return SUCCESS;
}

MPEG4Parser::~MPEG4Parser()
{
}

} /* namespace MPEG4Player */
