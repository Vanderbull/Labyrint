#include <windows.h>

class Player
{
public:
	~Player(void);
	//singelton stuff
	static Player& getInstance() { static Player pInstance; return pInstance;}

	int GetMoves();
	bool SetMoves();
	bool SetXY(int iX,int iY);
	bool SetLastXY();
	int GetX();
	int GetY();
	int GetPreviousX();
	int GetpreviousY();
private:
	Player(void);

	int mMoves;
	int mX,mY;
	int mXPrev,mYPrev;
};
