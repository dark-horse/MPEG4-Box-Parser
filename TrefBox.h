/*
 * TrefBox.h
 *
 *	Track Reference Box
 *
 */

#ifndef TREFBOX_H_
#define TREFBOX_H_

#include "BoxBase.h"

namespace MPEG4Player
{

class TrefBox : protected BoxBase
{
public:
	TrefBox();
	virtual ~TrefBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	class TrackReferenceTypeBox : BoxBase
	{

	public:
		TrackReferenceTypeBox () {}

		TrackReferenceTypeBox(BoxBase::BoxType boxType)
			{
				memset (this, 0, sizeof(TrackReferenceTypeBox));
				_boxType = boxType;
			}

		void Initialize(unsigned long long int fileOffset, unsigned int size, unsigned long long int largeSize)
			{
				_fileOffset = fileOffset;
				_size = size;
				_largeSize = largeSize;
			}

		FUNC_RES ParseBox(MPEG4FileStream *stream);

		void Print();

		virtual ~TrackReferenceTypeBox()
			{
				memset (this, 0, sizeof(TrackReferenceTypeBox));
			}
	private:

		static const unsigned int TrackIDsTblSize = 32;
		unsigned int _trackIDs[TrackIDsTblSize];				// store at most 32 track IDs
		unsigned int _numTrackIDs;								// how many track IDs are there?

	};
private:
	static const unsigned int TrackRefTblSize = 32;						// store at most 32 track reference type boxes
	TrackReferenceTypeBox _trackRefBoxes[TrackRefTblSize];	// our storage of track reference boxes.
	unsigned int _numTrackRefTypeBoxes;							// how many track reference boxes are there?
};

} /* namespace MPEG4Player */
#endif /* TREFBOX_H_ */
