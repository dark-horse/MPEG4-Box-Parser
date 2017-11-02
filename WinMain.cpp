/*
 * main.cpp
 *
 * Implementation of a MPEG4 media player based on ISO/EIC 14496.
 *
 */

#include "MPEG4Player.h"
#include "BoxBase.h"
#include "MPEG4Parser.h"
#include "FtypBox.h"
#include "MoovBox.h"
#include "MdatBox.h"
#include "UnknBox.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	MPEG4Player::MPEG4Parser parser;

	//pCmdLine = "c:\\Users\\Olga & Daniel\\Videos\\Luca\\SANY0001.MP4\0";
	//char *a = (char *) malloc ((strlen(pCmdLine) + 1) * sizeof(char));
	//memcpy (a /*dest*/, pCmdLine /*src*/, strlen(pCmdLine) + 1 /*num*/);

	FUNC_RES res = parser.Initialize(pCmdLine);

	MPEG4Player::BoxBase ** boxList;
	int numBoxes;

	if (res == SUCCESS)
	{
		parser.Parse(&boxList, &numBoxes);
		printf("WinMain, after Parse. numBoxes is: %d.\r\n", numBoxes);
		for (int i = 0; i < numBoxes; i++)
		{
			MPEG4Player::BoxBase * bb = *(boxList + i);
			if (bb->GetBoxType() == MPEG4Player::BoxBase::FtypBox)
			{
				printf("WinMain, after Parse. we have an FtypBox. Do the cast\r\n");

				MPEG4Player::FtypBox * ftypBox = reinterpret_cast<MPEG4Player::FtypBox*> (bb);
				printf("WinMain, after Parse. we have an FtypBox. after the cast before print\r\n");

				ftypBox->Print();
				printf("WinMain, after Parse. we have an FtypBox. after print\r\n");
			}
			delete bb;
		}
	}

	//free (a);

	if (res == ERR_FILE_OPEN)
	{
		MessageBox(NULL, L"Cannot open the file. Please check the path and try again.", L"MPEG4Player", MB_OK);
	}

	return 0;
}



