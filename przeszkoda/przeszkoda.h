#pragma once
#include <iostream>


using namespace std;

class przeszkoda
{
    double x;
    double y;

public:

    double daj_x();
    double daj_y();
    void losuj_wspolrzedne();
    void ruch(double,double);
    int trafienie(double,double);
    void nadaj_wspolrzedne(double,double);
    ~przeszkoda();
    przeszkoda();



};


