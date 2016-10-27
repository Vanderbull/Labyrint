//#include <vld.h>
#include <iostream>
#include <ctime>
using namespace std;

#include <windows.h>

#include "resource.h"

#include "gameengine.h"
#include "variables.h"
#include "DirectInputManager.h"

class Particle
{
    private:
    //Offsets
    int x, y;
    
    //Current frame of animation
    int frame;
    
    //Type of particle
    //SDL_Surface *type;
    
    public:
    //Constructor
    Particle( int X, int Y );
    
    //Shows the particle
    void show();

    //Checks if particle is dead
    bool is_dead();
};
//The dot
class Dot
{
    private:
    //The offsets
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;
    
    //The particles
    Particle *particles[ 20 ];
    
    public:
    //Initializes
    Dot();
    
    //Cleans up particles
    ~Dot();
    
    //Handles keypresses
    void handle_input();
    
    //Shows the particles
    void show_particles();
    
    //Shows the dot
    void show();
};
// Huvud Device handle
HDC	hdc=0;
Particle::Particle( int X, int Y )
{
    //Set offsets
    x = X - 5 + ( rand() % 25 );
    y = Y - 5 + ( rand() % 25 );
    
    //Initialize animation
    frame = rand() % 5;
    
    //Set type
    switch( rand() % 3 )
    {
        case 0: SetPixel(hdc,x,y,RGB(255,0,0)); break;
        case 1: SetPixel(hdc,x,y,RGB(0,255,0)); break;
        case 2: SetPixel(hdc,x,y,RGB(0,0,255)); break;
    }
}

void Particle::show()
{
    //Show image
    //apply_surface( x, y, type, screen );
    
    //Show shimmer
    if( frame % 2 == 0 )
    {
		SetPixel(hdc,x,y,RGB(255,255,255));
        //apply_surface( x, y, shimmer, screen );    
    }
    
    //Animate
    frame++;
}

bool Particle::is_dead()
{
    if( frame > 10 )
    {
        return true;    
    }
    
    return false;
}

HINSTANCE		hInst;
HWND			hwnd;
static TCHAR	szAppName[] = TEXT("Labyrint") ;
//static HINSTANCE hInstance;
static HICON	hIcon;
static HMENU	hMenu;
static int		cxIcon, cyIcon, cxClient, cyClient ;


	
PAINTSTRUCT		ps ;

// rect for holding window size
RECT rect;


int roc = 0;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

/* Get a reference to the DirectInput Manager */	
static diManager& mgr= diManager::getInstance();

/* Get a reference to the DirectInput Manager */	
static Engine& Ingine= Engine::getInstance();
//	Main window entry point

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow) 
{
	MSG			msg = {0};
	WNDCLASSEX	wndclass ;

	wndclass.cbSize			= sizeof(WNDCLASSEX);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc	= WndProc ;
	wndclass.cbClsExtra		= 0 ;
	wndclass.cbWndExtra		= 0 ;
	wndclass.hInstance		= hInstance ;
	wndclass.hIcon			= LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON)) ;
	wndclass.hIconSm       = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndclass.hCursor		= LoadCursor (hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wndclass.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName	= MAKEINTRESOURCE (IDR_MENU) ;
	wndclass.lpszClassName	= szAppName ;

	if (!RegisterClassEx (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires a advanced windows"),
					szAppName, MB_ICONERROR) ;
		return 0;
	}


	hwnd = CreateWindowEx(
						 0,
						 szAppName,							// Window class name
						 szAppName,							//window caption
						 WS_OVERLAPPEDWINDOW,
						 0,
						 0,
						 GetSystemMetrics(SM_CXSCREEN),				//GetSystemMetrics(SM_CXSCREEN),
						 GetSystemMetrics(SM_CYSCREEN),				//GetSystemMetrics(SM_CYSCREEN),
						 NULL,
						 NULL,
						 hInstance,
						 NULL) ;

	srand ( time(0) );
	ShowWindow(hwnd, iCmdShow) ;
	UpdateWindow(hwnd);

	Particle balle(100,100);;

	Ingine.init();
	timeInit = Ingine.timePainty();

	if( ! (GameInit(hwnd) ) )
		SendMessage(hwnd,WM_QUIT,NULL,NULL);

	mgr.InitDirectInput(hInstance,hwnd,0x00000002L);
	
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage (&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		timePaint = Ingine.timePainty();
		mgr.ProcessKeyboardInput();

		if(mgr.isKeyDown(DIK_RIGHT))
		{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
		}
		if(mgr.isKeyDown(DIK_LEFT))
		{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 - 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()-Laby.block_size,Player.GetY());
			}
		}
		if(mgr.isKeyDown(DIK_UP))
		{
			roc++;
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32, Player.GetY()/32 - 1))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX(),Player.GetY() - Laby.block_size);
			}
		}
		if(mgr.isKeyDown(DIK_DOWN))
		{
			roc--;
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32, Player.GetY()/32 + 1))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX(),Player.GetY() + Laby.block_size);
			}
		}

		int x = rand()%255;
		int y = rand()%255;
		SetPixel(hdc,x,y,RGB(255,0,0));

		Ingine.paint(hInstance,hwnd,hdc,ps,rect,roc);
		debug_info(hwnd);

		Laby.Goal(hwnd,hInstance, "R",Player.GetX()/32,Player.GetY()/32,0);		
	}
	return(msg.wParam);
}

