#include <iostream>
#include "okno_gry.h"


int main()
{

    gra* nowa_gra= new gra;
   nowa_gra->gramy();
   delete nowa_gra;

    return 0;
}
