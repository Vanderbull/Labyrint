#include ".\highscore.h"

extern HINSTANCE hInst;				// holds the instance for this app

Hiscore::Hiscore(void)
{
}

Hiscore::~Hiscore(void)
{
}

bool Hiscore::printer(HWND hwnd, const scores& test, int iterator )
{
	HDC gDC = GetDC(hwnd);

	string p = test.name;
	TextOut(gDC,300,250+iterator*20,p.c_str(),p.length());

	ReleaseDC(hwnd,gDC);
	return true;
}