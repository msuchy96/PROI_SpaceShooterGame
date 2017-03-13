#include <iostream>
#include "fale_dw.h"
#include "math.h"


fala_dzw::fala_dzw()
{
   std::cout<<"Tworzy sie fala"<<std::endl;
}

 fala_dzw::~fala_dzw()
{
    std::cout<<"Niszczy sie fala"<<std::endl;
}
void fala_dzw::ustaw_wspolrzedne(double x_dane,double y_dane)
{
    x=x_dane;
    y=y_dane;
    szybkosc=-3.0;
    typ=2;

}

double fala_dzw::daj_y()
{

    return y;
}

double fala_dzw::daj_x()
{

    return x;
}

int fala_dzw::destrukcja()
{
    return 0;
}



int fala_dzw::daj_typ()
{

    return typ;

}
int fala_dzw::niszcz_przeszkode()
{
    return 0;
}

void fala_dzw::ustaw_moc(int nowa_moc)
{
  zniszczenia=4*nowa_moc;
}

void fala_dzw::ruch(bool kierunek)
{
       if(kierunek) x=x+szybkosc;
       else x=x-szybkosc;

    y=y+szybkosc;

}

int fala_dzw::daj_zniszczenia()
{
    return zniszczenia;
}
