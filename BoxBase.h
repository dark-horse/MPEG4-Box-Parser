/*
 * BoxBase.h
 *
 * Base class for MPEG4 box types
 *
 */

#ifndef BOXBASE_H_
#define BOXBASE_H_

#include "MPEG4Player.h"
#include "MPEG4FileStream.h"
#include "Utils.h"
#include <stdio.h>

namespace MPEG4Player
{

class BoxBase
{
public:

	enum BoxType
	{
		AvccBox,							// is this an avcc box?
		ClapBox,							// is this a clean aperture box?
		BtrtBox,							// is this a bit rate box?
		Co64Box,							// is this a chunk large offset box?
		FtypBox,							// is this a file type box?
		PdinBox,							// is this a progressive download information box?
		MvhdBox,							// is this a movie header box?
		MoovBox,							// is this a movie box?
		TrakBox,							// is this a track box?
		TkhdBox,							// is this a track header box?
		TrefBox,							// is this a track reference container?
		EdtsBox,							// is this a edit list container?
		ElstBox,							// is this a edit list box?
		MehdBox,							// is this a movie extends box?
		MfhdBox,							// is this a movie fragment box?
		MdiaBox,							// is this a container for media information in a track?
		MdhdBox,							// is this a movie header?
		HdlrBox,							// is this a media handler box?
		MinfBox,							// is this a media information container?
		VmhdBox,							// is this a video media header (video track only)?
		SmhdBox,							// is this a sound media header (sound track only)?
		HmhdBox,							// is this a hint media header (hint track only)?
		NmhdBox,							// is this a null media header box?
		DinfBox,							// is this a data information box?
		DrefBox,							// is this a data reference box?
		StblBox,							// is this a sample table box?
		StsdBox,							// is this a sample description box?
		StssBox,							// is this a decoding time to sample box?
		CttsBox,							// is this a composition time to sample box?
		StscBox,							// is this a sample to chunk partial data offset info box?
		StszBox,							// is this a sample sizes box?
		Stz2Box,							// is this a compact sample sizes box?
		StcoBox,							// is this a chunk offset, partial data offset info box?
		StshBox,							// is this a sync sample table box?
		PadbBox,							// is this a sample padding box?
		StdpBox,							// is this a sample degradation priority box?
		SttsBox,							// is this a time to sample box?
		SdtpBox,							// is this a independent and disposable sample box?
		SbgpBox,							// is this a sample to group box?
		SgpdBox,							// is this a sample group description box?
		SubsBox,							// is this a sub sample info box?
		TrexBox,							// is this a track extends box?
		M4dsBox,							// is this a MPEG4 descriptor box?
		MdatBox,							// is this a media data box?
		FreeBox,							// is this a free box?
		SkipBox,							// is this a skip box?
		UdtaBox,							// is this a user data box?
		UuidBox,							// is this a UUID box?
		UrlBox,								// is this an URL box?
		UrnBox,								// is this an URN box?
		HintBox,							// is this a hint track reference type box?
		CdscBox,							// is this a cdcs track reference type box?
		HindBox,							// is this a hind track reference type box?
		PaspBox,							// is this a pixel aspect box?
		UnknBox,							// if it's not one of the boxes above, then it's an unknown box.
	};

	BoxBase()
		{
			_size = 0;
			_largeSize = 0;
			_fileOffset = 0;
			_isLargeBox = false;
		}

	BoxType GetBoxType() {return _boxType;}


	bool IsLargeBox() {return _isLargeBox;}						// is this a 64 bit box?

	// Size functions
	unsigned int GetSize() {return _size;}						// return the size of the box - when it's not a 64 bit box
	unsigned long long int GetLargeSize() {return _largeSize;}	// return the size of the box - when it is a 64 bit box.

	// offset functions - useful when searching through files
	unsigned long long int GetStartOffset() {return _fileOffset;}

	// Initialization
	virtual void Initialize(unsigned long long int fileOffset, unsigned int size, unsigned long long int largeSize)
		{
			_fileOffset = fileOffset;
			_size = size;
			_largeSize = largeSize;
		}

	// Parsing
	virtual FUNC_RES ParseBox(MPEG4FileStream *stream)
		{
			return ERR_FILE_READ;
		}

	virtual ~BoxBase() {}


	// Child boxes
	virtual void GetChildren(BoxBase *** boxList, int * numBoxes)
		{
			*numBoxes = 0;
			*boxList = NULL;
		}

	// useful for debugging. Need to link with -mconsole option.
	virtual void Print() {printf("Base Box.\r\n");}


protected:

	FUNC_RES ParseBoxHeader(MPEG4FileStream *stream)
	{
		FUNC_RES res = SUCCESS;

		if (_size == 1)
		{
			// this is a large box.
			_isLargeBox = true;
			unsigned int a;
			char eightChars[8];
			res = stream->ReadBytes(eightChars, 8, &a);
			_largeSize = UtilsLongIntFromEightChars(eightChars);
		}

		return res;
	}

	unsigned int _size;
	unsigned long long int _largeSize;
	unsigned long long int _fileOffset;
	BoxType _boxType;
	bool _isLargeBox;
};

} /* namespace MPEG4Player */
#endif /* BOXBASE_H_ */
