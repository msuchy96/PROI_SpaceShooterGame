#include <iostream>
#include <cstdlib>
#include <ctime>
#include "przeszkoda.h"


przeszkoda::przeszkoda()
{
    std::cout<<"Tworzy sie przeszkoda"<<std::endl;
}

przeszkoda::~przeszkoda()
{
    std::cout<<"Niszczy sie przeszkoda"<<std::endl;

}

int przeszkoda::trafienie(double x_pocisku,double y_pocisku)
{
    if(x-10<=x_pocisku && x+40>=x_pocisku  && y<=y_pocisku && y+30>=y_pocisku) return 1;

    return 0;
}

double przeszkoda::daj_x()
{
    return x;
}

double przeszkoda::daj_y()
{
    return y;
}
void przeszkoda::nadaj_wspolrzedne(double x_nowy,double y_nowy)
{
    x=x_nowy;
    y=y_nowy;


}
void przeszkoda::ruch(double x_n, double y_n)
{
  x=x+x_n;
  y=y+y_n;

}

 void przeszkoda::losuj_wspolrzedne()
 {
   x=(rand()%970)-10;
    y=-50;

 }

