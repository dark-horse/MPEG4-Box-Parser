/*
 * PdinBox.h
 *
 *
 */

#ifndef PDINBOX_H_
#define PDINBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class PdinBox : protected FullBox
{
public:
	PdinBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~PdinBox();

private:
	struct DownloadInfo
	{
		unsigned int _rate;
		unsigned int _initialDelay;
	};

	static const unsigned int DownloadInfoBufferSize = 32;
	unsigned int _entryCount;										// number of entries
	DownloadInfo _entries[DownloadInfoBufferSize] ;					// we only copy at most 32 entries.
};

} /* namespace MPEG4Player */
#endif /* PDINBOX_H_ */
