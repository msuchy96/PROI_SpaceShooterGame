#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <typeinfo>
#include "mob_type2.h"
#include "przeszkoda.h"
#include "okno_gry.h"
#include "gracz.h"
#include "pocisk.h"
#include "rakiety.h"
#include "mob1.h"
#include "boss.h"
#include "mob2.h"
#include "ogien.h"
#include <sstream>
#include <exception>
#include <fstream>
#include "wyjatki.h"

#define VNAZWA(x) #x


gra::gra()
{
    oknoAplikacji.create( sf::VideoMode(1000, 800, 32), "Shooter" );
    std::cout<<"Rozpoczynamy gre:"<<std::endl;
}

gra::~gra()
{
    std::cout<<"Konczymy gre:"<<std::endl;
}

void gra::gramy()
{
    ustawienie_tekstur();
    int  ogr_pocisk,widelki_rakiet=1,widelki_fal=1,wybrany_x;
    bool flaga_p, flaga_l, flaga_g, flaga_d, flaga_kierunku_1, flaga_partii_mob2, flaga_partii_mob3,flaga_kierunku_2,flaga_bron_dod;
    gracz* gracz1;
    boss* boss1=NULL;
    while(oknoAplikacji.isOpen())
    {
        if(smierc==false && wczyt==false) /// warunki poczatkowe ( wejscie rowniez po restarcie gry )
        {
            gracz1= new gracz;
            punkty=0,widelki_rakiet=1,widelki_fal=1;
            ogr_pocisk=0;
            flaga_p=0, flaga_l=0, flaga_g=0, flaga_d=0, flaga_kierunku_1=0, flaga_partii_mob2=1, flaga_partii_mob3=1,flaga_kierunku_2=1;
            liczba_zabitych_1=0, liczba_zabitych_2=0;
            flaga_bron_dod=0,boss_start=0,wygrales=0,szukaj_x=1;
        }
        if(wczyt)
        {
            wczytaj_gre(&gracz1,&widelki_rakiet,&widelki_fal,&flaga_kierunku_1,&flaga_kierunku_2,&flaga_partii_mob2,&flaga_partii_mob3,&boss1);
            ogr_pocisk=0, flaga_p=0, flaga_l=0, flaga_g=0, flaga_d=0, szukaj_x=1,flaga_bron_dod=0,boss_start=0;
            wczyt=false;
        }
        while(oknoAplikacji.isOpen() && smierc==false && wygrales==false)
        {
            sf::Event zdarzenie;
            t1=zegar.getElapsedTime();
            t2=zegar2.getElapsedTime();
            t3=zegar3.getElapsedTime();
            t4=zegar4.getElapsedTime();

            while( oknoAplikacji.pollEvent( zdarzenie )  )
            {
                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right) flaga_p=1;
                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left) flaga_l=1;
                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up) flaga_g=1;
                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down) flaga_d=1;
                if(zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::S && boss_start==false)  /// zapis gry
                    zapis_do_pliku(gracz1,widelki_rakiet,widelki_fal,flaga_kierunku_1,flaga_kierunku_2,flaga_partii_mob2,flaga_partii_mob3);
                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space && ogr_pocisk==0 && wejscie_bossa(boss1))
                {
                    wektor_pociskow.push_back(gracz1->strzal());
                    ogr_pocisk=1;
                }
                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::X && flaga_bron_dod==0 && gracz1->daj_liczbe_rakiet()>0 && wejscie_bossa(boss1))
                {
                    akt_bron_dod_l=(gracz1->strzal_2());
                    akt_bron_dod_l->ustaw_wspolrzedne(gracz1->daj_x()-10,gracz1->daj_y());
                    akt_bron_dod_p=(gracz1->strzal_2());
                    akt_bron_dod_p->ustaw_wspolrzedne(gracz1->daj_x()+50,gracz1->daj_y());
                    flaga_bron_dod=true;  /// ograniczenie pociskow dodatkowych

                }
                if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::C && flaga_bron_dod==0 && gracz1->daj_liczbe_fal()>0 && wejscie_bossa(boss1))
                {
                    akt_bron_dod_l=(gracz1->strzal_3());
                    akt_bron_dod_l->ustaw_wspolrzedne(gracz1->daj_x()-10,gracz1->daj_y());
                    akt_bron_dod_p=(gracz1->strzal_3());
                    akt_bron_dod_p->ustaw_wspolrzedne(gracz1->daj_x()+40,gracz1->daj_y());
                    flaga_bron_dod=true; /// ograniczenie pociskow dodatkowych
                }
                if (zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Right) flaga_p=0;
                if (zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Left) flaga_l=0;
                if (zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Up) flaga_g=0;
                if (zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Down) flaga_d=0;
                if(zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Space) ogr_pocisk=0;
                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape || zdarzenie.type == sf::Event::Closed )
                    oknoAplikacji.close();
            } // while poll Event
            if(boss_start)
            {
               obsluga_bossa(&boss1,&wybrany_x);
            }
            else
            {
               obsluga_rozgrywki(&flaga_partii_mob2,&flaga_partii_mob3);
            }
            if(t2.asSeconds()>1.5 && wektor_mobow.empty()==false)
            {
                int los=(rand()%wektor_mobow.size());
                atakujacy=wektor_mobow[los]->strzal();
                zegar2.restart();
            } /// losowy przeciwnik strzela
            ruchy_mobow2(flaga_kierunku_1,flaga_kierunku_2);
            ruchy_pociskow_i_przeszkod();
            organizacja_ruchem(&flaga_partii_mob2,&flaga_kierunku_1,&flaga_partii_mob3,&flaga_kierunku_2,&flaga_bron_dod);
            kolizje(gracz1,boss1);
            trafienia(gracz1,boss1);
            likwidacje(gracz1,boss1);
            rysowanie(gracz1,boss1);
            gracz1->ruchy_gracza(flaga_g,flaga_p,flaga_d,flaga_l);
            sprawdz_bonusy(&widelki_rakiet,&widelki_fal,gracz1);
            oknoAplikacji.display();
            if(punkty>10) boss_start=true;
        }
        zniszcz_wszystkie(&gracz1,&boss1);

        rysowanie_menu();
    }///while okno aplikacji is open
}

