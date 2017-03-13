
struct Pusty_plik : public exception
{
  const char * what () const throw ()
  {
    return "Plik jest pusty!";
  }
};

struct Blad_otwarcia: public exception
{
    const char * what () const throw ()
  {
    return "Blad otwarcia pliku!";
  }

};
