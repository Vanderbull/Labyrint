#include <windows.h>
#include <vector>
#include <fstream>
using namespace std;
#include "resource.h"
#include "player.h"
#include "labyrint.h"


//#include "ShowBitmapResource.h"

// Get a reference

static Player& Player = Player::getInstance();

// Get a reference

static Labyrint& Laby = Labyrint::getInstance();

class Engine
{
public:
	~Engine(void);
	//singelton stuff
	static Engine& getInstance() { static Engine pInstance; return pInstance;}

	bool init();
	bool paint(HINSTANCE hInstance, HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect,int temp);
	bool erase_screen(HWND hwnd, HDC hdc, PAINTSTRUCT ps, RECT rect);
	bool collision(int NextX, int NextY);
	int timePainty();

private:

	long timePaint;
	long timeInit;
	long timeCollision;

	Engine(void);
};