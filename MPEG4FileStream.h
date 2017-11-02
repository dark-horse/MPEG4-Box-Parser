/*
 * MPEG4FileStream.h
 *
 *
 */

#ifndef MPEG4FileStream_H_
#define MPEG4FileStream_H_

#include "MPEG4Player.h"
#include <stdio.h>

namespace MPEG4Player
{

class MPEG4FileStream
{
public:
	MPEG4FileStream();
	FUNC_RES Initialize(char * fileName);
	FUNC_RES ReadBytes(char * buff, 									// used to read sequentially from the file.
					   unsigned int numBytesReq, 						// number of bytes requested
					   unsigned int * numBytesRead);					// number of bytes read from the stream.

	unsigned long long int GetOffset();									// returns the current offset in the file on disk.

	FUNC_RES Seek(unsigned long long int offset);						// if we just want to parse the file, we want to skip some regions
																		// For ex. skip / free / mdat boxes.

	bool Eof();															// we are at the end of the stream.
	virtual ~MPEG4FileStream();

private:

	// Constants
	static const unsigned int DataBuffLen = 1024 * 1024 * 5;			// we will copy 5 megs at a time from the disk onto our buffer

	// member variables

	// I/O variables.
	unsigned long long int _fileOffset;						// the offset into the file
	FILE *_fileHandle;										// the handle to the file object

	// local data variables
	int _dataOffset;										// so we know where in the data buffer we are right now.
	char * _dataBuff;										// our memory page - the data copied from disk into memory
	int _bytesReadFromDisk;									// number of bytes read last time from disk (may be less than DataBuffLen
};

} /* namespace MPEG4Player */
#endif /* MPEG4FileStream_H_ */
