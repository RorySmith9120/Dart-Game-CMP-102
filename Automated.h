#include <iostream>
#include <string>

#pragma once
class Automated
{
public:
	//Public functions
	void Auto(int RiskArr[][2][3], int SafeArr[][2][3]);
	void countFreq(int results[][2]);
	
private:
	//Private vairables
	int throwScore[3] = { 0,0,0 };
	int throwFirst = 0;
	int count = 0;
	int game = 0;	
	bool missed1 = false;
};

