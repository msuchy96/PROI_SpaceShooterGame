#pragma once
#include <iostream>
#include "bron_dod.h"


using namespace std;

class rakieta  : public bron_dodatkowa
{
    double x;
   double y;
    double szybkosc;
    int zniszczenia;
    int typ; /// rakieta -> 1 , fala dzw ->2;

public:

    rakieta();
    ~rakieta();
     void ustaw_wspolrzedne(double,double);
     double daj_x();
     double daj_y();
     void ustaw_moc(int);
     void ruch(bool);
     int daj_zniszczenia();
     int destrukcja();
     int daj_typ();

     int niszcz_przeszkode();



};
