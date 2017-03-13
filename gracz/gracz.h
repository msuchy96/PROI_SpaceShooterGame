#pragma once
#include <iostream>
#include "pocisk.h"
#include "bron_dod.h"
#include "rakiety.h"
#include "fale_dw.h"

class gracz
{
    int hp;
    int moc;
    double x;
    double y;
    double wspolczynnik_ruchu;
    int liczba_rakiet;
    int liczba_fal;


public:
   double daj_x();
   double daj_y();
   int daj_hp();
   int daj_moc();
   int daj_liczbe_rakiet();
   int daj_liczbe_fal();

   double daj_wspol_ruchu();
   void trafiony(int);
   void ruch(double,double);
   void ruchy_gracza(bool,bool,bool,bool);
   void dodaj_rakiety();
   void dodaj_fale();
   int trafienie(double,double,int);
    pocisk* strzal();
    rakieta* strzal_2();
    fala_dzw* strzal_3();


    gracz(int=200,int=20,double=468.0,double=736.0,double=0.7,int=2,int=2);
    ~gracz();
};
