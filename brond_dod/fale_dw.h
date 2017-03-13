#pragma once
#include <iostream>
#include "bron_dod.h"


using namespace std;

class fala_dzw  : public bron_dodatkowa
{
    double x;
   double y;
    double szybkosc;
    int zniszczenia;
    int typ;

public:

    fala_dzw();
    ~fala_dzw();
     void ustaw_wspolrzedne(double,double);
     double daj_x();
     double daj_y();
     void ustaw_moc(int);
     void ruch(bool);
     int daj_zniszczenia();
     int destrukcja();
     int daj_typ();
     int destrukcja_od_przeszkody();
     int niszcz_przeszkode();



};
