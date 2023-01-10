#include "Throw.h"
#include <cstdlib>
#include <string>


void Throw::setThrowType(int typeThrow)
{
	//Set type of throw
	TypeThrow = typeThrow;
}

int Throw::getThrowType()
{
	//Get type of throw
	return TypeThrow;
}

void Throw::setDart(int dart)
{
	//Set type of dart
	Dart = dart;
}

int Throw::getDart()
{
	//Get type of dart
	return Dart;
}

void Throw::setHit(bool hit)
{
	//Set hit to true or false
	Hit = hit;
}

bool Throw::getHit()
{
	//Get hit true or false value
	return Hit;
}

int Throw::throw_bull(int p) {

	//  Throw for the bull with percent accuracy (20<p<85)

	int random = rand() % 100 + 1;

	if (random <= (p - 20))
	{
		setHit(true);
	}
	else
	{
		setHit(false);
	}

	if (random <= (p - 20))
	{
		setDart(1);
		setThrowType(4);
		return 50;
	}
	else if (random <= 85)
	{
		setDart(2);
		setThrowType(4);
		return 25;
	}
	else
	{
		random = rand() % 20 + 1;
		setDart(random);
		setThrowType(1);
		return random;
	}
}

int Throw::throw_treble(int d, int p) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	int r = rand() % 100 + 1;

	if (r <= p)
	{
		setHit(true);
	}
	else
	{
		setHit(false);
	}


	if (r <= p)
	{
		setDart(d);
		setThrowType(3);
		return 3 * d;
	}
	else if (r <= 90)
	{
		setDart(d);
		setThrowType(1);
		return d;
	}
	else if (r <= 93)
	{
		setDart(bd[0][d]);
		setThrowType(3);
		return 3 * bd[0][d];
	}
	else if (r <= 96)
	{
		setDart(bd[1][d]);
		setThrowType(3);
		return 3 * bd[1][d];
	}
	else if (r <= 98)
	{
		setDart(bd[0][d]);
		setThrowType(1);
		return bd[0][d];
	}
	else
	{
		setDart(bd[1][d]);
		setThrowType(1);
		return bd[1][d];
	}
}


int Throw::throw_double(int d, int p) {

	//  return result of throwing for double d with accuracy p%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100 + 1;

	if (r <= p)
	{
		setHit(true);
	}
	else
	{
		setHit(false);
	}

	if (r <= p)
	{
		setDart(d);
		setThrowType(2);
		return 2 * d;
	}
	else if (r <= 85)
	{
		setDart(0);
		setThrowType(2);
		return 0;
	}
	else if (r <= 90)
	{
		setDart(d);
		setThrowType(1);
		return d;
	}
	else if (r <= 93)
	{
		setDart(bd[0][d]);
		setThrowType(2);
		return 2 * bd[0][d];
	}
	else if (r <= 96)
	{
		setDart(bd[1][d]);
		setThrowType(2);
		return 2 * bd[1][d];
	}
	else if (r <= 98)
	{
		setDart(bd[0][d]);
		setThrowType(1);
		return bd[0][d];
	}
	else
	{
		setDart(bd[1][d]);
		setThrowType(1);
		return bd[1][d];
	}
}



int Throw::throw_single(int d, int p) {

	//  return result of throwing for single d with accuracy p%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100 + 1;

	if (r <= p)
	{
		setHit(true);
	}
	else
	{
		setHit(false);
	}

		// we must be aiming for 1 to 20 single
	if (r <= p)
	{
		setDart(d);
		setThrowType(1);
		return d;
	}
	else if (r <= 92)
	{
		setDart(bd[0][d]);
		setThrowType(1);
		return bd[0][d];
	}
	else if (r <= 96)
	{
		setDart(bd[1][d]);
		setThrowType(1);
		return bd[1][d];
	}
	else if (r <= 98)
	{
		setDart(d);
		setThrowType(3);
		return 3 * d;
	}
	else
	{
		setDart(d);
		setThrowType(2);
		return 2 * d;
	}
}

int Throw::dartType(int type, int dart, int percent)
{
	switch (type)
	{
	case 1:
		return throw_single(dart, percent);
		break;
	case 2:
		return throw_double(dart, percent);
		break;
	case 3:
		return throw_treble(dart, percent);
		break;
	case 4:
		return throw_bull(percent);
		break;
	}
}

int Throw::throwTest(int type, int dart)
{
	/*Switch checks type of throw and set's multiplier accordingly for the dart
	Or returns 50 for BULL*/
	switch (type)
	{
	case 1:
		return dart;
		break;
	case 2:
		return (2 * dart);
		break;
	case 3:
		return (3 * dart);
		break;
	case 4:
		return (2 * 25);
		break;
	}
}