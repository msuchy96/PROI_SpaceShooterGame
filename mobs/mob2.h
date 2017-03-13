#pragma once
#include <iostream>
#include "pocisk.h"
#include "mob_type2.h"


class mob2: public mob_typ
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
    int trafienie(double,double,int);
    void ruch(double);
    pocisk* strzal();
    mob2(int=100,int=10,double=936,double=5);
    ~mob2();
    void nadaj_id_typ(int);

};