void gra::obsluga_bossa(boss** boss1,int* wybrany_x)
{

     if(t1.asSeconds()>2.5)
                {
                    losuj_przeszkode();
                    zegar.restart();
                }

                if(wektor_mobow.empty())
                {
                    if(*boss1==NULL) *boss1=stworz_bossa();

                    switch ((*boss1)->daj_tryb()) /// switch obslugujacy tryby bossa
                    {
                    case 1:
                        (*boss1)->tryb1();
                        break;
                    case 2:

                        (*boss1)->tryb2();
                        if(t3.asSeconds()>1.5)
                        {
                            tryb2(*boss1);
                            zegar3.restart();
                        }
                        break;
                    case 3:
                        if(szukaj_x)
                        {
                            (*wybrany_x)=losuj_x();
                            szukaj_x=false;
                        }
                        (*boss1)->tryb3();

                        if((int)(*boss1)->daj_x()>(*wybrany_x)-2 && (int)(*boss1)->daj_x()<(*wybrany_x)+2)
                        {
                            (*boss1)->zmiana_trybu(4);
                            szukaj_x=true;
                        }

                        break;
                    case 4:
                        (*boss1)->tryb4();
                        break;
                    case 5:
                        (*boss1)->tryb5();
                        if(t3.asSeconds()>1.0)
                        {
                            tryb2(*boss1);
                            zegar3.restart();
                        }
                        if(t2.asSeconds()>1.2)
                        {
                            tryb5(*boss1);
                            zegar2.restart();
                        }
                        break;

                    }   ///switch
                }



}

void gra::obsluga_rozgrywki(bool* flaga_partii_mob2,bool* flaga_partii_mob3)
{

 if (t1.asSeconds()>0.7)
                {
                    losuj_przeszkode();
                    if(liczba_typ(1)<4 && (*flaga_partii_mob2)==1)
                    {
                        stworzenie_przeciwnika(1);
                    } /// wchodzenie przeciwnikow mob1 seriami
                    zegar.restart();
                }
                if(t3.asSeconds()>0.3)
                {
                    if(liczba_typ(2)<3 && (*flaga_partii_mob3)==1)
                    {
                        stworzenie_przeciwnika(2);

                    }
                    zegar3.restart();
                } ///wchodzenie przeciwnikow mob2 seriami

}

void gra::zapis_do_pliku(gracz* gracz1,int widelki_rakiet,int widelki_fal,bool flaga_kier_1,bool flaga_kier_2,bool flaga_partii_mob2,bool flaga_partii_mob3)
{
    plikzapisu.open("plikzapisu.txt", ios::out);
    if(!plikzapisu.good())
    {
        cout << "BLAD OTWARCIA PLIKU PLIKZAPISU.TXT" << endl;
        return;
    }
    ///obsluga ruchow
    plikzapisu <<widelki_fal<<" "<<widelki_rakiet<<" "<<flaga_kier_1<<" "<<flaga_kier_2<<" "<<flaga_partii_mob2<<" "<<flaga_partii_mob3<<" "<<punkty<<" "<<liczba_zabitych_1<<" "<<liczba_zabitych_2<<endl;

    ///info gracz
    plikzapisu<<gracz1->daj_x()<<" "<<gracz1->daj_y()<<" "<<gracz1->daj_hp()<<" "<<gracz1->daj_moc()<<" "<<gracz1->daj_wspol_ruchu()<<" "<<gracz1->daj_liczbe_rakiet()<<" "<<gracz1->daj_liczbe_fal()<<endl;

    ///info przeszkody
    plikzapisu<<wektor_przeszkod.size()<<endl;
    for(int i=0; i<wektor_przeszkod.size(); i++)
    {
        plikzapisu<<wektor_przeszkod[i]->daj_x()<<" "<<wektor_przeszkod[i]->daj_y()<<endl;
    }

    ///info moby
    plikzapisu<<wektor_mobow.size()<<endl;
    for(int i=0; i<wektor_mobow.size(); i++)
    {
        plikzapisu<<wektor_mobow[i]->daj_typ()<<" "<<wektor_mobow[i]->daj_x()<<" "<<wektor_mobow[i]->daj_y()<<" "<<wektor_mobow[i]->daj_hp()<<" "<<wektor_mobow[i]->daj_moc()<<endl;
    }

    plikzapisu.close();

}

