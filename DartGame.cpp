#include "DartGame.h"
#include <iostream>
#include "Automated.h"
#include "Throw.h"
#include "Interactive.h"
#include <windows.h>
#include <thread>
#include <iomanip>

using namespace std;

//Object pointers
Automated* Strategy1;
Throw* throwing;
Interactive* Strategy2;

void DartGame::Game()
{
	//Creates objects
	throwing = new Throw();
	Strategy1 = new Automated();
	Strategy2 = new Interactive();

	cout << "Loading Menu..." << endl;
	
	//Pre-calculates all dart checkout routes
	DartCheckout();

	//Clears the screen
	system("CLS");

	//While forever
	while (1)
	{
		//Set opt to 0 each time the menu is opened
		opt = 0;

		//Set console text to green for ascii title
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << R"(
 ______     __      _      ____                     __             
/\  ___\  /'__`\  /' \    /\  _`\                  /\ \__          
\ \ \__/ /\ \/\ \/\_, \   \ \ \/\ \     __     _ __\ \ ,_\   ____  
 \ \___``\ \ \ \ \/_/\ \   \ \ \ \ \  /'__`\  /\`'__\ \ \/  /',__\ 
  \/\ \L\ \ \ \_\ \ \ \ \   \ \ \_\ \/\ \L\.\_\ \ \/ \ \ \_/\__, `\
   \ \____/\ \____/  \ \_\   \ \____/\ \__/.\_\\ \_\  \ \__\/\____/
    \/___/  \/___/    \/_/    \/___/  \/__/\/_/ \/_/   \/__/\/___/                                                                   
)";
		//Resets console text to white
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		cout << "Choose an option..." << endl << "1.Automated Strategy" << endl << "2.Interactive Strategy" << endl << "3.Rules" << endl << "4.Exit" << endl;
		//While input is outside params keep looping
		while (opt < 1 || opt > 4)
		{
			cout << ">";
			cin >> opt;
		}

		//Clears screen
		system("CLS");

		//Selects option using switch
		switch (opt)
		{
		case 1:
			//Opens strategy 1 and passes in the two score arrays for safe and risky throws
			Strategy1->Auto(ScoreArrRisk, ScoreArrSafe);
			break;
		case 2:
			//Opens strategy 2 and passes in the two score arrays for safe and risky throws
			Strategy2->Interact(ScoreArrRisk, ScoreArrSafe);
			break;
		case 3:
			//Opens the rule page
			Rules();
			break;
		case 4:
			//Exits the program
			std::exit(0);
		}
	}
}
void DartGame::Rules()
{
	//Prints rule page
	cout << R"(
|Play|

The order of play is either determined by a toss of a coin (50:50).
A throw consists three darts except where the game is finished in less.
If the number required for the game is exceeded in the course 
of a throw, throw ceases, and no account is taken of the score obtained during that throw.
The inner bull (50) counts as double of (25) the outer bull.
The game is to score 501.

|Scoring|

Each player's score must start and finish a game with a double (The outer narrow ring of the board). 
The first throw is deducted from the player's start number e.g. 501 and then from the subsequent reduced total. The scorer should 
show both the score obtain for the throw and the reducing total remaining.    
                                                               
)";
	cout << "Press enter to return to the main menu" << endl;

	//Clears cin buffer and asks the users to enter anything
	cin.ignore();
	cin.get();
	system("CLS");
}

