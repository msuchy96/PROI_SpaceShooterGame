#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mob2.h"
#include "math.h"

mob2::mob2(int k_hp, int k_moc,double k_x, double k_y)
{

    hp=k_hp;
    moc_m=k_moc;
    x=k_x;
    y=k_y;
    std::cout<<"Tworzy sie Mob"<<std::endl;

}

mob2::~mob2()
{
std::cout<<"Niszczy sie Mob"<<std::endl;
}
int mob2::daj_moc()
{
    return moc_m;
}
int mob2::daj_typ()
{
    return typ;
}

void mob2::ruch(double x_n)
{

    x=x+x_n;
    y=50*sin(x/100)+300;


}

void mob2::nadaj_id_typ(int typ_mob)
{

   typ=typ_mob;

}

int mob2::trafienie(double x_pocisku,double y_pocisku,int obrazenia)
{
    if(x<=x_pocisku && x+50>=x_pocisku  && y-50<=y_pocisku && y+50>=y_pocisku)
{
     std::cout<<"Trafiony mob_typ2!"<<std::endl;
     trafiony(obrazenia);


    return 1;
}

    return 0;




}






int mob2::daj_hp()
{
    return hp;
}
double mob2::daj_x()
{
    return x;
}

double mob2::daj_y()
{
    return y;
}

void mob2::trafiony(int obrazenia)
{
    hp=hp-obrazenia;
}

pocisk* mob2::strzal()
{
    pocisk* nowy_pocisk=new pocisk;
    nowy_pocisk->ustaw_wspolrzedne(x+16,y+25,moc_m);

    return nowy_pocisk;
}
