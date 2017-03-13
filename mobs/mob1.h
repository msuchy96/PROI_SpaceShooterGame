#pragma once
#include <iostream>
#include "pocisk.h"
#include "mob_type2.h"


class mob1: public mob_typ
{

    int hp;
    int moc_m;
    double x;
    double y;
    int typ;




public:

    double daj_x();
    double daj_y();
    int daj_hp();
    int daj_moc();
    int daj_typ();
    void trafiony(int);
    void ruch(double);
    int trafienie(double,double,int);
    pocisk* strzal();
    mob1(int=100,int=20,double=936,double=5);
    ~mob1();
    void nadaj_id_typ(int);

};
