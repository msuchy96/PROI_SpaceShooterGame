#include <iostream>
#include "pocisk.h"
#include "math.h"
using namespace std;

pocisk::pocisk()
{
   cout<<"Tworzy sie pocisk"<<endl;
}

pocisk::~pocisk()
{
    cout<<"Niszczy sie pocisk"<<endl;
}

double pocisk::daj_x()
{
    return x;
}

double pocisk::daj_y()
{
    return y;
}

void pocisk::ustaw_wspolrzedne(double x_dane,double y_dane,int moc)
{
    x=x_dane;
    y=y_dane;
    zniszczenia=moc;

}



void pocisk::pokaz()
{
    cout<<"wsporzedna x: "<<x<<endl;
    cout<<"wspolrzedna y: "<<y<<endl;
}

int pocisk::daj_zniszczenia()
{
    return zniszczenia;
}

void pocisk::ruch(double y_n)
{

    y=y+y_n;

}

