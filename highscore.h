
#include <iostream>
#include <string>		// for string variables
#include <vector>		// vector<Highscore>
#include <algorithm>	// for_each() + sort()
#include <iomanip>
#include <fstream>
#include<sstream>
#include <windows.h>

using namespace std;

struct scores
{
	std::string name;
};
// Descending date sorting function
struct SDescendingDateSort
{
	bool operator()(const scores& rpStart, const scores& rpEnd)
     {
		 //return true;
		 return rpStart.name > rpEnd.name;
     }
};


class Hiscore : public std::vector<scores>
{
public:
	~Hiscore(void);
	Hiscore(void);
	bool printer(HWND hwnd, const scores& test, int iterator );
   // singleton stuff
//	static Hiscore& getInstance() { static Hiscore pInstance; return pInstance;}

private:

	//
};