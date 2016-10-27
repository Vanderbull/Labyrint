#include ".\labyrint.h"

extern HINSTANCE hInst;				// holds the instance for this app

Labyrint::Labyrint() : block_size(32)
{
}

int Labyrint::size()
{
	return block_size;
}

// Måste se till att den bara randomizar mitten inte kanterna
bool Labyrint::RandomizeMap()
{
	int		col;
	int		row;

	levelFigure.clear();

	for(col = 0; col < levelFigure.size()-1; col++)
	{
		levelFigure.push_back(vector <int>());

		for(row = 0; row < levelFigure.size()-1; row++)
		{
			if(row == 0 || row == 19 || col == 0 || col == 19)
				levelFigure[col].push_back(1);
			else
				levelFigure[col].push_back(rand()%2);		
		}
	}

	return true;
}

bool Labyrint::LoadMap(std::string file)
{
	int		col;
	int		row;
	char	c;

	ifstream fin(file.c_str());

	if ( !fin.is_open() ) 
	{
		return false;
	}

	for(col = 0; col < 21; col++)
	{
		levelFigure.push_back(vector <int>());

		for(row = 0; row < 21; row++)
		{
			c = fin.get();		
			
			levelFigure[col].push_back(atoi(&c));		
		}
	}
	
	fin.close();

	return true;
}

bool Labyrint::StartLocation()
{
	for(int col = 0; col < 21; col++)
	{
		for(int row = 0; row < 21; row++)
		{
			if(levelFigure[col].at(row) == 2)
			{
				xcoord = row*block_size;
				ycoord = col*block_size;
			}
		}
	}
	return true;
}

bool Labyrint::Collision(int xcoord, int ycoord)
{
	if(levelFigure[xcoord].at(ycoord) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Labyrint::Goal(HWND hwnd, HINSTANCE hInstance, std::string szPlayerName, int x, int y, int moves)
{
	if(levelFigure[x].at(y) == 3)
	{
		PostQuitMessage(0);
	}
	return true;
}

bool Labyrint::Init()
{
	return true;
}
Labyrint::~Labyrint()
{
}