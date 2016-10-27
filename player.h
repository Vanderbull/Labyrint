#include <windows.h>

class Player
{
public:
	~Player(void);
	//singelton stuff
	static Player& getInstance() { static Player pInstance; return pInstance;}

	int GetMoves();
	bool SetMoves();
	bool SetXY(int new_x,int new_y);
	bool SetLastXY();
	int GetX();
	int GetY();
	int GetPX();
	int GetPY();
private:
	Player(void);

	int m_Moves;
	int x,y;
	int xprev,yprev;
};