void gra::wczytaj_gre(gracz** gracz1,int* widelki_rakiet,int* widelki_fal,bool* flaga_kier_1,bool* flaga_kier_2,bool* flaga_partii_mob2,bool* flaga_partii_mob3,boss** boss1)
{

    try
    {
        plikzapisu.open("plikzapisu.txt", ios::in);
        if(!plikzapisu.good())
        {
            throw Blad_otwarcia();
        };

        double x,y,wspol_ruch;
        int hp,moc,typ,licz_rak,licz_fal,licznik;
        int kierunku_1,kierunku_2,partii_mob2,partii_mob3;
        if(!(plikzapisu.peek() == std::ifstream::traits_type::eof()))
        {

            plikzapisu>>(*widelki_rakiet)>>(*widelki_fal)>>kierunku_1>>kierunku_2>>partii_mob2>>partii_mob3>>punkty>>liczba_zabitych_1>>liczba_zabitych_2;
            plikzapisu>>x>>y>>hp>>moc>>wspol_ruch>>licz_rak>>licz_fal;

            if(x<0) /// sprawdzenie czy zmienna  jest dodatnia
            {
                cout<<"U gracza zmienna "<<VNAZWA(x);
                throw x;
            }
            if(y<0) /// sprawdzenie czy zmienna y jest dodatnia
            {
                cout<<"U gracza zmienna "<<VNAZWA(y);
                throw y;
            }

            (*gracz1)=new gracz(hp,moc,x,y,wspol_ruch,licz_fal,licz_rak);
            plikzapisu>>licznik;
            for(int i=0; i<licznik; i++)
            {
                plikzapisu>>x>>y;
                przeszkoda* nowa=new przeszkoda;
                wektor_przeszkod.push_back(nowa);
                wektor_przeszkod[i]->nadaj_wspolrzedne(x,y);
            }

            plikzapisu>>licznik; /// liczba przeciwnikow
            for(int i=0; i<licznik; i++)
            {
                plikzapisu>>typ>>x>>y>>hp>>moc;
                if(x<0)
                {
                    cout<<"U moba o numerze "<<i<<" zmienna "<<VNAZWA(x);
                    throw x;
                }
                if(y<0)
                {
                    cout<<"U moba o numerze "<<i<<" zmienna "<<VNAZWA(y);
                    throw y;
                }
                if(typ!=1 && typ!=2) throw ++i; /// zly typ przeciwnika
                mob_typ* nowy_mobek;
                if(typ==1)  nowy_mobek=new mob1(hp,moc,x,y);
                if(typ==2)  nowy_mobek=new mob2(hp,moc,x,y);

                nowy_mobek->nadaj_id_typ(typ);
                wektor_mobow.push_back(nowy_mobek);                                               //

            }
            ///ktoras z flag zle zapisana
            if(kierunku_1!=1 && kierunku_1!=0) throw VNAZWA(kierunku_1); ///
            if(kierunku_2!=1 && kierunku_2!=0) throw VNAZWA(kierunku_2);
            if(partii_mob2!=1 && partii_mob2!=0) throw VNAZWA(partii_mob2);
            if(partii_mob3!=1 && partii_mob3!=0) throw VNAZWA(partii_mob3);

            (*flaga_kier_1)=kierunku_1;
            (*flaga_kier_1)=kierunku_2;
            (*flaga_partii_mob2)=partii_mob2;
            (*flaga_partii_mob3)=partii_mob3;

        }
        else
        {
            throw Pusty_plik();
            smierc=true;
        }
    }
    catch(exception &e)
    {
        std::cout<<" Wyjatek! "<<endl;
        std::cout<<e.what()<<endl;
        zniszcz_wszystkie(&(*gracz1),&(*boss1));

        smierc=true;
    }

    plikzapisu.close();

}

boss* gra::stworz_bossa()
{
    boss* nowy_boss=new boss;
    return nowy_boss;
}

void gra::sprawdz_bonusy(int* widelki_rakiet,int* widelki_fal,gracz* gracz1)
{
    /// liczba rakiet zwieksza sie co 50 ptk
    if(punkty>=(50*(*widelki_rakiet)))
    {
        gracz1->dodaj_rakiety();
        (*widelki_rakiet)++;
    }
   /// liczba pociskow sonicznych zwikesza co 50 ptk
    if(punkty>=(75*(*widelki_fal)))
    {
        gracz1->dodaj_fale();
        (*widelki_fal)++;
    }


}

void gra::rysowanie_menu()
{
    oknoAplikacji.clear( sf::Color::Black );
    if(wygrales==true) oknoAplikacji.draw(wygrana);


    ostringstream wynik2,zabitych,zabitych2;
    string wynik_string,liczba_zab;

    wynik2 << punkty;
    wynik_string=wynik2.str();
    wynik_string="Twoj wynik: "+wynik_string;
    wynik.setString(wynik_string);

    zabitych<<liczba_zabitych_1;
    zabitych2<<liczba_zabitych_2;
    liczba_zab="Zniszczonych: "+liczba_zab+"                x"+zabitych.str()+"                x"+zabitych2.str();


    liczba_zabitych.setString(liczba_zab);
    przeciwnik.setPosition(440,450);
    przeciwnik.setScale(1.75,1.75);
    przeciwnik2.setPosition(690,470);
    przeciwnik2.setScale(1.75,1.75);
    wynik.setScale(1.5,1.5);
    wynik.setPosition(350,100);

    oknoAplikacji.draw(restart);
    oknoAplikacji.draw(esc);
    oknoAplikacji.draw(wynik);
    oknoAplikacji.draw(wczytaj);
    oknoAplikacji.draw(przeciwnik);
    oknoAplikacji.draw(przeciwnik2);
    oknoAplikacji.draw(liczba_zabitych);
    oknoAplikacji.display();

    wynik.setScale(1,1);
    wynik.setPosition(0,0);
    przeciwnik.setScale(1,1);
    przeciwnik2.setScale(1,1);

    sf::Event zdarzenie2;
    /// obsluga menu
    while(oknoAplikacji.pollEvent( zdarzenie2 ) )
    {
        if (zdarzenie2.type == sf::Event::KeyPressed && zdarzenie2.key.code == sf::Keyboard::R)
        {
            smierc=false;
            boss_start=false;

        }
        if (zdarzenie2.type == sf::Event::KeyPressed && zdarzenie2.key.code == sf::Keyboard::W)
        {
            wczyt=true;
            boss_start=false;
            smierc=false;

        }
        if (zdarzenie2.type == sf::Event::KeyPressed && zdarzenie2.key.code == sf::Keyboard::Escape || zdarzenie2.type == sf::Event::Closed )
            oknoAplikacji.close();
    }

}

void gra::tryb2(boss* boss1)
{
     ///strzelanie podczas trybu2
    pierw_pocisk_boss=(boss1->strzal1(10.0));
    akt_pocisk_boss=pierw_pocisk_boss;
    for(int i=2; i<9; i++)
    {
        if(i<5)(akt_pocisk_boss->nastepny)=(boss1->strzal1(i*10.0));
        else (akt_pocisk_boss->nastepny)=(boss1->strzal1(i*10.0+30.0));
        akt_pocisk_boss=(akt_pocisk_boss->nastepny);
        akt_pocisk_boss->nastepny=NULL;

    }
}

