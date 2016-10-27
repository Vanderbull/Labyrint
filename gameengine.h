//#include "highscore.h"
//#include "labyrint.h"
//#include "player.h"
#include "engine.h"
//#include "ShowBitmapResource.h"

// Get a reference

//static Labyrint& Laby = Labyrint::getInstance();

// Get a reference

//static Player& Player = Player::getInstance();

/* Get a reference to the DirectInput Manager */	
//static Engine& Ingine = Engine::getInstance();

long timePaint;
long timeInit;
long timeCollision;

//char	playername[64];

//vector<Hiscore> top_ten;
//Hiscore temp;



bool GameInit(HWND hwnd);
bool GameLoading(HWND hwnd);
bool GameGoal(HWND hwnd, string szPlayerName, int x, int y, int moves);
bool EraseScreen(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect);
bool GamePaint(HINSTANCE hInstance, HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect ,int temp);
bool GameCollision(int NextX, int NextY);
BOOL CALLBACK NameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

bool GameInit(HWND hwnd)
{
	long t1=timeGetTime();

	Laby.StartLocation();

	Player.SetXY(Laby.xcoord,Laby.ycoord);

	long t2=timeGetTime();
	timeInit=t2-t1;
	return true;
}

bool GameLoading(HWND hwnd)
{
/*	ifstream inmat("test.txt");
	inmat.clear();

	inmat.close();

	for(int iter = 0; iter < top_ten.size(); iter++)
	{
		print_highscore(hwnd,top_ten[iter],iter);
	}
*/
	return true;
}

// int Goal() funktionen tar emot spelaren namn och skriver ut namn och antalet
// moves som spelaren har gjort för att komma till mål, kollar ifall man har gjort
// bästa antalet moves och notifierar i så fal spelaren om att denna har lyckats
// komma in på highsocre listan. Skriver sedan allt till fil

bool GameGoal(HWND hwnd, HINSTANCE hInstance, std::string szPlayerName, int x, int y, int moves)
{
/*	if(Laby.levelFigure[x].at(y) == 3)
	{
		DialogBox (hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, NameDlgProc);
		
		temp.name = playername;
		temp.score = moves;

		if(top_ten.size() == 4)
		{
			MessageBox(hwnd,TEXT("Pop_back() one score to fit a better in the top ten list"),TEXT("File"),MB_OK);
			top_ten.pop_back();
		}
		
		top_ten.push_back(temp);
		sort(top_ten.begin(),top_ten.end(),Sorting);
		
		for(int iter = 0; iter < top_ten.size(); iter++)
		{
			print_highscore(hwnd, top_ten[iter],iter);
		}
		return true;
	}*/
	return false;
}

bool EraseScreen(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect)
{
	hdc = GetDC(hwnd);
	ValidateRect(hwnd,&rect);
	GetClientRect(hwnd,&rect);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	return true;
}

// void GamePaint() ser till att rita grafiken till skärmen

bool GamePaint(HINSTANCE hInstance, HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect,int temp )
{
	long t3=timeGetTime();

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
					//ShowBitmapResource(hInstance, hdc,row*Laby.block_size,col*Laby.block_size,IDB_WALL);
					SetPixel(hdc,740+row*2,100+col*2,RGB(255,0,255));
				}
				if(Laby.levelFigure[col].at(row) == 3)
				{
					Rectangle(hdc, col*Laby.block_size, row*Laby.block_size, (col*Laby.block_size)+Laby.block_size, (col*Laby.block_size) + Laby.block_size);
				}
			}
	}

	HPEN white_pen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	SelectObject(hdc,white_pen);
	//Rectangle(hdc,xprev,yprev,xprev+Laby.block_size,yprev+Laby.block_size);
	Rectangle(hdc,Player.GetPX(),Player.GetPY(),Player.GetPX()+Laby.block_size,Player.GetPY()+Laby.block_size);
	//ShowBitmapResource(hInstance, hdc,PlayerX,PlayerY,IDB_PLAYER);
	//ShowBitmapResource(hInstance, hdc,Player.GetX(),Player.GetY(),IDB_PLAYER);
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

// Hanterar Kollisions detektionen för spelet och kollar även ifall man nåt målet
// anropet till Goal skall dock flyttas och troligen vara i main loopen istället.
// Kan finnas en bugg i den med att man får ett mindre move än vad man egentligen
// har tagit.

bool GameCollision(int NextX, int NextY)
{
	long t5 =timeGetTime();
	if(Laby.levelFigure[NextX].at(NextY) == 1)
	{
		return true;
	}
	else
	{
		Player.SetMoves();
		return false;
	}
	long t6 =timeGetTime();
	long elapsed=t6-t5;
	timePaint = t6-t5;
}

// BOOL CALLBACK NameDlgProc() är tänkt att användas för att ta emot inmatning
// av spelarens namn innan spelet börjar, ser även till att man faktiskt fyller
// i ett namn.

BOOL CALLBACK NameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		{
			if (GetDlgCtrlID((HWND) wParam) != IDC_NAME) 
		    {
				SetFocus(GetDlgItem(hDlg, IDC_NAME)); 
				return false; 
			}			
		}
		break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
/*					if((GetDlgItemText(hDlg,IDC_NAME,playername, 64)) != 0)
					{
						for(int i=0; i < 64; i++)
						{
							playername[i] = '\0';
						}
						GetDlgItemText(hDlg,IDC_NAME, playername, 64);
						EndDialog(hDlg,0);
					}*/
					return true;
			}
			break;
	}
	return false;
};