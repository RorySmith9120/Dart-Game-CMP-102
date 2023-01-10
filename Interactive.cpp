#include "Interactive.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Throw.h"
#include "Player.h"
#include "windows.h"

//Namespace
using namespace std;

//Object pointers

Player* A2;
Player* B2;

void Interactive::Interact(int RiskArr[][2][3], int SafeArr[][2][3])
{
	//Changes console text colour to green
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

	//Prints ascii title
	cout << R"(
 ______          __                                 __                          
/\__  _\        /\ \__                             /\ \__  __                   
\/_/\ \/     ___\ \ ,_\    __   _ __    __      ___\ \ ,_\/\_\  __  __     __   
   \ \ \   /' _ `\ \ \/  /'__`\/\`'__\/'__`\   /'___\ \ \/\/\ \/\ \/\ \  /'__`\ 
    \_\ \__/\ \/\ \ \ \_/\  __/\ \ \//\ \L\.\_/\ \__/\ \ \_\ \ \ \ \_/ |/\  __/ 
    /\_____\ \_\ \_\ \__\ \____\\ \_\\ \__/.\_\ \____\\ \__\\ \_\ \___/ \ \____\
    \/_____/\/_/\/_/\/__/\/____/ \/_/ \/__/\/_/\/____/ \/__/ \/_/\/__/   \/____/                                                                 
)";
	//Changes console text colour back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "Please enter Joe's accuracy" << endl;

	//While Accuracy is out of params keep asking for an input
	while (Accuracy < 1 || Accuracy > 100)
	{
		cout << ">";
		cin >> Accuracy;
	}

	//Creates object A2
	A2 = new Player("Joe", Accuracy);

	//Sets accuracy outside params for upcoming while loop
	Accuracy = 101;
	cout << "Please enter Sid's accuracy" << endl;

	//While Accuracy is out of params keep asking for an input
	while (Accuracy < 1 || Accuracy > 100)
	{
		cout << ">";
		cin >> Accuracy;
	}

	//Creates object B2
	B2 = new Player("Sid", Accuracy);

	//Sets changes arr for both player objects to the array passed into this function
	A2->setArr(RiskArr);
	B2->setArr(RiskArr);
	A2->setArrSafe(SafeArr);
	B2->setArrSafe(SafeArr);

	cout << "How many games would you like to play?" << endl;

	//Sets the number of games, unless the values is less than 1
	while (NumGames < 1)
	{	
		cout << ">";
		cin >> NumGames;
	}

	//50:50 coin toss for first throw
	int r = rand() % 2 + 1;

	//Clears the screen
	system("CLS");

	//Prints who got the first throw
	if (r == 1)
	{
		cout << "You get to throw first" << endl;
	}
	else
	{
		cout << "Your opponent had the first 3 throws" << endl;
	}

	//Sets the first throw to the 50:50 result
	throwFirst = r;

	//Loop noOfGames times

	for (int i = 0; i < NumGames; i++)
	{		
			//Resets scores for both players to 301
			A2->setScore(501);
			B2->setScore(501);

			//While the scores of both players are more than one, meaning one of them hasn't won then continue to loop the code below
			LOOP:while (A2->getScore() > 0 && B2->getScore() > 0)
			{
				switch (throwFirst)
				{
				case 1:

					//If the score of player one is more than 0 execute the code below
					if (A2->getScore() > 0)
					{
						//Set the starting score before any throws to ScoreRead
						A2->setScoreRead(A2->getScore());

						//If player A score is ahead by 180 points then play safe
						if (B2->getScore() > (A2->getScore() + 180))
						{
							A2->setSafe(true);
						}
						else
						{
							A2->setSafe(false);
						}
						
						//Resets the number of throw at the start of the round
						ThrowNum = 0;

						//Loop 3 times
						for (count = 0; count < 3; count++)
						{

							//Increments the throw to let the player know what throw out of 3 they are on
							ThrowNum += 1;

							//Lets the player know who has what accuracy
							cout << A2->getName() << "|Accuracy:" << A2->getPercentage() << " " << B2->getName() << "|Accuracy:" << B2->getPercentage() << endl;

							//Lets the player know what their and their opponents current score is
							cout << "Throw: " << ThrowNum << endl << "Score " << A2->getName() <<": " << A2->getScore() << endl << "Score " << B2->getName() << ": " << B2->getScore() << endl;

							//Prints the dartboard passing in the type of dart and throw for the last throw
							PrintDartBoard(A2->getDart(), A2->getThrowType());

							cout << "Recommended throws for this round: ";

							//Checks if the player needs to double in
							if (A2->getScore() == 501)
							{
								A2->setFirstHit(true);
							}
							else
							{
								A2->setFirstHit(false);
							}

							//Recommends how to double in for the first 3 throws
							if (A2->getScoreRead() == 501)
							{
								cout << "Bullseye";
								cout << " ";
								cout << "T20";
								cout << " ";
								cout << "T20" << endl;
							}	
							//If the orginal score is below or equal to 170 grab the precalculated throws as suggestions
							else if (A2->getScoreRead() <= 170)
							{
								PrintThrow(A2->GetDartRoute(0, 0), A2->GetDartRoute(0, 1));
								cout << " ";
								PrintThrow(A2->GetDartRoute(1, 0), A2->GetDartRoute(1, 1));
								cout << " ";
								PrintThrow(A2->GetDartRoute(2, 0), A2->GetDartRoute(2, 1));
								cout << endl;
							}
							//If the original score is more than 170 throw for the maximum score
							else if (A2->getScoreRead() > 170)
							{
								cout << "T20";
								cout << " ";
								cout << "T20";
								cout << " ";
								cout << "T20" << endl;
							}							

							//Sets multiplier and dart to 0 so new values can be input
							multiplier = 0;
							dart = 0;

							cout << "Enter multiplier 1-3, or enter 4 for a bullseye" << endl;

							//While input outside params, loop
							while (multiplier < 1 || multiplier > 4)
							{
								cout << ">";
								cin >> multiplier;
							}

							//If the mutiplier is not 4(Number for bullseye) then ask for dart and loop while input outside params
							if (multiplier != 4)
							{				
								cout << "Enter dart" << endl;
								while (dart < 1 || dart > 20)
								{
									cout << ">";
									cin >> dart;
								}
							}

							//Throw the dart specified by the player
							throwScore[count] = A2->dartType(multiplier, dart, A2->getPercentage());

							//Remove the dart score from player's current score
							A2->setScore(A2->getScore() - throwScore[count]);

							//If the score has reached 0 and the type of throw is a double or bull then goto LOOP (Look Upwards^^)
							if (A2->getScore() == 0 && (A2->getThrowType() == 2 || A2->getThrowType() == 4))
							{
								B2->setNumOfThrows(B2->getNumOfThrows() + 3);
								goto LOOP;
							}
							//Otherwise if the score is less than 1 or its the first/last hit and you missed or if it's the first/last hit and not a double or a bull then reset the score to the inital score
							else if (A2->getScore() <= 1 || ( (A2->getFirstHit() || A2->getScore() == 0) && !A2->getHit() ) || ( (A2->getFirstHit() || A2->getScore() == 0) && (multiplier != 2 && multiplier != 4) ))
							{
								A2->setScore(A2->getScoreRead());
							}

							//Increase number of throws
							A2->setNumOfThrows(A2->getNumOfThrows() + 1);

							//Clear the screen
							system("CLS");
						}
					}

					case 2:
						//If the score of player one is more than 0 execute the code below
						if (B2->getScore() > 0)
						{
							B2->setScoreRead(B2->getScore());
							//Loop 3 times
							for (count = 0; count < 3; count++)
							{
								//Checks if the player needs to double in
								if (B2->getScore() == 501 || B2->getScore() == 50)
								{
									B2->setFirstHit(true);
								}
								else
								{
									B2->setFirstHit(false);
								}

								//If it is the first hit throw for a bull
								if (B2->getFirstHit() == true)
								{
									throwScore[count] = B2->throw_bull(B2->getPercentage());
								}
								//Ottherwise if the score is less than 41 check if the score can be divided by 2 if so then throw the double
								else if (B2->getScore() < 41)
								{
									throwScore[count] = B2->dartType(2, (B2->getScore() / 2), B2->getPercentage());

									//If it couldn't be divided then check the score and try make the maximum score without going below 2
									if (throwScore[count] != B2->getScore())
									{
										if (B2->getScore() < 21)
										{
											throwScore[count] = B2->dartType(1, (B2->getScore() - 2), B2->getPercentage());
										}
										else if (B2->getScore() > 21)
										{
											throwScore[count] = B2->dartType(1, 20, B2->getPercentage());
										}
										else if (B2->getScore() == 21)
										{
											throwScore[count] = B2->dartType(1, 19, B2->getPercentage());
										}
									}
								}
								//Try make the maximum score without going below 2
								else if (B2->getScore() >= 60)
								{
									throwScore[count] = B2->dartType(3, 20, B2->getPercentage());
								}
								else if (B2->getScore() > 41)
								{
									throwScore[count] = B2->dartType(2, 20, B2->getPercentage());
								}
								else if (B2->getScore() == 41)
								{
									throwScore[count] = B2->dartType(2, 19, B2->getPercentage());
								}

								//Remove throwscore from current score

								B2->setScore(B2->getScore() - throwScore[count]);


								//If the score has reached 0 and the type of throw is a double or bull then goto LOOP (Look Upwards^^)
								if (B2->getScore() == 0 && (B2->getThrowType() == 2 || B2->getThrowType() == 4))
								{
									A2->setNumOfThrows(A2->getNumOfThrows() + 3);
									goto LOOP;
								}
								//If the score is less than 1 or it's the first/last hit and you missed reset the score to the initial score
								else if (B2->getScore() <= 1 || ((B2->getFirstHit() || B2->getScore() == 0) && !B2->getHit()))
								{
									B2->setScore(B2->getScoreRead());
								}

								//Increase number of throws
								B2->setNumOfThrows(B2->getNumOfThrows() + 1);
							}
							//Reset the 3 throws scores for this round to 0
							throwScore[0] = 0;
							throwScore[1] = 0;
							throwScore[2] = 0;
						}
					}

					//Clears the screen
					system("CLS");

					//Set the first throw back to 1 if the second player got the first throw
					throwFirst = 1;

					//End of round
				}

				//Clear the screen
				system("CLS");

				//Checks players number of throws and gives the player with the least a win 
				if (A2->getNumOfThrows() < B2->getNumOfThrows())
				{
					A2->setWins(A2->getWins() + 1);
					cout << A2->getName() << " won this round" << endl;
				}
				else if (B2->getNumOfThrows() < A2->getNumOfThrows())
				{
					B2->setWins(B2->getWins() + 1);
					cout << B2->getName() <<" won this round" << endl;
				}
				else if (A2->getNumOfThrows() == B2->getNumOfThrows())
				{
					cout << "This round was a draw" << endl;
				}			
		}

		//Clear the screen
		system("CLS");

		//Prints player's names and wins
		cout << A2->getName() << ":" << B2->getName() << endl;

		cout << A2->getWins() << ":" << B2->getWins() << endl;

	cout << endl << "Results Loaded Successfully!" << endl;
	cout << "Press enter to return to the main menu" << endl;

	//Clear the buffer with cin.ignore and use cin.get to make the user enter something
	cin.ignore();
	cin.get();

	//Clear the screen
	system("CLS");

	//Resets the accuract and number of games if the user wants to play this mode again
	Accuracy = 0;
	NumGames = 0;
}


void Interactive::PrintThrow(int dart, int throwtype)
{
	//Based on throw type prints character corresponding e.g D is double
	switch (throwtype)
	{
	case 1:
		cout << "S" << dart;
		break;
	case 2:
		cout << "D" << dart;
		break;
	case 3:
		cout << "T" << dart;
		break;
	case 4:
		cout << "BULL";
		break;
	}
}

void Interactive::PrintDartBoard(int dart, int throwtype)
{
	//Checks the throwtype and sets board locations based on what type and the size of the area printed in colour(add)
	switch (throwtype)
	{
	case 1:
		memcpy(TargetLocations, SingleLocations, 21 * 2 * sizeof(int));
		add = 1;
		break;
	case 2:
		memcpy(TargetLocations, DoubleLocations, 21 * 2 * sizeof(int));
		add = 1;
		break;
	case 3:
		memcpy(TargetLocations, TrebleLocations, 21 * 2 * sizeof(int));
		add = 0;
		break;
	case 4:
		add = 0;
		break;
	}

	//Initialses row and collums for the board
	const int rows = 29, columns = 69;

	//For each row
	for (int i = 0; i < rows; ++i)
	{
		//For each collumn
		for (int j = 0; j < columns; ++j)
		{
			//If the throwtype is a bullseye then use bull locations
			if (throwtype == 4 && (i == BullLocation[dart][0] || i == BullLocation[dart][0] + add) && (j == BullLocation[dart][1] || j == BullLocation[dart][1] + 1))
			{
				//If you hit print in screen otherwise print in red
				if (A2->getHit())
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				}
				cout << dartboard[i][j];
			}
			//If the throwtype is for but the player didnt hit the board print normally
			else if (throwtype == 4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << dartboard[i][j];
			}
			//Checks to see if its a target location to print in colour
			else if ((i == TargetLocations[dart][0] || i == TargetLocations[dart][0] + add) && (j == TargetLocations[dart][1] || j == TargetLocations[dart][1] + 1))
			{
				//If you hit print in screen otherwise print in red
				if (A2->getHit())
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				}
				cout << dartboard[i][j];
			}
			//Otherwise print normally
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << dartboard[i][j];
			}
		}
		//These end the lines so the board prints properly
		cout << endl;
	}
	cout << endl;
}