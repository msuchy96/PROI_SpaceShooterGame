#pragma once
#include <iostream>


class bron_dodatkowa
{


    public:

    virtual void ustaw_wspolrzedne(double,double)=0;;
    virtual double daj_x()=0;
    virtual double daj_y()=0;
    virtual void ustaw_moc(int)=0;
    virtual void ruch(bool)=0;
    virtual int daj_zniszczenia()=0;
    virtual int destrukcja()=0;
    virtual int daj_typ()=0;
    virtual int niszcz_przeszkode()=0;
    virtual ~bron_dodatkowa()
    {  }

};
