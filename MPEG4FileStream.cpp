/*
 * MPEG4FileStream.cpp
 *
 *
 */

#include "MPEG4FileStream.h"
#include <stdlib.h>

namespace MPEG4Player
{

MPEG4FileStream::MPEG4FileStream()
{
	memset (this, 0, sizeof(MPEG4Player::MPEG4FileStream));
}

FUNC_RES MPEG4FileStream::Initialize(LPSTR fileName)
{
	// Sometimes Windows puts double quotes (") around the file name in the command line.
	if (*fileName == '"')
		fileName++;

	int len = strlen(fileName);
	if (!len)
		return ERR_FILE_OPEN;

	char a = * (fileName + len - 1);
	if (a == '"') * (fileName + len - 1) = '\0';

	_fileHandle = fopen(fileName, "rb");

	_dataBuff = (char *) malloc (MPEG4FileStream::DataBuffLen);

	* (fileName + len - 1) =  a;

	return _fileHandle ? SUCCESS : ERR_FILE_OPEN;
}

// reads at most numBytesReq from the current _dataOffset
FUNC_RES MPEG4FileStream::ReadBytes(char * buff, unsigned int numBytesReq, unsigned int * numBytesRead)
{
	if (!_fileHandle)
		return ERR_FILE_READ;

	unsigned int bytesCopiedSoFar = 0;
	*numBytesRead = 0;

	while (bytesCopiedSoFar < numBytesReq)
	{
		// copy what is in the memory page so far
		int bytesToCopyFromPage = min (_bytesReadFromDisk - _dataOffset, numBytesReq - bytesCopiedSoFar);

		if (bytesToCopyFromPage > 0)
		{
			memcpy (buff /*dest*/, _dataBuff + _dataOffset /*src*/, bytesToCopyFromPage);
			_dataOffset += bytesToCopyFromPage;
			_fileOffset += bytesToCopyFromPage;
			bytesCopiedSoFar += bytesToCopyFromPage;
			*numBytesRead = bytesCopiedSoFar;
		}
		else
		{
			// we need to copy the next page in memory
			if (feof(_fileHandle))
			{
				return ERR_FILE_EOF;
			}
			else
			{
				_bytesReadFromDisk = fread(_dataBuff, 1, MPEG4FileStream::DataBuffLen, _fileHandle);
				_dataOffset = 0;
			}
		}
	}

	return SUCCESS;
}

unsigned long long int MPEG4FileStream::GetOffset()
{
	return _fileOffset;
}

FUNC_RES MPEG4FileStream::Seek(unsigned long long int offset)
{
	if (!_fileHandle)
		return ERR_FILE_SEEK;

	if (offset >= _bytesReadFromDisk - _dataOffset)
	{
		if (feof(_fileHandle))
		{
			return ERR_FILE_EOF;
		}

		// invalidate our state
		_bytesReadFromDisk = 0;
		_dataOffset = 0;
		_fileOffset += offset;
		return fseek(_fileHandle, offset, SEEK_CUR) ? ERR_FILE_SEEK : SUCCESS;
	}

	_dataOffset += offset;
	_fileOffset += offset;

	return SUCCESS;
}


bool MPEG4FileStream::Eof()
{
	if (!_fileHandle) return true;

	if (_bytesReadFromDisk > _dataOffset) return false;

	return feof(_fileHandle) != 0;
}

MPEG4FileStream::~MPEG4FileStream()
{
	if (_fileHandle)
		fclose (_fileHandle);

	if (_dataBuff)
		free(_dataBuff);

	memset (this, 0, sizeof(MPEG4Player::MPEG4FileStream));
}

} /* namespace MPEG4Player */
