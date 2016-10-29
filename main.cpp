#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

//Basics
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_revision.h>

#include <iostream>
#include <ctime>
using namespace std;

#include "gameengine.h"
#include "DirectInputManager.h"
#include "Particle.h"
#include "Dot.h"

bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();


// main device handle
HDC	hdc=0;
HINSTANCE		hInst;
HWND			hwnd;
static TCHAR	szAppName[] = TEXT("Labyrint") ;
//static HINSTANCE hInstance;
static HICON	hIcon;
static HMENU	hMenu;
static int cxIcon, cyIcon, cxClient, cyClient ;
PAINTSTRUCT ps;

// rect for holding window size
RECT rect;

int roc = 0;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

/* Get a reference to the DirectInput Manager */	
static diManager& mgr= diManager::getInstance();

/* Get a reference to the DirectInput Manager */	
static Engine& Ingine= Engine::getInstance();
//	Main window entry point

int main( int argc, char* args[] )
{

	if ( !InitEverything() )
	{
		return -1;
	}
	
	while ( loop )
	{
		SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
			{
				loop = false;
			}
			else if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
                    			case SDLK_ESCAPE:
                        		exit(1);
                        		break;
					case SDLK_RIGHT:
						Player.SetLastXY();
						if(!Laby.Collision(Player.GetX()/32 + 1, Player.GetY()/32))
						{
							Player.SetMoves();
							Player.SetXY(Player.GetX()+Laby.block_size,Player.GetY());
						}
					break;
					case SDLK_LEFT:
						Player.SetLastXY();
						if(!Laby.Collision(Player.GetX()/32 - 1, Player.GetY()/32))
						{
							Player.SetMoves();
							Player.SetXY(Player.GetX()-Laby.block_size,Player.GetY());
						}
					break;
					case SDLK_DOWN:
						roc--;
						Player.SetLastXY();
						if(!Laby.Collision(Player.GetX()/32, Player.GetY()/32 + 1))
						{
							Player.SetMoves();
							Player.SetXY(Player.GetX(),Player.GetY() + Laby.block_size);
						}
					break;
					case SDLK_UP:
			roc++;
			Player.SetLastXY();
			if(!Laby.Collision(Player.GetX()/32, Player.GetY()/32 - 1))
			{
				Player.SetMoves();
				Player.SetXY(Player.GetX(),Player.GetY() - Laby.block_size);
			}
						break;
                    			case SDLK_KP_MINUS:
                        		break;
                    			case SDLK_KP_PLUS:
                        		break;
					default :
					break;
				}
			}
		}
	}
	
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage (&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

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
			EndPaint(hwnd,&ps);
		return 0;

		case WM_DESTROY:
			PostQuitMessage (0) ;
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

bool InitEverything()
{
	if ( !InitSDL() )
		return false;

	if ( !CreateWindow() )
		return false;

	if ( !CreateRenderer() )
		return false;

	SetupRenderer();

	return true;
}

bool InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}

    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
		return false;
    }

	return true;
}

bool CreateWindow()
{
	//window = SDL_CreateWindow( "Server", posX, posY, sizeX, sizeY, 0 );
	window = SDL_CreateWindow( "Labyrint", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0 );

	if ( window == nullptr )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}

	SDL_Surface *surface;     // Declare an SDL_Surface to be filled in with pixel data from an image file
/*
  Uint16 pixels[16*16] = {  // ...or with raw pixel data:
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
    0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
    0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
    0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
    0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
    0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
    0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
    0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
    0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
    0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
    0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
    0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
    0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
    0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
    0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
    0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
    0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
    0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
    0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
    0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
    0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
  };
  */
  //surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);

    surface = IMG_Load( "./assets/atari.png" );

    // The icon is attached to the window pointer
    SDL_SetWindowIcon(window, surface);

    // ...and the surface containing the icon pixel data is no longer required.
    SDL_FreeSurface(surface);

    return true;
}

bool CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer == nullptr )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
	return true;
}

void SetupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, windowRect.w, windowRect.h );
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	// Set color of renderer to red
	//SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
}

