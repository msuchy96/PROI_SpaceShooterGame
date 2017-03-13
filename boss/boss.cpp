#include <iostream>
#include "boss.h"
#include "bron_dod.h"
#include "ogien.h"


boss::boss(int hp_bossa,int moc_bossa,double x_bossa,double y_bossa,int tryb_bossa)
{
    std::cout<<"Tworzy sie boss"<<std::endl;
    hp=hp_bossa;
    moc=moc_bossa;
    x=x_bossa;
    y=y_bossa;
    tryb=tryb_bossa;
}

boss::~boss()
{
    std::cout<<"Niszczy sie boss"<<std::endl;
}

double boss::daj_x()
{
    return x;
}

double boss::daj_y()
{
    return y;
}

int boss::daj_moc()
{
    return moc;
}

void boss::obrazenia(int obrazenia)
{
    hp=hp-obrazenia;
}

int boss::daj_tryb()
{
    return tryb;
}
void boss::tryb1()
{
    y=y+szybkosc;
    if(y>100) zmiana_trybu(2);
    hp=1000;

}
void boss::tryb2()
{
    if(flaga_kier_tryb2) x=x-6*szybkosc;
    else x=x+6*szybkosc;

    if(x>850) flaga_kier_tryb2=true;
    if(x<0) flaga_kier_tryb2=false;

    if(500<hp && hp<800) zmiana_trybu(3);
    if(200<hp && hp<300) zmiana_trybu(3);


}

void boss::tryb3()
{
    if(flaga_kier_tryb2) x=x-8*szybkosc;
    else x=x+8*szybkosc;

    if(x>850) flaga_kier_tryb2=true;
    if(x<0) flaga_kier_tryb2=false;

    if(300<hp && hp<600) zmiana_trybu(5);
    if(0<hp && hp<100) zmiana_trybu(5);

}

void boss::tryb4()
{
   if(flaga_kier_tryb4)   y=y-10*szybkosc;
   else y=y+10*szybkosc;

   if(y>700) flaga_kier_tryb4=true;
    if(y<90)
   {   y=100;
       flaga_kier_tryb4=false;
       zmiana_trybu(3);
   }

}

void boss::tryb5()
{
     if(flaga_kier_tryb4)   y=y-5*szybkosc;
   else y=y+5*szybkosc;
   if(y>700) flaga_kier_tryb4=true;
   if(y<50) flaga_kier_tryb4=false;
   if(200<hp && hp<500)
   {
       zmiana_trybu(2);
       szybkosc=0.02+szybkosc;

   }



}
pocisk* boss::strzal1(double przesun)
{
    pocisk* nowy_pocisk=new pocisk;
    nowy_pocisk->ustaw_wspolrzedne(x+przesun,y+90,moc);
    nowy_pocisk->nastepny=NULL;
    return nowy_pocisk;



}
ogien* boss::strzal2()
{
    ogien* nowy_ogien=new ogien;
    nowy_ogien->ustaw_moc(moc);
    return nowy_ogien;


}
int boss::trafiony(double x_pocisku,double y_pocisku,int moc_pocisku)
{
    if((x-10<=x_pocisku && x+150>x_pocisku && y<=y_pocisku && y+70>=y_pocisku) || (x+25<=x_pocisku && x+125>x_pocisku && y<=y_pocisku && y+120>=y_pocisku))
    {
        hp=hp-moc_pocisku;
        return 1;
    }

return 0;

}

int boss::daj_hp()
{
    return hp;
}

void boss::zmiana_trybu(int nowy_tryb)
{
    tryb=nowy_tryb;
}
