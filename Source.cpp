
#include <iostream>
#include "DartGame.h"
#include "windows.h"
using namespace std;

//Object pointer
DartGame* Games;

int main()
{
	//Initialses rand
	srand(time(0));
	//Sets console text colour to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	//Creates object
	Games = new DartGame();

	//Calls game function from Games object
	Games->Game();
}