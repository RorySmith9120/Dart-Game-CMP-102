#pragma once
class DartGame
{
public:
	//Declares public functions
	void Game();
	void DartCheckout();
	void Rules();
private:
	//Declares private variables
	int ScoreArr[171][2][3];
	int count2 = 0;
	int value = 0;
	int ScoreArrRisk[171][2][3] = { 0 };
	int ScoreArrSafe[171][2][3] = { 0 };
	int ArrNum;
	int opt;
};

