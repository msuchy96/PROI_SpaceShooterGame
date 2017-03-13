#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mob1.h"
#include "math.h"

mob1::mob1( int k_hp, int k_moc,double k_x, double k_y)
{
    hp=k_hp;
    moc_m=k_moc;
    x=k_x;
    y=k_y;
    std::cout<<"Tworzy sie Mob"<<std::endl;

}

mob1::~mob1()
{
    std::cout<<"Niszczy sie Mob"<<std::endl;
}

int mob1::daj_moc()
{
    return moc_m;
}

int mob1::daj_typ()
{
    return typ;
}

void mob1::ruch(double x_n)
{
    x=x+x_n;

}

int mob1::trafienie(double x_pocisku,double y_pocisku,int obrazenia)
{


    if(x<=x_pocisku && x+50>=x_pocisku  && y-50<=y_pocisku && y+50>=y_pocisku)
    {
        std::cout<<"Trafiony mob_typ2!"<<std::endl;
        trafiony(obrazenia);
        return 1;
    }

    return 0;

}


void mob1::nadaj_id_typ(int typ_mob)
{

    typ=typ_mob;

}

int mob1::daj_hp()
{
    return hp;
}
double mob1::daj_x()
{
    return x;
}

double mob1::daj_y()
{
    return y;
}

void mob1::trafiony(int obrazenia)
{
    hp=hp-obrazenia;
}

pocisk* mob1::strzal()
{
    pocisk* nowy_pocisk=new pocisk;
    nowy_pocisk->ustaw_wspolrzedne(x+16,y+25,moc_m);

    return nowy_pocisk;
}