void gra::tryb5(boss* boss1)
{
    ///strzelanie bossa w trybie5
    lewa_bossa=boss1->strzal2();
    lewa_bossa->ustaw_wspolrzedne(boss1->daj_x()-20,boss1->daj_y()+30);
    prawa_bossa=boss1->strzal2();
    prawa_bossa->ustaw_wspolrzedne(boss1->daj_x()+120,boss1->daj_y()+30);


}

void gra::rysowanie(gracz* gracz1,boss* boss1)
{
    ostringstream hp,obrazenia,mob2_hp,rakiety,fale;
    string str,str2,str3,str4,str5;
    hp << gracz1->daj_hp();
    obrazenia << gracz1->daj_moc();
    rakiety << gracz1->daj_liczbe_rakiet();
    fale << gracz1->daj_liczbe_fal();
    str2=obrazenia.str();
    str=hp.str();
    str4=rakiety.str();
    str5=fale.str();
    str2="moc: " + str2;
    str="hp: " + str;
    str4="rakiet: " +str4;
    str5="pocisk soniczny: "+str5;
    tekst_hp.setString(str);
    tekst_obrazenia.setString(str2);
    tekst_fale.setString(str5);
    tekst_rakiety.setString(str4);

    ostringstream wynik2;
    string wynik_string;
    wynik2 << punkty;
    wynik_string=wynik2.str();
    wynik_string="Punkty: "+ wynik_string;
    wynik.setString(wynik_string);


    oknoAplikacji.clear( sf::Color::Black );
    for(int i=0; i<wektor_mobow.size() || i<wektor_przeszkod.size() || i<wektor_pociskow.size(); i++)
    {
        if(i<wektor_mobow.size())
        {

            if(wektor_mobow[i]->daj_typ()==1) przeciwnik.setPosition(wektor_mobow[i]->daj_x(),wektor_mobow[i]->daj_y());
            if(wektor_mobow[i]->daj_typ()==2) przeciwnik2.setPosition(wektor_mobow[i]->daj_x(),wektor_mobow[i]->daj_y());
            if(wektor_mobow[i]->daj_typ()==1) oknoAplikacji.draw(przeciwnik);
            if(wektor_mobow[i]->daj_typ()==2) oknoAplikacji.draw(przeciwnik2);
            mob2_hp<<wektor_mobow[i]->daj_hp();
            str3=mob2_hp.str();
            hp_mob2.setString(str3);
            hp_mob2.setCharacterSize(25);
            hp_mob2.setColor(sf::Color::Green);
            hp_mob2.setPosition(wektor_mobow[i]->daj_x()+15,wektor_mobow[i]->daj_y()+30);
            oknoAplikacji.draw(hp_mob2);
            mob2_hp.str( "" );


        }
        if(i<wektor_przeszkod.size())
        {
            chmura.setPosition(wektor_przeszkod[i]->daj_x(),wektor_przeszkod[i]->daj_y());
            oknoAplikacji.draw(chmura);
        }
        if(i<wektor_pociskow.size())
        {
            pocisk_s.setPosition(wektor_pociskow[i]->daj_x(),wektor_pociskow[i]->daj_y());
            oknoAplikacji.draw(pocisk_s);
        }

    }

    if(atakujacy!=NULL)
    {
        pocisk_s.setPosition(atakujacy->daj_x(),atakujacy->daj_y());
        oknoAplikacji.draw(pocisk_s);
    }
    if(akt_bron_dod_l!=NULL)
    {
        switch (akt_bron_dod_l->daj_typ())
        {
        case 1:
            rakietka.setPosition(akt_bron_dod_l->daj_x(),akt_bron_dod_l->daj_y());
            oknoAplikacji.draw(rakietka);
            break;
        case 2:
            fala.setPosition(akt_bron_dod_l->daj_x(),akt_bron_dod_l->daj_y());
            oknoAplikacji.draw(fala);
            break;

        }
    }
    if(akt_bron_dod_p!=NULL)
    {

        switch (akt_bron_dod_p->daj_typ())
        {
        case 1:
            rakietka.setPosition(akt_bron_dod_p->daj_x(),akt_bron_dod_p->daj_y());
            oknoAplikacji.draw(rakietka);
            break;
        case 2:
            fala2.setPosition(akt_bron_dod_p->daj_x(),akt_bron_dod_p->daj_y());
            oknoAplikacji.draw(fala2);
            break;

        }

    }
    if(pierw_pocisk_boss!=NULL)
    {
        akt_pocisk_boss=pierw_pocisk_boss;

        while(akt_pocisk_boss!=NULL)
        {

            pocisk_s.setPosition(akt_pocisk_boss->daj_x(),akt_pocisk_boss->daj_y());
            oknoAplikacji.draw(pocisk_s);
            akt_pocisk_boss=akt_pocisk_boss->nastepny;

        }

    }
    if(lewa_bossa!=NULL)
    {
        ogien_l.setPosition(lewa_bossa->daj_x(),lewa_bossa->daj_y());
        oknoAplikacji.draw(ogien_l);

    }
    if(prawa_bossa!=NULL)
    {
        ogien_p.setPosition(prawa_bossa->daj_x(),prawa_bossa->daj_y());
        oknoAplikacji.draw(ogien_p);
    }
    statek.setPosition(gracz1->daj_x(),gracz1->daj_y());
    if(boss1!=NULL)
    {
        bos.setPosition(boss1->daj_x(),boss1->daj_y());
        oknoAplikacji.draw(bos);

        mob2_hp<<boss1->daj_hp();
        str3=mob2_hp.str();
        hp_mob2.setString(str3);
        hp_mob2.setCharacterSize(40);
        hp_mob2.setColor(sf::Color::Red);
        hp_mob2.setPosition(boss1->daj_x()+40,boss1->daj_y()-40);
        oknoAplikacji.draw(hp_mob2);
        mob2_hp.str( "" );
    }
    oknoAplikacji.draw(statek);
    oknoAplikacji.draw(tekst_hp);
    oknoAplikacji.draw(tekst_obrazenia);
    oknoAplikacji.draw(tekst_rakiety);
    oknoAplikacji.draw(tekst_fale);
    oknoAplikacji.draw(wynik);
}

