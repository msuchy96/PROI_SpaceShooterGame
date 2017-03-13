#pragma once
#include <iostream>


class ogien
{
    double x;
   double y;
    double szybkosc;
    int zniszczenia;


public:

    ogien();
    ~ogien();
     void ustaw_wspolrzedne(double,double);
     double daj_x();
     double daj_y();
     void ustaw_moc(int);
     void ruch(bool);
     int daj_zniszczenia();






};