// LRESULT CALLBACK WndProc() sköter grovjobbet

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	POINT point;
	switch (message)
	{
	case WM_CREATE:

		hIcon = LoadIcon (hInst, MAKEINTRESOURCE (IDI_ICON));
		cxIcon = GetSystemMetrics(SM_CXICON);
		cyIcon = GetSystemMetrics(SM_CYICON);

		//Standard menu with a popup
		hMenu = LoadMenu(hInst, MAKEINTRESOURCE (IDR_MENU));
		hMenu = GetSubMenu(hMenu, 0);
		return 0;

	case WM_SETFOCUS:
		return 0;

		case WM_KEYDOWN:
			switch(wParam) 
			{
				case VK_RIGHT:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
					}
					break;
					
				
				case VK_LEFT:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
					}
					break;

				case VK_UP:
					{
						roc++;
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
					}
					break;
				case VK_DOWN:
					{
						roc--;
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
					}
					break;
				default:
					break; //Everything else
			} 
		return 0; 


	case WM_RBUTTONUP:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		ClientToScreen(hwnd,&point);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
		return 0;

	case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_RIGHT:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
						SetFocus(hwnd);
					}
					break;
					
				
				case ID_LEFT:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
						SetFocus(hwnd);
					}
					break;

				case ID_UP:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
						SetFocus(hwnd);
					}
					break;
				case ID_DOWN:
					{
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
			}
						SetFocus(hwnd);
					}
					break;

			case IDM_APP_EXIT:
				SendMessage(hwnd,WM_CLOSE,0,0);
				return 0;

			case IDM_LEVEL_LOAD:
				{
					Ingine.erase_screen(hwnd,hdc,ps,rect);
					//EraseScreen(hwnd,hdc,ps,rect);
					//Laby.RandomizeMap();
					MessageBox(0,"Coming soon", "Loading level",MB_ICONINFORMATION);
					DialogBox (hInst, MAKEINTRESOURCE(IDD_DIALOG2), NULL, NameDlgProc);
					return 0;
				}
			case IDM_HIGHSCORE:
				GameLoading(hwnd);
				return 0;

			case IDM_ABOUT:
				MessageBox(hwnd,"Created by Rickard Skeppstrom\n2007(c)","About",MB_ICONINFORMATION);
				return 0;

			case IDM_VERSION:
				MessageBox(hwnd,"Version 1.2","Version",MB_ICONINFORMATION);
				return 0;
		
			default:
				break;
				InvalidateRect(hwnd,NULL,TRUE);
			}
			return 0;
		

	case WM_SIZE:
		cxClient = LOWORD(lParam) ;
		cyClient = HIWORD(lParam) ;
		return 0;

	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		//Ingine.paint(hInst,hwnd,hdc,ps,rect,roc);
		//GamePaint(hInst, hwnd,hdc,ps,rect,roc);

		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