void gra::ustawienie_tekstur()
{
    tekstura1.loadFromFile( "przeciwnik.png" );
    przeciwnik.setTexture( tekstura1 );
    tekstura2.loadFromFile("chmura.png");
    chmura.setTexture(tekstura2);
    tekstura3.loadFromFile("statek.png");
    statek.setTexture(tekstura3);
    tekstura4.loadFromFile("pocisk.png");
    pocisk_s.setTexture(tekstura4);
    tekstura5.loadFromFile("przeciwnik2.png");
    przeciwnik2.setTexture(tekstura5);
    tekstura6.loadFromFile("Rocket_Arrow.png");
    rakietka.setTexture(tekstura6);
    tekstura7.loadFromFile("Music1.png");
    fala.setTexture(tekstura7);
    tekstura8.loadFromFile("Music2.png");
    fala2.setTexture(tekstura8);
    czcionka.loadFromFile("Pacifico.ttf");
    brazowy_statek.loadFromFile("boss.png");
    bos.setTexture(brazowy_statek);
    kulaognia_l.loadFromFile("lewy_ogien.png");
    ogien_l.setTexture(kulaognia_l);
    kulaognia_p.loadFromFile("prawy_ogien.png");
    ogien_p.setTexture(kulaognia_p);
    tekst_hp.setFont(czcionka);
    tekst_hp.setPosition(0,760);
    tekst_obrazenia.setFont(czcionka);
    tekst_obrazenia.setPosition(900,690);
    tekst_rakiety.setFont(czcionka);
    tekst_fale.setFont(czcionka);
    tekst_rakiety.setPosition(880,730);
    tekst_fale.setPosition(770,760);
    restart.setFont(czcionka);
    restart.setString("Kliknij [R], aby rozpoczac ponownie.");
    restart.setPosition(250,650);
    wczytaj.setFont(czcionka);
    wczytaj.setString("Kliknij [W], aby wczytac gre z pliku.");
    wczytaj.setPosition(245,700);
    wynik.setFont(czcionka);
    wynik.setScale(1,1);
    wynik.setPosition(0,0);
    esc.setString("Klinikj [Esc], aby wyjsc.");
    esc.setPosition(320,750);
    esc.setFont(czcionka);
    wygrana.setFont(czcionka);
    wygrana.setString("WYGRALES!");
    wygrana.setPosition(260,280);
    wygrana.setScale(2,2);
    hp_mob2.setFont(czcionka);
    liczba_zabitych.setFont(czcionka);
    liczba_zabitych.setPosition(100,500);
    liczba_zabitych.setScale(1.5,1.5);

}

void gra::zniszcz_wszystkie(gracz** gracz1,boss** boss1)
{

 if((*gracz1)!=NULL)
        {
            delete (*gracz1);
            *gracz1=NULL;
            smierc=true;
        }
        if((*boss1)!=NULL)
        {
            delete (*boss1);
            *boss1=NULL;
        }

    if(wektor_przeszkod.empty()==false)
        for(int i=0; i<wektor_przeszkod.size(); i++)
        {
            delete wektor_przeszkod[i];
            wektor_przeszkod[i]=NULL;

        }
    wektor_przeszkod.clear();
    if(wektor_mobow.empty()==false)
        for(int i=0; i<wektor_mobow.size(); i++)
        {
            delete wektor_mobow[i];
            wektor_mobow[i]=NULL;


        }
    wektor_mobow.clear();
    if(wektor_pociskow.empty()==false)
        for(int i=0; i<wektor_pociskow.size(); i++)
        {

            delete wektor_pociskow[i];
            wektor_pociskow[i]=NULL;


        }
    wektor_pociskow.clear();
    if(atakujacy!=NULL)
    {

        delete atakujacy;
        atakujacy=NULL;


    }
    if(akt_bron_dod_l!=NULL)
    {
        delete akt_bron_dod_l;
        akt_bron_dod_l=NULL;

    }
    if(akt_bron_dod_p!=NULL)
    {
        delete akt_bron_dod_p;
        akt_bron_dod_p=NULL;

    }
    if(pierw_pocisk_boss!=NULL)
    {
        akt_pocisk_boss=pierw_pocisk_boss;
        pocisk* pomocniczy=NULL;
        while(akt_pocisk_boss!=NULL)
        {
            pomocniczy=akt_pocisk_boss;
            delete akt_pocisk_boss;
            akt_pocisk_boss=NULL;
            if((pomocniczy->nastepny)!=NULL) akt_pocisk_boss=pomocniczy->nastepny;

        }
    }
    pierw_pocisk_boss=NULL;
    if(lewa_bossa!=NULL)
    {
        delete lewa_bossa;
        lewa_bossa=NULL;
    }
    if(prawa_bossa!=NULL)
    {
        delete prawa_bossa;
        prawa_bossa=NULL;
    }


}

void gra::likwidacje(gracz* gracz1,boss* boss1) /// funkcja sprawdzajaca ktorzy przeciwnicy maj¹ <= 0 punktow zycia
{
    if(wektor_mobow.empty()==false)
        for(int i=0; i<wektor_mobow.size(); i++)
        {
            if(wektor_mobow[i]->daj_hp()<=0)
            {
                if(wektor_mobow[i]->daj_typ()==1)
                {
                    punkty+=20;
                    liczba_zabitych_1++;
                }
                if(wektor_mobow[i]->daj_typ()==2)
                {
                    punkty+=15;
                    liczba_zabitych_2++;
                }
                delete wektor_mobow[i];
                wektor_mobow.erase(wektor_mobow.begin()+i);
            }

        }
    if(gracz1->daj_hp()<=0) smierc=true;
    if(boss1!=NULL) if(boss1->daj_hp()<=0) wygrales=true;

}

