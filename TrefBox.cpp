/*
 * TrefBox.cpp
 *
 *
 */

#include "TrefBox.h"

namespace MPEG4Player
{

TrefBox::TrefBox()
{
	memset (this, 0, sizeof (TrefBox));
	_boxType = BoxBase::TrefBox;
}

FUNC_RES TrefBox::ParseBox(MPEG4FileStream *stream)
{
	unsigned int bytesLeft = _size - 4 - 4;		// 4 for size, 4 for 'tref' token

	while (bytesLeft)
	{
		char fourChars[4];
		unsigned int a, trackReferenceTypeBoxSize;

		// read the size of the next TrackRefType Box
		stream->ReadBytes(fourChars, 4, &a);
		trackReferenceTypeBoxSize = UtilsIntFromFourChars(fourChars);

		if (_numTrackRefTypeBoxes < TrackRefTblSize)
		{
			// read the 'hint'/'cdsc'/'hind' token
			stream->ReadBytes(fourChars, 4, &a);
			if (!strncmp(fourChars, "hint", 4))
			{
				_trackRefBoxes[_numTrackRefTypeBoxes] = TrackReferenceTypeBox(BoxBase::HintBox);
			}
			else if (!strncmp(fourChars, "cdsc", 4))
			{
				_trackRefBoxes[_numTrackRefTypeBoxes] = TrackReferenceTypeBox(BoxBase::CdscBox);
			}
			else if (!strncmp(fourChars, "hind", 4))
			{
				_trackRefBoxes[_numTrackRefTypeBoxes] = TrackReferenceTypeBox(BoxBase::HindBox);
			}
			else
			{
				// TODO: process error case
			}

			_trackRefBoxes[_numTrackRefTypeBoxes].Initialize(
										stream->GetOffset() - 4 - 4,	// 4 for size, 4 for 'hint'/'cdsc'/'hind' token
										trackReferenceTypeBoxSize,
										0);
			_trackRefBoxes[_numTrackRefTypeBoxes].ParseBox(stream);
		}
		else
		{
			// stop parsing the track reference type boxes.
			// Advance the stream to the end of the current track reference type box.
			stream->Seek(trackReferenceTypeBoxSize - 4);
		}

		_numTrackRefTypeBoxes ++;
		bytesLeft -= trackReferenceTypeBoxSize;
	}

	return SUCCESS;
}

void TrefBox::Print()
{
	printf("Box Type: TREF.\r\n");
	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: %x.\r\n", _size);
	printf("\ttrack Reference Boxes: %x", _numTrackRefTypeBoxes);

	for (unsigned int i = 0; i < _numTrackRefTypeBoxes && i < TrackRefTblSize; i++)
	{
		printf("\t\ttrack Reference Box %x:\r\n", i);
		_trackRefBoxes[i].Print();
	}
}

TrefBox::~TrefBox()
{
	memset (this, 0, sizeof(TrefBox));
}


// TrackReferenceTypeBox functions
FUNC_RES TrefBox::TrackReferenceTypeBox::ParseBox(MPEG4FileStream *stream)
{
	// assume that this box is not a large box...
	unsigned int bytesLeft = _size - 4 - 4;		// 4 for size, 4 for hint/cdsc/hint
	while (bytesLeft)
	{
		char fourChars[4];
		unsigned int a;

		stream->ReadBytes(fourChars, 4, &a);
		bytesLeft -= 4;

		if (_numTrackIDs < TrackIDsTblSize)
		{
			_trackIDs[_numTrackIDs] = UtilsIntFromFourChars(fourChars);
		}
		_numTrackIDs++;
	}

	return SUCCESS;
}

void TrefBox::TrackReferenceTypeBox::Print()
{
	switch (_boxType)
	{
		case BoxBase::HintBox:
			printf ("TrackReferenceTypeBox. Type HINT.\r\n");
			break;
		case BoxBase::CdscBox:
			printf ("TrackReferenceTypeBox. Type CDSC.\r\n");
			break;
		case BoxBase::HindBox:
			printf ("TrackReferenceTypeBox. Type HIND.\r\n");
			break;
		default:
			printf ("Error - type not known: %x.\r\n", _boxType);
	}

	printf("\toffset: \t0x%08I64x.\r\n", _fileOffset);
	printf("\tsize: 	\t0x%08X.\r\n", _size);
	printf ("\tnumber of TrackIDs: %d.\r\n", _numTrackIDs);

	for (unsigned int i = 0; i < _numTrackIDs && i < TrackIDsTblSize; i++)
	{
		printf("\t\ttrack id %d: %x", i, _trackIDs[i]);
	}
}

} /* namespace MPEG4Player */