void DartGame::DartCheckout()
{
	//Iteration for both risk array and safe array
	for (ArrNum = 0; ArrNum < 2; ArrNum++)
	{
		//Iteration for each score
		for (int iteration = 1; iteration < 171; iteration++)
		{
			//If the array is risky start at 0
			if (ArrNum == 0)
			{
				count2 = 0;
			}
			//If array is safe start at 4
			else if (ArrNum == 1)
			{
				count2 = 4;
			}

			//Loops 3 times
			for (int x = 0; x < 3; x++)
			{
				//If the array is risky increments by 1 
				if (ArrNum == 0)
				{
					count2++;
				}
				//If the array is safe decrement by 1
				else if (ArrNum == 1)
				{
					count2--;
				}

				//Iteration type of throw for throw 1
				for (int throwtype1 = 1; throwtype1 < 5; throwtype1++)
				{
					//Iteration type of throw for throw 2
					for (int throwtype2 = 1; throwtype2 < 5; throwtype2++)
					{
						//Iteration type of throw for throw 3
						for (int throwtype3 = 1; throwtype3 < 5; throwtype3++)
						{
							//Iteration dart for throw 1
							for (int d1 = 1; d1 < 21; d1++)
							{
								//Iteration dart for throw 2
								for (int d2 = 1; d2 < 21; d2++)
								{
									//Iteration dart for throw 3
									for (int d3 = 1; d3 < 21; d3++)
									{
										//Switch uses number of count 2 which is the number of throws being tested for
										switch (count2)
										{
										//Case 1 for 3 throws
										case 1:
											//Checks iteration is below 171 or that the previous throw didn't have a double or bull to finish
											if ((iteration < 171) || (throwtype3 != 2 && throwtype3 != 4))
											{
												/*Makes value equal to the eqaution of all throws if the equation is is equal to the iteration then set the array to these types
												and reset the iteration values for the loops */
												value = throwing->throwTest(throwtype1, d1) + throwing->throwTest(throwtype2, d2) + throwing->throwTest(throwtype3, d3);
												if (iteration == value && (throwtype3 == 2 || throwtype3 == 4))
												{
													ScoreArr[iteration][0][0] = d1;
													ScoreArr[iteration][0][1] = d2;
													ScoreArr[iteration][0][2] = d3;
													ScoreArr[iteration][1][0] = throwtype1;
													ScoreArr[iteration][1][1] = throwtype2;
													ScoreArr[iteration][1][2] = throwtype3;

													throwtype1 = 5;
													throwtype2 = 5;
													throwtype3 = 5;

													d1 = 21;
													d2 = 21;
													d3 = 21;
												}
											}
											break;
										//Case 2 for 2 throws
										case 2:
											//Checks iteration is below 111 or that the previous throw didn't have a double or bull to finish
											if ((iteration < 111) || (throwtype2 != 2 && throwtype2 != 4))
											{
												/*Makes value equal to the eqaution of all throws if the equation is is equal to the iteration then set the array to these types
												and reset the iteration values for the loops */
												value = throwing->throwTest(throwtype1, d1) + throwing->throwTest(throwtype2, d2);
												if (iteration == value && (throwtype2 == 2 || throwtype2 == 4))
												{
													ScoreArr[iteration][0][0] = d1;
													ScoreArr[iteration][0][1] = d2;
													ScoreArr[iteration][0][2] = 0;
													ScoreArr[iteration][1][0] = throwtype1;
													ScoreArr[iteration][1][1] = throwtype2;
													ScoreArr[iteration][1][2] = 0;

													throwtype1 = 5;
													throwtype2 = 5;
													throwtype3 = 5;

													d1 = 21;
													d2 = 21;
													d3 = 21;

												}
											}
											break;
										//Case 3 for 3 throws
										case 3:
											//Checks iteration is below 51 or that the previous throw didn't have a double or bull to finish
											if ((iteration < 51) || (throwtype1 != 2 && throwtype1 != 4))
											{
												/*Makes value equal to the eqaution of all throws if the equation is is equal to the iteration then set the array to these types
												and reset the iteration values for the loops */
												value = throwing->throwTest(throwtype1, d1);
												if (iteration == value && (throwtype1 == 2 || throwtype1 == 4))
												{
													ScoreArr[iteration][0][0] = d1;
													ScoreArr[iteration][0][1] = 0;
													ScoreArr[iteration][0][2] = 0;
													ScoreArr[iteration][1][0] = throwtype1;
													ScoreArr[iteration][1][1] = 0;
													ScoreArr[iteration][1][2] = 0;

													throwtype1 = 5;
													throwtype2 = 5;
													throwtype3 = 5;

													d1 = 21;
													d2 = 21;
													d3 = 21;
												}
											}
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//If Arrnum is for risk array copy over risk array
		if (ArrNum == 0)
		{
			memcpy(ScoreArrRisk, ScoreArr, 171 * 2 * 3 * sizeof(int));
		}
		//Otherwise if Arrnum is for safe array copy over safe array
		else if (ArrNum == 1)
		{
			memcpy(ScoreArrSafe, ScoreArr, 171 * 2 * 3 * sizeof(int));
		}
	}
}


