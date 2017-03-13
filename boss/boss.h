#pragma once
#include "pocisk.h"
#include "ogien.h"
#include <iostream>

class boss
{
    double x;
    double y;
    int hp;
    int moc;
    int tryb;
    double szybkosc=0.1;
    bool flaga_kier_tryb2;
    bool flaga_kier_tryb4;


    public:

    double daj_x();
    double daj_y();
    int daj_moc();
    int daj_hp();
    void obrazenia(int);
    int daj_tryb();
    pocisk* strzal1(double);
    ogien*  strzal2();
    int trafiony(double,double,int);
    void tryb1();
    void tryb2();
    void tryb3();
    void tryb4();
    void tryb5();
    void zmiana_trybu(int);
    boss(int=1000,int=10,double=368.0,double=-100.0,int=1);
    ~boss();




};
