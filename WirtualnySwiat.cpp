#include "WirtualnySwiat.h"
#include "organizm.h"
#include "wilk.h"
#include "owca.h"
#include "trawa.h"
#include "lis.h"
#include "guarana.h"
#include "wilcze_jagody.h"
#include "zolw.h"
#include "leniwiec.h"

using std::cout;
using std::copy;
using std::ofstream;
using std::ifstream;


Swiat::Swiat(int size_x, int size_y, char background, char border)
: Canvas(size_x, size_y, background, border)
{
  srand (time(NULL));

  tura = 0;
  iloscOrganizmow = 0;

  new Wilk(this);
  new Wilk(this);
  new Wilk(this);
  new Wilk(this);
  // new Owca(this);
  // new Owca(this);
  //
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);
  new Zolw(this);

  new Lis(this);
  new Lis(this);
  new Lis(this);
  new Lis(this);
  new Lis(this);
  // new Leniwiec(this);
  // new Leniwiec(this);
  // new Leniwiec(this);
  //
  //new Trawa(this);
  // new Trawa(this);
  // new Trawa(this);
  // new Trawa(this);

  // new WilczeJagody(this);
  // new WilczeJagody(this);

  // new Guarana(this);
  // new Guarana(this);
  // new Guarana(this);
  // new Guarana(this);
  // new Guarana(this);

}



Swiat::Swiat() : Canvas()
{
  srand (time(NULL));

  tura = 0;
  iloscOrganizmow = 0;
}



Swiat::~Swiat()
{
  for (Organizm * organizm : organizmy)
    delete organizm;
}



Swiat::Swiat(const Swiat& original)
{
  organizmy = original.organizmy;
  iloscOrganizmow = original.iloscOrganizmow;
  tura = original.tura;
}



void Swiat::rysujSwiat(ostream & out) const
{

  this -> Canvas::print();

  std::cout << "tura: " << tura << " ilosc organizmow: " << iloscOrganizmow << std::endl;

  /* DEBUG INFO */
  // for (int i = 0; i < iloscOrganizmow; i++)
  // {
  //   std::cout << i << " ";
  //   organizmy[i] -> debugInfo();
  // }

}



bool Swiat::append(Organizm * nastepnyOrganizm)
{
  if (nastepnyOrganizm == nullptr) return false;

    organizmy.push_back(nastepnyOrganizm);
    iloscOrganizmow++;

   return true;
}



bool Swiat::remove(Organizm * ten_organizm)
{
    if (ten_organizm == nullptr)
      return false;

    iloscOrganizmow--;

    for (auto i = organizmy.begin(); i != organizmy.end(); i++)
    {
       if (*i == ten_organizm)
       {
           delete *i;
           organizmy.erase(i);
           return true;
       }
    }

    return true;
}




void Swiat::drawEntity(char * icon, int x, int y)
{
  if (x >= size_x - 1 || y >= size_y - 1 || x < 1 || y < 1)
    return;

  canva[x][y] = *icon;
}



Organizm * Swiat::isfree(Organizm * organizm)
{
  for (int i = 0; i < iloscOrganizmow; i++)
  {

     // Sprawdzanie, czy na polu na ktorym ma stanac organizm, jest juz jakis organizm
     if (organizm -> overlap(organizmy[i]) && (organizmy[i] != organizm))
     {

     // Organizmy są tego samego gatunku,zwraca "siebie"
        if (organizm -> getGatunek() == organizmy[i] -> getGatunek())
          return organizm;

     // Organizmy nie są tego samego gatunku, nastepuje walka
        return organizmy[i];
     }
  }

  // Pole jest zupełnie puste
  return nullptr;
}



bool Swiat::wykonajTure()
{

  sortujOrganizmy();

  tura++;
  Canvas::ClearConsoleScreen();
  fillEmpty();

  for (int i = 0; i < iloscOrganizmow; i++)
  {
    organizmy[i] -> akcja();
  }

  rysujSwiat();
  return true;
}



void Swiat::sortujOrganizmy()
{

  for (size_t i = 0; i < organizmy.size(); i++)
  {

    bool swapped = false;

    // Loop through the vector up to the i-th element
    for (size_t j = 0; j < organizmy.size() - i - 1; j++)
    {
      if (organizmy[j] -> getInicjatywa() < organizmy[j + 1] -> getInicjatywa())
      {
        std::swap(organizmy[j], organizmy[j + 1]);
        swapped = true;
      }
    }


    if (!swapped)
      break;

  }
}



bool Swiat::save()
{
  ofstream saving;

  //tworzy nowy plik textowy o tej nazwie, a jak juz jest to go czysci
  saving.open("worldsave.txt");

  if (!saving.is_open())
  {
      throw "Nie mozna zapisac pliku!\n";
  }

  _toFile(saving);

  saving.close();
  return true;
}



void Swiat::_toFile(ostream & os)
{
  /* DANE ŚWIATA */
  os << "Zapis swiata\n";
  os << iloscOrganizmow << "\n";
  os << tura << "\n\n";


  for (int i = 0; i < iloscOrganizmow; i++)
  {
      os << "[organizm " << i << "]\n";
      organizmy[i] -> saveParameters(os);
      os << "\n";
  }
}



bool Swiat::load()
{
    ifstream saving;

    saving.open("worldsave.txt");

    if (!saving.is_open())
    {
        throw "Nie mozna odnalezc pliku!";
    }



    /* KASOWANIE WSZYSTKICH ORGANIZMOW ZE SWIATA */
    for (Organizm * organizm : organizmy)
      remove(organizm);

    organizmy.clear();



    // OD TEGO MOMENTU "saving >> " dziala jak cin.

    // Pomijanie napisu "Zapis swiata"
    while (saving.get() != '\n');

    int iloscOrgWpliku;
    saving >> iloscOrgWpliku;  // ilosc organizmow w pliku. Nie przypisuje do zmiennej this, bo przy tworzeniu nowych organizmow updatuje sie sama
    saving >> tura;


    for (int i = 0; i < iloscOrgWpliku; i++)
    {
      std::string tempGatunek;
      char ikona;
      int sila, inicjatywa, x, y, wiek;

      saving.get();
      saving.get();
      while (saving.get() != '\n');

      saving >> tempGatunek;
      saving >> ikona;

      while (saving.get() != '\n');
      saving.get();

      saving >> sila;
      saving >> inicjatywa;
      saving >> x;
      saving >> y;
      saving >> wiek;

      if (tempGatunek == "Wilk")
      {
        new Wilk(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Owca")
      {
        new Owca(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Lis")
      {
        new Lis(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Trawa")
      {
        new Trawa(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Guarana")
      {
        new Guarana(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "WilczeJagody")
      {
        new WilczeJagody(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Zolw")
      {
        new Zolw(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      if (tempGatunek == "Leniwiec")
      {
        new Leniwiec(ikona, sila, inicjatywa, x, y, this);
        continue;
      }

      //return false;
      if (saving.eof())
        break;

    }


    if (saving.eof())
      cout << "koniec pliku zapisu\n";
    else if (saving.fail())
      throw "Plik uszkodzony\n";

    Canvas::ClearConsoleScreen();
    rysujSwiat();


    saving.close();
    return true;
}
