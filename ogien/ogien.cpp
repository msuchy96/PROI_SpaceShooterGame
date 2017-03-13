#include <iostream>
#include "ogien.h"
#include "math.h"

ogien::ogien()
{
   std::cout<<"Tworzy sie ogien"<<std::endl;
}

 ogien::~ogien()
{
    std::cout<<"Niszczy sie ogien"<<std::endl;
}

void ogien::ustaw_wspolrzedne(double x_dane,double y_dane)
{
    x=x_dane;
    y=y_dane;
    szybkosc=1.0;


}

double ogien::daj_y()
{

    return y;
}

double ogien::daj_x()
{

    return x;
}

void ogien::ustaw_moc(int nowa_moc)
{
  zniszczenia=6*nowa_moc;
}

void ogien::ruch(bool kierunek)
{
    if(kierunek) x=x-szybkosc;
    else x=x+szybkosc;

}

int ogien::daj_zniszczenia()
{
    return zniszczenia;
}
