#pragma once
#include "Throw.h"
#include <iostream>
#include <string>
using namespace std;

class Player:
	public Throw
{
public:

	//Constructor/Destructor
	Player(string name, int percentage);
	~Player();

	//Public functions

	string getName();
	void setScoreMiss(int score);
	int getPercentage();
	int getNumOfThrows();
	int getScore();
	void setScore(int score);
	void setScoreRead(int scoreread);
	int getScoreRead();
	int getNumOfBulls();
	void setNumOfBulls(int bullNum);
	void setNumOfThrows(int throwNum);
	int getWins();
	void setWins(int wins);
	int getBOTWins();
	void setBOTWins(int BOTwins);
	void setTotal(int total);
	int getTotal();
	void setArrSafe(int ScoreArr[][2][3]);
	void setArr(int ScoreArr[][2][3]);
	void setFirstHit(bool firstHit);
	bool getFirstHit();
	
	//Fuctions for throw 1/2/3 Automated

	int DartRoute(int ThrowNum);
	int miss1(int ThrowNum);
	int miss1and2(int ThrowNum);
	void setSafe(bool safe);

	//Functions for throw 1/2/3 Interactive

	int GetDartRoute(int ThrowNum, int throwOrDart);


private:

	//Private variables
	bool firstHit = true;
	int ScoreArray[171][2][3];
	int ScoreMiss;
	int PlayerScoreArr[171][2][3];
	int PlayerScoreArrSafe[171][2][3];
	int NumOfThrows = 0;
	int Score;
	int ScoreRead;
	int NumOfBulls = 0;
	string Name;
	int Percentage = 0;
	int Wins = 0;
	int BOTWins = 0;
	int Total = 0;
	int value;
};

