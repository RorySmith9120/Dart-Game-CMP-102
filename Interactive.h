#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#pragma once
class Interactive
{
	//Declare public functions
public:
	void Interact(int RiskArr[][2][3], int SafeArr[][2][3]);
	void PrintThrow(int a, int b);
	void PrintDartBoard(int dart, int throwtype);

	//Declare private variables
private:
	//Y, X coordinates for board locations
	int SingleLocations[21][2] =
	{
		{25, 36},//missed board
		{6, 39},//1
		{20, 44},//2
		{22, 33},//3
		{8, 50},//4
		{6, 27},//5
		{13, 55},//6
		{20, 22},//7
		{16, 14},//8
		{8, 16},//9
		{16, 53},//10
		{13, 11},//11
		{7, 21},//12
		{11, 51},//13
		{11, 12},//14
		{18, 49},//15
		{18, 17},//16
		{22, 39},//17
		{7, 45},//18
		{22, 27},//19
		{5, 33} //20
	};
	int DoubleLocations[21][2] =
	{
		{25, 36},//missed board
		{3, 39},//1
		{22, 49},//2
		{24, 33},//3
		{7, 55},//4
		{3, 27},//5
		{13, 60},//6
		{22, 16},//7
		{17, 8},//8
		{6, 13},//9
		{17, 59},//10
		{13, 6},//11
		{4, 19},//12
		{10, 58},//13
		{10, 8},//14
		{20, 53},//15
		{20, 13},//16
		{24, 40},//17
		{5, 48},//18
		{24, 26},//19
		{3, 33} //20
	};
	int TrebleLocations[21][2] =
	{
		{25, 36},//missed board
		{8, 38},//1
		{19, 42},//2
		{20, 33},//3
		{10, 46},//4
		{8, 28},//5
		{14, 49},//6
		{19, 24},//7
		{16, 18},//8
		{10, 20},//9
		{16, 49},//10
		{14, 18},//11
		{9, 24},//12
		{12, 47},//13
		{12, 18},//14
		{17, 46},//15
		{17, 20},//16
		{20, 38},//17
		{9, 42},//18
		{20, 29},//19
		{8, 33} //20
	};
	int BullLocation[3][2] = //dart = 1 for bull dart = 2 for outer bull
	{
		{25, 36},//missed board
		{14, 33},//Bull
		{13, 33} //Outer Bull
	};
	int add = 1;
	int TargetLocations[21][2];
	int Accuracy = 0;
	int throwScore[3] = { 0,0,0 };
	int throwFirst = 0;
	int count = 0;
	int game = 0;
	int multiplier = 0;
	int dart = 0;
	int NumGames = 0;
	int ThrowNum = 0;
	char dartboard[29][69] =
		//     0		   1		 2		   3		 4		   5		 6
	{ //  123456789 123456789 123456789 123456789 123456789 123456789 1234567
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",//0
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@",//1
		"@@@@@@@@@@@@@@@@@@@              20              @@@@@@@@@@@@@@@@@@@",//2
		"@@@@@@@@@@@@@@@        5                   1         @@@@@@@@@@@@@@@",//3
		"@@@@@@@@@@@@    12      *#*****#&&&&#*****#*            @@@@@@@@@@@@",//4
		"@@@@@@@@@          ,,,#@@@@@@@%. .. .%@@@@@@@#,,,   18     @@@@@@@@@",//5
		"@@@@@@@         ,,,, . .@@@@@@@. .. .@@@@@@@. . ,,,,         @@@@@@@",//6
		"@@@@@@   9   *&**@.  .. .@@@@@@..  ..@@@@@@. .. . @**&*    4  @@@@@@",//7
		"@@@@       &**@@@@@@ ..  .%*****,,,,*****%.  .. @@@@@@**&       @@@@",//8
		"@@@       **&@@@@@@@@@ ,,&  @@@@ .. @@@@  &,, @@@@@@@@@&**       @@@",//9
		"@@   14  ,, . *@@@@@&**@ . . @@@@..@@@@ . . @**&@@@@@  . ,,   13  @@",//10
		"@       ,,. .. .   )*%@@@@@. .@@@..@@@. .@@@@@%*(  .. ..  ,,       @",//11
		"@      ,# . .. . .,&  . %@@@@  %@  @%  @@@@# . &,. .. .. *,&       @",//12
		"@      **@@@@@@@@@*%( . . .  &&******&&  . . . )%*@@@@@@@@@**      @",//13
		"@  11  **@@@@@@@@#*&@@@@@@@@@@***##***@@@@@@@@@@%*&@@@@@@@@**  6   @",//14
		"@      **@@@@@@@& ,,  . . . %@@******@@% . . .  ,, &@@@@@@@**      @",//15
		"@      #,, .  .. .*,&  %@@@@@  @@..@@  @@@@@%  &,*&  .. . ,,#      @",//16
		"@@      ,,( . .. .@@**@@@@ . .@@@..@@@. . @@@@**@@@. .. . ),,     @@",//17
		"@@  8    ,,  ,@@@@@@@**(  . .@@@ .. @@@. .  )**@@@@@@@@,  ,,  10  @@",//18
		"@@@       %**@@@@@@@@  &,, %@@@@ .. @@@@% ,,&  @@@@@@@@**%       @@@",//19
		"@@@@,        **&@@@@. .. .'@%**%,,,,%***@'. .. .@@@@&**         @@@@",//20
		"@@@@@@  16    ##(. .. .. @@@@@@..  ..@@@@@@ .. .. .)##   15   @@@@@@",//21
		"@@@@@@@@       (,,(. .  @@@@@@@. .. .@@@@@@@  . .),,)       @@@@@@@@",//22
		"@@@@@@@@@@        .,,(*@@@@@@@@. .. .@@@@@@@@,,,   2      @@@@@@@@@@",//23
		"@@@@@@@@@@@@    7       ******,,,,,,,,******            @@@@@@@@@@@@",//24
		"@@@@@@@@@@@@@@@@       19                  17       @@@@@@@@@@@@@@@@",//25
		"@@@@@@@@@@@@@@@@@@@@/            3             /@@@@@@@@@@@@@@@@@@@@",//26
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@",//27
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" //28
	};
};



