#pragma once
#include <iostream>
#include "pocisk.h"


class mob_typ
{




public:

   virtual double daj_x()=0;
   virtual double daj_y()=0;
   virtual int daj_hp()=0;
   virtual int daj_moc()=0;
   virtual int daj_typ()=0;
   virtual void trafiony(int)=0;
   virtual void ruch(double)=0;
   virtual pocisk* strzal()=0;
   virtual void nadaj_id_typ(int)=0;
   virtual int trafienie(double,double,int)=0;
   virtual ~mob_typ()
   {    }



};
