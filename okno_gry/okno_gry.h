#include <iostream>
#include <vector>
#include <sstream>
#include "gracz.h"
#include "przeszkoda.h"
#include "mob_type2.h"
#include "pocisk.h"
#include "bron_dod.h"
#include "mob1.h"
#include "mob2.h"
#include "boss.h"
#include "ogien.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

class gra
{

public:

    void gramy();
    gra();
    ~gra();
    bool smierc;
    bool boss_start;
    bool wygrales;
    bool szukaj_x=true;




private:
    sf::RenderWindow oknoAplikacji;
    sf::Texture tekstura1;
    sf::Sprite przeciwnik;
    sf::Texture tekstura2;
    sf::Sprite chmura;
    sf::Texture tekstura3;
    sf::Sprite statek;
    sf::Texture tekstura4;
    sf::Sprite pocisk_s;
    sf::Texture tekstura5;
    sf::Sprite przeciwnik2;
    sf::Texture tekstura6;
    sf::Sprite rakietka;
    sf::Texture tekstura7;
    sf::Sprite fala;
    sf::Texture tekstura8;
    sf::Sprite fala2;
    sf::Texture brazowy_statek;
    sf::Sprite bos;
    sf::Texture kulaognia_l;
    sf::Sprite ogien_l;
    sf::Texture kulaognia_p;
    sf::Sprite ogien_p;
    sf::Font czcionka;
    sf::Text tekst_hp;
    sf::Text tekst_obrazenia;
    sf::Text tekst_fale;
    sf::Text tekst_rakiety;
    sf::Text restart;
    sf::Text wczytaj;
    sf::Text esc;
    sf::Text hp_mob2;
    sf::Text wynik;
    sf::Text wygrana;
    sf::Text liczba_zabitych;
    sf::Clock zegar;
    sf::Clock zegar2;
    sf::Clock zegar3;
    sf::Clock zegar4;
    sf::Time t1;
    sf::Time t2;
    sf::Time t3;
    sf::Time t4;


    void ustawienie_tekstur();
    void stworzenie_przeciwnika(int);
    void ruchy_pociskow_i_przeszkod();
    void losuj_przeszkode();
    void rysowanie(gracz*,boss*);
    void rysowanie_menu();
    void zniszcz_wszystkie(gracz**,boss**);

    void strzal(gracz*);
    void ruchy_mobow2(bool,bool);
    void trafienia(gracz*,boss*);
    int trafienie_w_mob2(double,double,int);
    int trafienie_w_przeszkoda(double,double);
    void likwidacje(gracz*,boss*);
    void strzal_moba();
    void organizacja_ruchem(bool*,bool*,bool*,bool*,bool*);
    void kolizje(gracz*,boss*);
    int liczba_typ(int);
    int trafienie_w_mob_bron_dod(bron_dodatkowa*);
    int trafienie_w_przeszkode_bron_dod(bron_dodatkowa*);
    int losuj_x();
    void sprawdz_bonusy(int*,int*,gracz*);
    mob1* stworz_mob1();
    mob2* stworz_mob2();
    boss* stworz_bossa();
    void tryb2(boss*);
    void tryb5(boss*);
    void obsluga_bossa(boss**,int*);
    void obsluga_rozgrywki(bool*,bool*);
    bool wejscie_bossa(boss*);
    void zapis_do_pliku(gracz*,int,int,bool,bool,bool,bool);
    void wczytaj_gre(gracz**,int*,int*,bool*,bool*,bool*,bool*,boss**);




    int punkty;
    int liczba_zabitych_1;
    int liczba_zabitych_2;
    fstream plikzapisu;
    bool wczyt;


    vector <mob_typ*> wektor_mobow;
    vector <przeszkoda*> wektor_przeszkod;
    vector <pocisk*> wektor_pociskow;
    pocisk* atakujacy;
    pocisk* pierw_pocisk_boss;
    pocisk* akt_pocisk_boss;
    ogien *lewa_bossa;
    ogien *prawa_bossa;
    bron_dodatkowa *akt_bron_dod_l;
    bron_dodatkowa *akt_bron_dod_p;
};
