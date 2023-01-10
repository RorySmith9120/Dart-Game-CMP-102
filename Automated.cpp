#include "Automated.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Throw.h"
#include "Player.h"
#include "Windows.h"

//Namespace
using namespace std;

//Object pointers

Player* A;
Player* B;

//Initialses constant for number of games
int const repeat = 1000;

void Automated::Auto(int RiskArr[][2][3], int SafeArr[][2][3])
{
	//Creates array to store results
	int results[repeat][2];
	
	//Creates objects for both players (Name,Percentage)
	A = new Player("Joe", 75);//75 Better strategy makes up for 25% Difference in accuracy

	B = new Player("Sid", 100);//100

	cout << "Loading Results..." << endl;

	//Sets changes arr for both player objects to the array passed into this function
	A->setArr(RiskArr);
	B->setArr(RiskArr);
	A->setArrSafe(SafeArr);
	B->setArrSafe(SafeArr);


	//50:50 coin toss for first throw
	int r = rand() % 2 + 1;

	throwFirst = r;

	//Loop noOfGames times
	for (game = 0; game < repeat; game++)
	{
		//Plays 13 games
		for (int i = 0; i < 13; i++)
		{
			//Resets wins for new best of three
			A->setWins(0);
			B->setWins(0);

			//While neither wins have made it to 3 repeat
			while (B->getWins() != 3 && A->getWins() != 3)
			{

				//Resets scores for both players to 301
				A->setScore(501);
				B->setScore(501);

				//While the scores of both players are more than one, meaning one of them hasn't won then continue to loop the code below
				LOOP:while (A->getScore() > 0 && B->getScore() > 0)
				{
					switch (throwFirst)
					{
					case 1:

						//If the score of player one is more than 0 execute the code below
						if (A->getScore() > 0)
						{
							//Set the starting score before any throws to ScoreRead
							A->setScoreRead(A->getScore());

							//If player A score is ahead by 180 points then play safe
							if (B->getScore() > (A->getScore() + 180))
							{
								A->setSafe(true);
							}
							else
							{
								A->setSafe(false);
							}

							//Loop 3 times
							for (count = 0; count < 3; count++)
							{
								//Checks if the player needs to double in
								if (A->getScore() == 501)
								{
									A->setFirstHit(true);
								}
								else
								{
									A->setFirstHit(false);
								}

								//If you are 80% or more accuracte double in on a bullseye otherwise double in on a 20
								if (A->getFirstHit() == true)
								{
									if (A->getPercentage() >= 80)
									throwScore[count] = A->throw_bull(A->getPercentage());
									else
									{
									throwScore[count] = A->throw_double(20, A->getPercentage());
									}
								}

								//If the orginal score is below or equal to 170 grab the precalculated throws and use them
								else if (A->getScoreRead() <= 170)
								{
									switch (count)
									{
									case 0:
										//Throwscore[0] = Function for throw 0 scores path
										throwScore[0] = A->DartRoute(0);
										break;
									case 1:
										//Throwscore[1] = Function for throw 1 scores path
										if (A->getHit())
										{
											throwScore[1] = A->DartRoute(1);
										}
										//If you missed the first throw recalculates for new score
										else if (!A->getHit())
										{
											A->setScoreMiss(A->getScore());
											throwScore[1] = A->miss1(1);
											missed1 = true;
										}
										break;
									case 2:
										//Throwscore[2] = Function for throw 2 scores path

										//If you also miss throw 2 recalculate score again
										if (!A->getHit())
										{
											A->setScoreMiss(A->getScore());
											throwScore[2] = A->miss1and2(2);
										}
										//Calcualted score for missing throw 1
										else if (missed1 == true)
										{
											throwScore[2] = A->miss1(2);
										}
										//Otherwise normal calculation
										else if (A->getHit())
										{
											throwScore[2] = A->DartRoute(2);
										}
										break;
									}
								}
								//If the initial score is more than 171 throw for the maximum score otherwise if its equal to 171 throw a triple 19
								else if (A->getScoreRead() > 171)
								{
									throwScore[count] = A->dartType(3, 20, A->getPercentage());
								}
								else if (A->getScoreRead() == 171)
								{
									throwScore[count] = A->dartType(3, 19, A->getPercentage());
								}

								//Remove throwscore from current score

								A->setScore(A->getScore() - throwScore[count]);

								//If the score has reached 0 and the type of throw is a double or bull then goto LOOP (Look Upwards^^)
								if (A->getScore() == 0 && (A->getThrowType()==2 || A->getThrowType() == 4))
								{									
									B->setNumOfThrows(B->getNumOfThrows() + 3);
									goto LOOP;
								}
								//If the score is less than 1 or it's the first/last hit and you missed reset the score to the initial score
								else if (A->getScore() <= 1 || ((A->getFirstHit() || A->getScore() == 0) && !A->getHit()))
								{
									A->setScore(A->getScoreRead());
								}

								//Increase number of throws
								A->setNumOfThrows(A->getNumOfThrows() + 1);

							}
							//Sets missed1 to false for the next 3 throws
							missed1 = false;
						}

					case 2:
						//If the score of player one is more than 0 execute the code below
						if (B->getScore() > 0)
						{
							//Set the starting score before any throws to ScoreRead
							B->setScoreRead(B->getScore());

							//Loop 3 times
							for (count = 0; count < 3; count++)
							{

								//Checks if the player needs to double in
								if (B->getScore() == 501 || B->getScore() == 50)
								{
									B->setFirstHit(true);
								}
								else
								{
									B->setFirstHit(false);
								}

								//If it is the first hit throw for a bull
								if (B->getFirstHit() == true)
								{
									throwScore[count] = B->throw_bull(B->getPercentage());
								}
								//Ottherwise if the score is less than 41 check if the score can be divided by 2 if so then throw the double
								else if (B->getScore() < 41)
								{
									throwScore[count] = B->dartType(2, (B->getScore() / 2), B->getPercentage());

									//If it couldn't be divided then check the score and try make the maximum score without going below 2
									if (throwScore[count] != B->getScore())
									{
										if (B->getScore() < 21)
										{
											throwScore[count] = B->dartType(1, (B->getScore() - 2), B->getPercentage());
										}
										else if (B->getScore() > 21)
										{
											throwScore[count] = B->dartType(1, 20, B->getPercentage());
										}
										else if (B->getScore() == 21)
										{
											throwScore[count] = B->dartType(1, 19, B->getPercentage());
										}
									}
								}
								//Try make the maximum score without going below 2
								else if (B->getScore() >= 60)
								{
									throwScore[count] = B->dartType(3, 20, B->getPercentage());
								}
								else if (B->getScore() > 41)
								{
									throwScore[count] = B->dartType(2, 20, B->getPercentage());
								}
								else if (B->getScore() == 41)
								{
									throwScore[count] = B->dartType(2, 19, B->getPercentage());
								}

								//Remove throwscore from current score

								B->setScore(B->getScore() - throwScore[count]);

								//If the score has reached 0 and the type of throw is a double or bull then goto LOOP (Look Upwards^^)
								if (B->getScore() == 0 && (B->getThrowType() == 2 || B->getThrowType() == 4))
								{
									A->setNumOfThrows(A->getNumOfThrows() + 3);
									goto LOOP;
								}
								//If the score is less than 1 or it's the first/last hit and you missed reset the score to the initial score
								else if (B->getScore() <= 1 || ((B->getFirstHit() || B->getScore() == 0) && !B->getHit()))
								{
									B->setScore(B->getScoreRead());
								}

								//Increase number of throws
								B->setNumOfThrows(B->getNumOfThrows() + 1);
							}
							//Reset the 3 throws scores for this round to 0
							throwScore[0] = 0;
							throwScore[1] = 0;
							throwScore[2] = 0;
						}
					}
					//Set the first throw back to 1 if the second player got the first throw
					throwFirst = 1;

					//End of round
				}

				//End of game

				//Checks players number of throws and gives the player with the least a win 
				if (A->getNumOfThrows() < B->getNumOfThrows())
				{
					A->setWins(A->getWins() + 1);
				}
				else if (B->getNumOfThrows() < A->getNumOfThrows())
				{
					B->setWins(B->getWins() + 1);
				}
				else if (A->getNumOfThrows() == B->getNumOfThrows())
				{

				}

				//Reset number of throws to 0
				A->setNumOfThrows(0);
				B->setNumOfThrows(0);

				//If the player reaches 3 wins first give them a best of 3 win
				if (A->getWins() == 3)
				{
					A->setBOTWins(A->getBOTWins() + 1);
				}
				else if (B->getWins() == 3)
				{
					B->setBOTWins(B->getBOTWins() + 1);
				}
			}

		}

		//Puts the game results into an array
		results[game][0] = A->getBOTWins();
		results[game][1] = B->getBOTWins();

		//Collects the total of best of three wins
		A->setTotal(A->getTotal() + A->getBOTWins());
		B->setTotal(B->getTotal() + B->getBOTWins());

		//Sets best of three wins to 0
		A->setBOTWins(0);
		B->setBOTWins(0);

	}

	//Clears screen
	system("CLS");

	//Set console text colour to green for title
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << R"(
 ______           __                                 __              __     
/\  _  \         /\ \__                             /\ \__          /\ \    
\ \ \L\ \  __  __\ \ ,_\   ___     ___ ___      __  \ \ ,_\    __   \_\ \   
 \ \  __ \/\ \/\ \\ \ \/  / __`\ /' __` __`\  /'__`\ \ \ \/  /'__`\ /'_` \  
  \ \ \/\ \ \ \_\ \\ \ \_/\ \L\ \/\ \/\ \/\ \/\ \L\.\_\ \ \_/\  __//\ \L\ \ 
   \ \_\ \_\ \____/ \ \__\ \____/\ \_\ \_\ \_\ \__/.\_\\ \__\ \____\ \___,_\
    \/_/\/_/\/___/   \/__/\/___/  \/_/\/_/\/_/\/__/\/_/ \/__/\/____/\/__,_ /                                                                
)";

	//Sets console text colour back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << A->getName() << "|Accuracy:" << A->getPercentage() << " " << B->getName() << "|Accuracy:" << B->getPercentage() << endl;
	cout << A->getName() << ":" << B->getName() << " | Frequency" << endl;

	//Prints results of the game
	countFreq(results);

	//If the total divided by repeat(calculating average) has both scores equal to 6 the find the one with larger score and give them the extra win
	int add1 = 0;
	int add2 = 0;

	if ((A->getTotal() / repeat) == 6 && (B->getTotal() / repeat) == 6)
	{
		if (A->getTotal() > B->getTotal())
		{
			add1 = 1;
		}
		else
		{
			add2 = 1;
		}
	}

	cout << endl << "AVG = " << (A->getTotal()/repeat) + add1 << ":" << (B->getTotal()/repeat) + add2 << endl;

	//Print the person with the the average result

	cout << endl << "Results Loaded Successfully!" << endl;
	
	cout << "Press enter to return to the main menu" << endl;

	//Clear cin buffer and get the user to enter any character
	cin.ignore();
	cin.get();

	//Clear the screen
	system("CLS");
}

void Automated::countFreq(int results[][2])
{
	//Initialise variables
	int PlayerResult[repeat][2];
	bool visited[repeat][2] = { false };

	float Frequency;

	//Copies array passed into function to PlayerResult
	memcpy(PlayerResult, results, repeat * 2 * sizeof(int));

	// Iteration for array elements
	// count frequency
	for (int i = 0; i < repeat; i++) {

		// Skip this element if has already been processed
		if (visited[i][0] == false && visited[i][1] == false)
		{

			// Count frequency
			float count = 1;
			for (int j = i + 1; j < repeat; j++)
			{
				if (PlayerResult[i][0] == PlayerResult[j][0] && PlayerResult[i][1] == PlayerResult[j][1]) {

					visited[j][0] = true;
					visited[j][1] = true;
					count++;
				}
			}
			//Calculates percentage of the frequency out of 100
			Frequency = (count / repeat) * 100.00;
			cout << " " << PlayerResult[i][0];
			//Some text formatting and printing of the results
			if (PlayerResult[i][0] > 9)
			{
				cout << ": ";
			}
			else
			{
				cout << " : ";
			}

			cout << PlayerResult[i][1];
			if (PlayerResult[i][1] < 10)
			{
				cout << " ";
			}
			cout << setw(8) << setprecision(4) << Frequency << "%" << endl;
		}
	}
}