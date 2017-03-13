#pragma once
#include <iostream>

class pocisk
{
    double x;
    double y;
    int zniszczenia;
    bool w_lewo;
    bool w_prawo;


public:
    pocisk();
    ~pocisk();
    double daj_x();
    double daj_y();

    int daj_zniszczenia();
    void ustaw_wspolrzedne(double,double,int);
    void pokaz();
    void ruch(double);
    pocisk* nastepny;
    pocisk* poprzedni;

};




