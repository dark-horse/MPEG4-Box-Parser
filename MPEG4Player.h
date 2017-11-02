/*
 * MPEG4Player.h
 *
 * Includes Windows header files and project wide constants.
 *
 */

#ifndef MPEG4PLAYER_H_
#define MPEG4PLAYER_H_

#pragma once

// WINDOWS header files.

#ifndef UNICODE
#define UNICODE
#endif

#ifndef WINVER                  // Minimum platform is Windows XP
#define WINVER 0x0501
#endif

#define WIN32_LEAN_AND_MEAN     // define before including <windows.h>


#include <windows.h>


// Error codes
#define FUNC_RES unsigned int
#define SUCCESS 					0x00000000
#define ERR_FILE_OPEN 				0x00000001
#define ERR_FILE_READ 				0x00000002
#define ERR_FILE_SEEK				0x00000004
#define ERR_FILE_EOF 				0x00000008
#define ERR_PARSE 					0x00000010

enum PredictionMode
{
	Intra_4x4,
	Inter
};

#endif /* MPEG4PLAYER_H_ */
