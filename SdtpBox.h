/*
 * SdtpBox.h
 *
 * Independent and Disposable Sample box.
 *
 */

#ifndef SDTPBOX_H_
#define SDTPBOX_H_

#include "FullBox.h"

namespace MPEG4Player
{

class SdtpBox : protected FullBox
{
public:
	SdtpBox();

	FUNC_RES ParseBox(MPEG4FileStream *stream);

	void Print();

	virtual ~SdtpBox();
private:
	void PrintDependencyInfo(char depend);
	unsigned int _sampleCount;					// number of samples
	char * _depends;							// an array of depends information.
												// first 2 bits = reserved
												// next 2 bits  = sample depends on 
												// next 2 bits  = sample is depended on
												// last 2 bits  = sample has redundancy.
};

} /* namespace MPEG4Player */
#endif /* SDTPBOX_H_ */
