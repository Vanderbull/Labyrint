#include <windows.h>
#include <vector>
#include <fstream>
using namespace std;

class Labyrint
{
public:
	~Labyrint(void);
   // singleton stuff
	static Labyrint& getInstance() { static Labyrint pInstance; return pInstance;}

	vector<vector<int> > levelFigure;
	
	int size();
	bool LoadMap(std::string file);
	bool RandomizeMap();
	bool StartLocation();
	bool Collision(int xcoord, int ycoord);
	bool Init();
	bool Goal(HWND hwnd, HINSTANCE hInstance, std::string szPlayerName, int x, int y, int moves);
	int xcoord;
	int ycoord;
	const int block_size;

private:

	char	playername[64];

	Labyrint(void);
};