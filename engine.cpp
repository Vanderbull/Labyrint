#include ".\engine.h"

#include "showbitmapresource.h"

extern HINSTANCE hInst;				// holds the instance for this app

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::init()
{
	Laby.LoadMap("levels/level2.txt");

	long t1=timeGetTime();

	Laby.StartLocation();

	Player.SetXY(Laby.xcoord,Laby.ycoord);

	long t2=timeGetTime();

	timePaint=t2-t1;
	return true;

//	Laby.StartLocation();

//	Player.SetXY(Laby.xcoord,Laby.ycoord);

//	return true;
}

bool Engine::paint(HINSTANCE hInstance, HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect,int temp)
{
	long t3 =timeGetTime();

	hdc = GetDC(hwnd);
	

	for(int col = 0; col < Laby.levelFigure.size()-1; col++)
	{
			for(int row = 0; row < Laby.levelFigure.size()-1; row++)
			{
				if(Laby.levelFigure.size() == 0)
				{
					Laby.LoadMap("levels/level2.txt");
				}
				if(Laby.levelFigure[col].at(row) == 1)
				{
					ShowBitmapResource(hInstance, hdc,row*Laby.block_size,col*Laby.block_size,IDB_WALL);
					SetPixel(hdc,740+row*2,100+col*2,RGB(255,0,255));
				}
				if(Laby.levelFigure[col].at(row) == 3)
				{
					Rectangle(hdc, col*Laby.block_size, row*Laby.block_size, (col*Laby.block_size)+Laby.block_size, (col*Laby.block_size) + Laby.block_size);
				}
			}
	}


	//int x = rand()%255;
	//int y = rand()%255;

	
	//SetPixel(hdc,x,y,RGB(255,0,0));

	HPEN white_pen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	SelectObject(hdc,white_pen);
	//Rectangle(hdc,xprev,yprev,xprev+Laby.block_size,yprev+Laby.block_size);
	Rectangle(hdc,Player.GetPX(),Player.GetPY(),Player.GetPX()+Laby.block_size,Player.GetPY()+Laby.block_size);
//	ShowBitmapResource(hInstance, hdc,PlayerX,PlayerY,IDB_PLAYER);
	ShowBitmapResource(hInstance, hdc,Player.GetX(),Player.GetY(),IDB_PLAYER);
	DeleteObject(white_pen);


	HPEN red_pen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
	SelectObject(hdc,red_pen);
	SetPixel(hdc,740+Player.GetPX()/16,100+Player.GetPY()/16,RGB(255,255,255));
	SetPixel(hdc,740+Player.GetX()/16,100+Player.GetY()/16,RGB(0,0,255));	
	DeleteObject(red_pen);

	ReleaseDC(hwnd,hdc);
	ValidateRect(hwnd,&rect);
	GetClientRect(hwnd,&rect);

	long t4 =timeGetTime();
	long elapsed=t4-t3;
	timePaint = t4-t3;

	return true;
}

bool Engine::erase_screen(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect)
{
	hdc = GetDC(hwnd);
	ValidateRect(hwnd,&rect);
	GetClientRect(hwnd,&rect);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	return true;
}

bool Engine::collision(int NextX, int NextY)
{
	if(Laby.levelFigure[NextX].at(NextY) == 1)
	{
		return true;
	}
	else
	{
		Player.SetMoves();
		return false;
	}
}

int Engine::timePainty()
{
	return timePaint;
}