void gra::stworzenie_przeciwnika(int typ)
{
    /// w zaleznosci od typu powstaje konkretny przeciwnik
    mob_typ* nowy_mobek;
    if(typ==1)  nowy_mobek=stworz_mob1();
    if(typ==2)  nowy_mobek=stworz_mob2();
    nowy_mobek->nadaj_id_typ(typ);
    wektor_mobow.push_back(nowy_mobek);

}

mob1* gra::stworz_mob1()
{
    mob1* nowy_mob=new mob1;
    return nowy_mob;
}

mob2* gra::stworz_mob2()
{
    mob2* nowy_mob=new mob2(100,10,-10,500);
    return nowy_mob;
}

int gra::liczba_typ(int szukany_typ) ///sprawdzenie ile jest przeciwnikow na planszy danego typu
{
    int licznik=0;
    if(wektor_mobow.empty()==false)
        for(int i=0; i<wektor_mobow.size(); i++)
        {
            if(wektor_mobow[i]->daj_typ()==szukany_typ) licznik++;
        }

    return licznik;

}

void gra::kolizje(gracz* gracz1, boss* boss1)
{
    int kolizja=0;
    if(wektor_przeszkod.empty()==false)
        for(int i=0; i<wektor_przeszkod.size(); i++)
        {
            if((wektor_przeszkod[i]->daj_x()<=gracz1->daj_x()+50 && wektor_przeszkod[i]->daj_x()+50>=gracz1->daj_x()+50) || (wektor_przeszkod[i]->daj_x()-5<=gracz1->daj_x() && wektor_przeszkod[i]->daj_x()+50>=gracz1->daj_x()))
                kolizja++;
            if((wektor_przeszkod[i]->daj_y()<=gracz1->daj_y()+50 && wektor_przeszkod[i]->daj_y()+50>=gracz1->daj_y()+50) || (wektor_przeszkod[i]->daj_y()<=gracz1->daj_y() && wektor_przeszkod[i]->daj_y()+50>=gracz1->daj_y()))
                kolizja++;

            if(kolizja==2) smierc=true;
            else kolizja=0;
        }
    if(kolizja!=2)
        if(wektor_mobow.empty()==false)
            for(int i=0; i<wektor_mobow.size(); i++)
            {
                if(wektor_mobow[i]->daj_typ()==2)
                {

                    if((wektor_mobow[i]->daj_x()<=gracz1->daj_x()+50 && wektor_mobow[i]->daj_x()+50>=gracz1->daj_x()+50) || (wektor_mobow[i]->daj_x()-5<=gracz1->daj_x() && wektor_mobow[i]->daj_x()+50>=gracz1->daj_x()))
                        kolizja++;
                    if((wektor_mobow[i]->daj_y()<=gracz1->daj_y()+50 && wektor_mobow[i]->daj_y()+50>=gracz1->daj_y()+50) || (wektor_mobow[i]->daj_y()<=gracz1->daj_y() && wektor_mobow[i]->daj_y()+50>=gracz1->daj_y()))
                        kolizja++;

                    if(kolizja==2) smierc=true;
                    else kolizja=0;
                }
            }
    kolizja=0;
    if(boss1!=NULL)
    {
        if(boss1->daj_x()-10<=gracz1->daj_x()+50 && boss1->daj_x()+150>gracz1->daj_x() && boss1->daj_y()<=gracz1->daj_y()+50 && boss1->daj_y()+70>=gracz1->daj_y()) kolizja++;
        if(boss1->daj_x()+25<=gracz1->daj_x()+50 && boss1->daj_x()+125>gracz1->daj_x() && boss1->daj_y()<=gracz1->daj_y()+50 && boss1->daj_y()+120>=gracz1->daj_y()) kolizja++;
        if(kolizja>0) smierc=true;
    }

}

void gra::losuj_przeszkode()
{
    przeszkoda* nowa_przeszkoda=new przeszkoda;
    nowa_przeszkoda->losuj_wspolrzedne();
    wektor_przeszkod.push_back(nowa_przeszkoda);
}

int gra::losuj_x()
{
    int x;
    x=(rand()%850);
    return x;

}

