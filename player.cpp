#include ".\player.h"

extern HINSTANCE hInst;				// holds the instance for this app

Player::Player() : m_Moves(0)
{
	xprev = 0;
	yprev = 0;
}

Player::~Player()
{
}

int Player::GetMoves()
{
	return m_Moves;
}

bool Player::SetMoves()
{
	m_Moves++;
	return true;
}

bool Player::SetXY(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
	return true;
}

bool Player::SetLastXY()
{
	xprev = x;
	yprev = y;
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
	return xprev;
}
int Player::GetPY()
{
	return yprev;
}