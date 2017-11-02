/*
 * MPEG4Parser.h
 *
 *
 */

#ifndef MPEG4PARSER_H_
#define MPEG4PARSER_H_

#include "MPEG4Player.h"
#include "BoxBase.h"

namespace MPEG4Player
{

class MPEG4Parser
{
public:
	MPEG4Parser();
	FUNC_RES Initialize(LPSTR fileName);
	FUNC_RES Parse(BoxBase *** boxList, int *numBoxes);				// returns a pointer to an array of pointers. Sort of kludgy. Maybe we can make it better.
	virtual ~MPEG4Parser();

private:

	// Constants

	// Member variables
	MPEG4FileStream _stream;

	// Functions

	// Helper Functions
};

} /* namespace MPEG4Player */
#endif /* MPEG4PARSER_H_ */