void gra::trafienia(gracz* gracz1,boss* boss1) /// funkcka odpowiadajaca za trafienia pociskow
{

    if(wektor_pociskow.empty()==false)

        for(int i=0; i<wektor_pociskow.size(); i++)
        {
            if(trafienie_w_mob2(wektor_pociskow[i]->daj_x(),wektor_pociskow[i]->daj_y(),i)) continue;

            if(trafienie_w_przeszkoda(wektor_pociskow[i]->daj_x(),wektor_pociskow[i]->daj_y()))
            {
                delete wektor_pociskow[i];
                wektor_pociskow.erase(wektor_pociskow.begin()+i);
                continue;
            }

            if(boss1!=NULL && boss1->trafiony(wektor_pociskow[i]->daj_x(),wektor_pociskow[i]->daj_y(),wektor_pociskow[i]->daj_zniszczenia()))
            {
                delete wektor_pociskow[i];
                wektor_pociskow.erase(wektor_pociskow.begin()+i);
                punkty+=2;
                continue;
            }
        }

    if(atakujacy!=NULL)
    {
        if(trafienie_w_przeszkoda(atakujacy->daj_x(),atakujacy->daj_y()))
        {
            delete atakujacy;
            atakujacy=NULL;

        }
        else if(gracz1->trafienie(atakujacy->daj_x(),atakujacy->daj_y(),atakujacy->daj_zniszczenia()))
        {
            delete atakujacy;
            atakujacy=NULL;
        }
    }

    if(akt_bron_dod_l!=NULL)
    {
        if(trafienie_w_mob_bron_dod(akt_bron_dod_l))
        {
            delete akt_bron_dod_l;
            akt_bron_dod_l=NULL;
        }
        else if(trafienie_w_przeszkode_bron_dod(akt_bron_dod_l))
        {
            if(akt_bron_dod_l->destrukcja())
            {
                delete akt_bron_dod_l;
                akt_bron_dod_l=NULL;
            }

        }
        else if(boss1!=NULL && boss1->trafiony(akt_bron_dod_l->daj_x(),akt_bron_dod_l->daj_y(),akt_bron_dod_l->daj_zniszczenia()*2))
        {
            delete akt_bron_dod_l;
            akt_bron_dod_l=NULL;
            punkty+=10;
        }

    }

    if(akt_bron_dod_p!=NULL)
    {
        if(trafienie_w_mob_bron_dod(akt_bron_dod_p))
        {
            delete akt_bron_dod_p;
            akt_bron_dod_p=NULL;
        }
        else if(trafienie_w_przeszkode_bron_dod(akt_bron_dod_p))
        {
            if(akt_bron_dod_p->destrukcja())
            {
                delete akt_bron_dod_p;
                akt_bron_dod_p=NULL;
            }

        }
        else if( boss1!=NULL && boss1->trafiony(akt_bron_dod_p->daj_x(),akt_bron_dod_p->daj_y(),akt_bron_dod_p->daj_zniszczenia()*2))
        {
            delete akt_bron_dod_p;
            akt_bron_dod_p=NULL;
            punkty+=10;
        }

    }
    if(lewa_bossa!=NULL)
    {
        if(gracz1->trafienie(lewa_bossa->daj_x()-20,lewa_bossa->daj_y()-20,lewa_bossa->daj_zniszczenia()))
        {
            delete lewa_bossa;
            lewa_bossa=NULL;
        }
        else if(trafienie_w_przeszkoda(lewa_bossa->daj_x(),lewa_bossa->daj_y()))
        {
            delete lewa_bossa;
            lewa_bossa=NULL;
        }

    }
    if(prawa_bossa!=NULL)
    {
        if(gracz1->trafienie(prawa_bossa->daj_x()+30,prawa_bossa->daj_y()-20,prawa_bossa->daj_zniszczenia()))
        {
            delete prawa_bossa;
            prawa_bossa=NULL;
        }
        else if(trafienie_w_przeszkoda(prawa_bossa->daj_x(),prawa_bossa->daj_y()))
        {
            delete prawa_bossa;
            prawa_bossa=NULL;
        }


    }

    if(pierw_pocisk_boss!=NULL)
    {
        akt_pocisk_boss=pierw_pocisk_boss;
        pocisk* poprzednik;
        poprzednik=pierw_pocisk_boss;
        while(akt_pocisk_boss!=NULL)
        {



            if(gracz1->trafienie(akt_pocisk_boss->daj_x(),akt_pocisk_boss->daj_y(),akt_pocisk_boss->daj_zniszczenia()))
            {
                if(akt_pocisk_boss==pierw_pocisk_boss)
                {
                    pierw_pocisk_boss=akt_pocisk_boss->nastepny;
                    delete akt_pocisk_boss;
                    akt_pocisk_boss=pierw_pocisk_boss;
                    continue;
                }
                else if(akt_pocisk_boss->nastepny==NULL)
                {
                    delete akt_pocisk_boss;
                    akt_pocisk_boss=NULL;
                    poprzednik->nastepny=NULL;
                }
                else
                {
                    poprzednik->nastepny=akt_pocisk_boss->nastepny;
                    delete akt_pocisk_boss;
                    akt_pocisk_boss=poprzednik->nastepny;
                }
            }

            poprzednik=akt_pocisk_boss;
            if(akt_pocisk_boss!=NULL) akt_pocisk_boss=akt_pocisk_boss->nastepny;

        }

    }


}

int gra::trafienie_w_przeszkoda(double x_pocisku,double y_pocisku)
{
    if(wektor_przeszkod.empty()==false)
        for(int i=0; i<wektor_przeszkod.size(); i++)
        {
            if(wektor_przeszkod[i]->trafienie(x_pocisku,y_pocisku)) return 1;
        }

    return 0;
}

int gra::trafienie_w_mob2(double x_pocisku,double y_pocisku,int indeks_pocisku)
{
    if(wektor_mobow.empty()==false)
        for(int i=0; i<wektor_mobow.size(); i++)
        {
            if(wektor_mobow[i]->trafienie(x_pocisku,y_pocisku,wektor_pociskow[indeks_pocisku]->daj_zniszczenia()))
            {

                delete wektor_pociskow[indeks_pocisku];
                wektor_pociskow.erase(wektor_pociskow.begin()+indeks_pocisku);
                return 1;
            }
        }
    return 0;
}

int gra::trafienie_w_mob_bron_dod(bron_dodatkowa* akt)
{

    if(wektor_mobow.empty()==false)
        for(int i=0; i<wektor_mobow.size(); i++)
        {

            if(wektor_mobow[i]->trafienie(akt->daj_x(),akt->daj_y(),akt->daj_zniszczenia()))
            {

                if(akt->destrukcja()) return 1;
            }
        }

    return 0;

}

int gra::trafienie_w_przeszkode_bron_dod(bron_dodatkowa* akt)
{
    if(wektor_przeszkod.empty()==false)
        for(int i=0; i<wektor_przeszkod.size(); i++)
        {

            if(wektor_przeszkod[i]->trafienie(akt->daj_x(),akt->daj_y()))
            {
                if(akt->niszcz_przeszkode())
                {
                    delete wektor_przeszkod[i];
                    wektor_przeszkod.erase(wektor_przeszkod.begin()+i);
                    return 1;
                }
            }
        }

    return 0;


}

