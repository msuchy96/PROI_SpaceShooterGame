#include <iostream>
#include "gracz.h"
#include "okno_gry.h"
#include "pocisk.h"
#include "fale_dw.h"
#include "bron_dod.h"
#include "rakiety.h"



gracz::gracz(int hp_gracza,int moc_gracza,double x_gracza,double y_gracza,double wspol_ruch,int ile_fal,int ile_rakiet)
{
  hp=hp_gracza;
  moc=moc_gracza;
  x=x_gracza;
  y=y_gracza;
  liczba_fal=ile_fal;
  liczba_rakiet=ile_rakiet;
  wspolczynnik_ruchu=wspol_ruch;

    std::cout<<"Tworzy sie gracz"<<std::endl;
}


gracz::~gracz()
{

    std::cout<<"Niszczy sie gracz"<<std::endl;

}

double gracz::daj_x()
{
    return x;
}

int gracz::daj_liczbe_rakiet()
{
    return liczba_rakiet;
}

int gracz::daj_liczbe_fal()
{
    return liczba_fal;
}

pocisk* gracz::strzal()
{
    pocisk* nowy_pocisk=new pocisk;
    nowy_pocisk->ustaw_wspolrzedne(x+16,y-25,moc);

    return nowy_pocisk;
}

rakieta* gracz::strzal_2()
{
    rakieta* nowa_rakieta= new rakieta;
    nowa_rakieta->ustaw_moc(moc);
    liczba_rakiet--;
    return nowa_rakieta;
}

void gracz::dodaj_rakiety()
{
    liczba_rakiet=liczba_rakiet+2;

}

void gracz::dodaj_fale()
{
    liczba_fal=liczba_fal+2;
}

fala_dzw* gracz::strzal_3()
{
   fala_dzw* nowa_fala= new fala_dzw;
   nowa_fala->ustaw_moc(moc);
   liczba_fal--;
   return nowa_fala;

}

double gracz::daj_y()
{
    return y;
}
int gracz::daj_moc()
{
    return moc;
}

int gracz::daj_hp()
{
    return hp;
}
double gracz::daj_wspol_ruchu()
{
    return wspolczynnik_ruchu;
}

void gracz::trafiony(int obrazenia)
{
    hp=hp-obrazenia;
}

int gracz::trafienie(double x_pocisku,double y_pocisku,int zniszczenia)
{
    if((x-20<=x_pocisku && x+50>=x_pocisku)  && (y-50<=y_pocisku && y+50>=y_pocisku))
    {
        std::cout<<"Trafiony gracz!"<<std::endl;
        trafiony(zniszczenia);
        return 1;

    }
    return 0;
}

void gracz::ruch(double x_n, double y_n)
{
  if(x+x_n<=929 && x+x_n>=0) x=x+x_n;
  if(y+y_n<=736 && y+y_n>=100) y=y+y_n;

}

void gracz::ruchy_gracza(bool flaga_gora,bool flaga_prawo,bool flaga_dol,bool flaga_lewo    )
{

    if (flaga_gora) ruch(0,-wspolczynnik_ruchu);
    if (flaga_dol) ruch(0,wspolczynnik_ruchu);
    if (flaga_lewo) ruch(-wspolczynnik_ruchu,0);
    if (flaga_prawo) ruch(wspolczynnik_ruchu,0);



}


