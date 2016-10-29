
#ifndef INC_VARIABLES_H
#define INC_VARIABLES_H

#include <iostream>
#include <string>		// for string variables
#include <vector>		// vector<Highscore>
#include <algorithm>	// for_each() + sort()
#include <iomanip>
#include <fstream>
#include<sstream>
#include <windows.h>

using namespace std;

HDC gDC;

HWND debug;

char debug_buffer[256];

int Dcol = 0;
int Drow = 0;

HPEN red_pen = 0;
HPEN green_pen = 0;
HPEN blue_pen = 0;

// Prints the highscore in a sorted order to the output screen
void debug_info(HWND hwnd)
{	
	gDC = GetDC(hwnd);
	
	TextOut(gDC, 900, 50, debug_buffer,
		wsprintf(debug_buffer, TEXT("DEBUGGING INFO")));

	TextOut(gDC, 900, 100, debug_buffer,
		wsprintf(debug_buffer, TEXT("moves: %d"), Player.GetMoves()));

	TextOut(gDC, 850, 0, debug_buffer,
		wsprintf(debug_buffer, TEXT("Paint: %d Init: %d Collision: %d"), timePaint, timeInit, timeCollision));
		
	for(Dcol = 0; Dcol < Laby.levelFigure.size()-1; Dcol++)
	{
		for( Drow = 0; Drow < Laby.levelFigure.size()-1; Drow++)
		{
			TextOut(gDC, 700+(Drow*10), 360+(Dcol*15), debug_buffer,
			wsprintf(debug_buffer, TEXT("%d"),Laby.levelFigure[Dcol][Drow]));
		}
	}
	ReleaseDC(hwnd,gDC);	
}

#endif