void gra::ruchy_pociskow_i_przeszkod()
{


    if(wektor_przeszkod.empty()==false)
        for(int i=0; i<wektor_przeszkod.size(); i++)
        {
            wektor_przeszkod[i]->ruch(0,0.2);
            if(wektor_przeszkod[i]->daj_y()>850)
            {
                punkty+=2;
                delete wektor_przeszkod[i];
                wektor_przeszkod.erase(wektor_przeszkod.begin()+i);
            }
        }
    if(wektor_pociskow.empty()==false)
        for(int i=0; i<wektor_pociskow.size(); i++)
        {
            wektor_pociskow[i]->ruch(-1.5);
            if(wektor_pociskow[i]->daj_y()<-10)
            {
                delete wektor_pociskow[i];
                wektor_pociskow.erase(wektor_pociskow.begin()+i);
            }

        }
    if(atakujacy!=NULL)
    {
        atakujacy->ruch(1.0);
        if(atakujacy->daj_y()>800)
        {
            delete atakujacy;
            atakujacy=NULL;
        }
    }

    if(akt_bron_dod_l!=NULL)
    {

        akt_bron_dod_l->ruch(true);
        if(akt_bron_dod_l->daj_y()<-10)
        {
            delete akt_bron_dod_l;
            akt_bron_dod_l=NULL;
        }

    }

    if(akt_bron_dod_p!=NULL)
    {

        akt_bron_dod_p->ruch(false);
        if(akt_bron_dod_p->daj_y()<-10)
        {
            delete akt_bron_dod_p;
            akt_bron_dod_p=NULL;
        }

    }
    if(lewa_bossa!=NULL)
    {
        lewa_bossa->ruch(true);
        if(lewa_bossa->daj_x()<0)
        {
            delete lewa_bossa;
            lewa_bossa=NULL;
        }

    }
    if(prawa_bossa!=NULL)
    {
        prawa_bossa->ruch(false);
        if(prawa_bossa->daj_x()>1000)
        {
            delete prawa_bossa;
            prawa_bossa=NULL;
        }

    }
    if(pierw_pocisk_boss!=NULL)
    {
        akt_pocisk_boss=pierw_pocisk_boss;
        pocisk* poprzednik;
        poprzednik=pierw_pocisk_boss;
        while(akt_pocisk_boss!=NULL)
        {

            akt_pocisk_boss->ruch(0.8);

            if(akt_pocisk_boss->daj_y()>810)
            {
                if(akt_pocisk_boss==pierw_pocisk_boss)
                {
                    pierw_pocisk_boss=akt_pocisk_boss->nastepny;
                    delete akt_pocisk_boss;
                    akt_pocisk_boss=pierw_pocisk_boss;
                    continue;
                }
                else if(akt_pocisk_boss->nastepny==NULL)
                {

                    delete akt_pocisk_boss;
                    akt_pocisk_boss=poprzednik;

                }
                else
                {
                    poprzednik->nastepny=akt_pocisk_boss->nastepny;
                    delete akt_pocisk_boss;
                    akt_pocisk_boss=poprzednik->nastepny;

                }
            }

            poprzednik=akt_pocisk_boss;
            akt_pocisk_boss=akt_pocisk_boss->nastepny;


        }

    }

}

void gra::ruchy_mobow2(bool flaga_kierunku_1,bool flaga_kierunku_2)
{
    double x_mob2,x_mob3;

    if(flaga_kierunku_1) x_mob2=0.15;
    else x_mob2=-0.15;
    if(flaga_kierunku_2) x_mob3=0.4;
    else x_mob3=-0.4;

    if(wektor_mobow.empty()==false )

        for(int i=0; i< wektor_mobow.size(); i++)
        {
            if(wektor_mobow[i]->daj_typ()==1) wektor_mobow[i]->ruch(x_mob2);
            if(wektor_mobow[i]->daj_typ()==2) wektor_mobow[i]->ruch(x_mob3);
        }

}

void gra::organizacja_ruchem(bool* flaga_partii_mob2,bool* flaga_kierunku_1,bool* flaga_partii_mob3,bool* flaga_kierunku_2,bool* flaga_broni_dod)
{

    int ostatni_typ_1,pierwszy_typ_1,ostatni_typ_2,pierwszy_typ_2;
    bool znaleziony_pierwszy_1=false,znaleziony_pierwszy_2=false;
    for(int i=0; i<wektor_mobow.size(); i++)
    {
        if(wektor_mobow[i]->daj_typ()==1) ostatni_typ_1=i;
        if(wektor_mobow[i]->daj_typ()==2) ostatni_typ_2=i;
        if(wektor_mobow[i]->daj_typ()==1 && znaleziony_pierwszy_1==false)
        {
            pierwszy_typ_1=i;
            znaleziony_pierwszy_1=true;
        }

        if(wektor_mobow[i]->daj_typ()==2 && znaleziony_pierwszy_2==false)
        {
            pierwszy_typ_2=i;
            znaleziony_pierwszy_2=true;
        }


    }

    if(liczba_typ(1)==4) *flaga_partii_mob2=0;             ///flaga partii odpowiada za sprawdzenie czy nalezy
    if(liczba_typ(1)==0) *flaga_partii_mob2=1; ///podeslac kolejna partie mobow w gornym sektorze
    if(liczba_typ(2)==3) *flaga_partii_mob3=0;
    if(liczba_typ(2)==0) *flaga_partii_mob3=1;
    if(liczba_typ(1)!=0 && wektor_mobow[pierwszy_typ_1]->daj_x()<0) *flaga_kierunku_1=1;
    if(liczba_typ(1)!=0 && wektor_mobow[ostatni_typ_1]->daj_x()>936) *flaga_kierunku_1=0;
    if(liczba_typ(2)!=0 && wektor_mobow[ostatni_typ_2]->daj_x()<0) *flaga_kierunku_2=1;
    if(liczba_typ(2)!=0 && wektor_mobow[pierwszy_typ_2]->daj_x()>936) *flaga_kierunku_2=0;
    if(akt_bron_dod_l==NULL && akt_bron_dod_p==NULL) *flaga_broni_dod=false;

}

bool gra::wejscie_bossa(boss* boss1)
{

    if(boss1==NULL) return 1;
    else if(boss1->daj_tryb()==1) return 0;
    else return 1;

}
