/*
 * ElstBox.h
 *
 * Edit List box.
 *
 */

#ifndef ELSTBOX_H_
#define ELSTBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class ElstBox : protected FullBox
{
public:
	ElstBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~ElstBox();
private:
	unsigned int _entryCount;						// number of entries
	
	class EditListEntry
	{
	public:
		typedef union _Duration
		{
			unsigned int 			_duration32;
			unsigned long long int 	_duration64;
		} Duration;
		typedef union _MediaTime
		{
			unsigned int 			_mediaTime32;
			unsigned long long int 	_mediaTime64;
		} MediaTime;
		
		Duration _duration;
		MediaTime _mediaTime;
		unsigned int _media_rate_integer;
	};

	EditListEntry * _entries;					// an array of entries
	
};

} /* namespace MPEG4Player */
#endif /* ELSTBOX_H_ */
