#include <iostream>
#include "rakiety.h"
#include "math.h"


rakieta::rakieta()
{
   std::cout<<"Tworzy sie rakieta"<<std::endl;
}

 rakieta::~rakieta()
{
    std::cout<<"Niszczy sie rakieta"<<std::endl;
}
void rakieta::ustaw_wspolrzedne(double x_dane,double y_dane)
{
    x=x_dane;
    y=y_dane;
    szybkosc=-1;
    typ=1;

}

double rakieta::daj_y()
{

    return y;
}
int rakieta::daj_typ()
{

    return typ;

}
double rakieta::daj_x()
{

    return x;
}

int rakieta::destrukcja()
{
    return 1;
}
int rakieta::niszcz_przeszkode()
{
    return 1;
}

void rakieta::ustaw_moc(int nowa_moc)
{
  zniszczenia=2*nowa_moc;
}

void rakieta::ruch(bool kierunek)
{
    y=y+szybkosc;

}

int rakieta::daj_zniszczenia()
{
    return zniszczenia;
}
