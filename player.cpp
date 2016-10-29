#include ".\player.h"

extern HINSTANCE hInst;				// holds the instance for this app

Player::Player() : mMoves(0)
{
	std::cout << "Player is growing up to be a strong man..." << std::endl;
	mXPrev = 0;
	mYPrev = 0;
}

Player::~Player()
{
	std::cout << "Player is buried and lost forever..." << std:endl;
}

int Player::GetMoves()
{
	return mMoves;
}

bool Player::SetMoves()
{
	mMoves++;
	return true;
}

bool Player::SetXY(int iX, int iY)
{
	x = iX;
	y = iY;
	return true;
}

bool Player::SetLastXY()
{
	mXPrev = x;
	mYPrev = y;
	return true;
}

int Player::GetX()
{
	return x;
}
int Player::GetY()
{
	return y;
}
int Player::GetPX()
{
	return mXPrev;
}
int Player::GetPY()
{
	return mYPrev;
}
