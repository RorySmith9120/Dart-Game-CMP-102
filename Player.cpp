#include "Player.h"
#include "Throw.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <array>
using namespace std;

//Constructor
Player::Player(string name, int percentage)
{
	Name = name;
	Percentage = percentage;
}

//Destructor
Player::~Player()
{
}

//Gets player percentage
int Player::getPercentage()
{
	return Percentage;
}

//Gets number of throws
int Player::getNumOfThrows()
{
	return NumOfThrows;
}

//Gets current score
int Player::getScore()
{
	return Score;
}

//Set current score
void Player::setScore(int score)
{
	Score = score;
}

//Gets Number of Bullseyes
int Player::getNumOfBulls()
{
	return NumOfBulls;
}

//Sets Number of Bullseyes
void Player::setNumOfBulls(int bullNum)
{
	NumOfBulls = bullNum;
}

//Sets number of throws
void Player::setNumOfThrows(int throwNum)
{
	NumOfThrows = throwNum;

}

//Sets number of wins
void Player::setWins(int wins)
{
	Wins = wins;
}

//Gets number of wins
int Player::getWins()
{
	return Wins;
}

//Gets name
string Player::getName()
{
	return Name;
}

//Gets best of three wins
int Player::getBOTWins()
{
	return BOTWins;
}

//Sets best of three wins
void Player::setBOTWins(int BOTwins)
{
	BOTWins = BOTwins;
}

//Gets total score
int Player::getTotal()
{
	return Total;
}

//Sets total score
void Player::setTotal(int total)
{
	Total = total;
}

//Sets intital score
void Player::setScoreRead(int scoreread)
{
	ScoreRead = scoreread;
}

//Gets intial score
int Player::getScoreRead()
{
	return ScoreRead;
}

//Sets array
void Player::setArr(int ScoreArr[][2][3])
{
	memcpy(PlayerScoreArr, ScoreArr, 171 * 2 * 3 * sizeof(int));
}

//Sets safe array
void Player::setArrSafe(int ScoreArr[][2][3])
{
	memcpy(PlayerScoreArrSafe, ScoreArr, 171 * 2 * 3 * sizeof(int));
}

//Sets missing score
void Player::setScoreMiss(int miss)
{
	ScoreMiss = miss;
}

//Sets first hit true/false
void Player::setFirstHit(bool FirstHit)
{
	firstHit = FirstHit;
}

//Gets first hit true/false
bool Player::getFirstHit()
{
	return firstHit;
}

//Throws 1/2/3

int Player::DartRoute(int ThrowNum)
{
	//If number is a bogey number reduce score by 20
	if (ScoreRead == 169 || ScoreRead == 168 || ScoreRead == 166 || ScoreRead == 165 || ScoreRead == 163 || ScoreRead == 162 || ScoreRead == 159)
	{
		ScoreRead = ScoreRead - 20;
	}

	//Switch checks throwNum to check which throw it is then uses the values form the score array to make a throw
	switch (ThrowNum)
	{
	case 0:
		return Throw::dartType(ScoreArray[ScoreRead][1][0], ScoreArray[ScoreRead][0][0], Percentage);
		break;
	case 1:
		return Throw::dartType(ScoreArray[ScoreRead][1][1], ScoreArray[ScoreRead][0][1], Percentage);
		break;
	case 2:
		return Throw::dartType(ScoreArray[ScoreRead][1][2], ScoreArray[ScoreRead][0][2], Percentage);
		break;
	}
}

int Player::miss1(int ThrowNum)
{
	//If second throw is less than or equal to 122
	if (ScoreMiss <= 122)
	{
		//Switch checks throwNum to check which throw it is then uses the values from the score array to make a throw
		switch (ThrowNum)
		{
		case 1:
			return Throw::dartType(ScoreArray[ScoreMiss][1][0], ScoreArray[ScoreMiss][0][0], Percentage);
			break;
		case 2:
			return Throw::dartType(ScoreArray[ScoreMiss][1][1], ScoreArray[ScoreMiss][0][1], Percentage);
			break;
		}
	}
	
	//If the scoremiss is more than 122 try and throw for the largest score
	else if (ScoreMiss > 122)
	{
		switch (ThrowNum)
		{
		case 1:
			return Throw::dartType(3, 20, Percentage);
			break;
		case 2:
			return Throw::dartType(3, 20, Percentage);
			break;
		}
	}
	//If the score is more than 98 
}
int Player::miss1and2(int ThrowNum)
{	
	//If the score is less than or equal to 20 or equal to 50 then use array scores
	if (ScoreMiss <= 20 || ScoreMiss == 50)
	{
		return Throw::dartType(ScoreArray[ScoreMiss][1][0], ScoreArray[ScoreMiss][0][0], Percentage);
	}
	
	//If score miss is more than 62 try and throw for the largest score
	else if (ScoreMiss > 62)
	{
		return Throw::dartType(3, 20, Percentage);
	}

	//If the score is more than 20 use the score array
	else if (ScoreMiss > 20)
	{
		return Throw::dartType(ScoreArray[ScoreMiss][1][0], ScoreArray[ScoreMiss][0][0], Percentage);
	}
	
}

//If safe is true use the safe array if safe is false use risky array
void Player::setSafe(bool safe)
{
	if (safe == false)
	{
		memcpy(ScoreArray, PlayerScoreArr, 171 * 2 * 3 * sizeof(int));
	}
	else if (safe == true)
	{
		memcpy(ScoreArray, PlayerScoreArrSafe, 171 * 2 * 3 * sizeof(int));
	}
}

//Same as dart route except instead of a score it returns the dart and throw type
int Player::GetDartRoute(int ThrowNum, int throwOrDart)
{
	if (ScoreRead == 169 || ScoreRead == 168 || ScoreRead == 166 || ScoreRead == 165 || ScoreRead == 163 || ScoreRead == 162 || ScoreRead == 159)
	{
		ScoreRead = ScoreRead - 20;
	}

	switch (ThrowNum)
	{
	case 0:
		return ScoreArray[ScoreRead][throwOrDart][0];
		break;
	case 1:
		return ScoreArray[ScoreRead][throwOrDart][1];
		break;
	case 2:
		return ScoreArray[ScoreRead][throwOrDart][2];
		break;
	}
}