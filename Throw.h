#pragma once
class Throw
{
public:
    //Declaring public functions
    void setHit(bool hit);
    bool getHit();
    void setThrowType(int typethrow);
    int getThrowType();
    void setDart(int dart);
    int getDart();

    int throw_single(int d, int p);
    int throw_double(int d, int p);
    int throw_treble(int d, int p);
    int throw_bull(int p);

    int dartType(int type, int dart, int percent);
    int throwTest(int type, int dart);

private:
    //Declaring private variables
    bool Hit;
    int TypeThrow = 1;
    int Dart = 0;
};
