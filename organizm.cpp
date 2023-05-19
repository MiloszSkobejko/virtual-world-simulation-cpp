#include "organizm.h"
#include "WirtualnySwiat.h"



Organizm::Organizm(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat)
{
  this -> wiek = 0;
  this -> ikona = ikona;
  this -> sila = sila;
  this -> inicjatywa = inicjatywa;
  this -> x = x;
  this -> y = y;
  this -> swiat = swiat;

  //Dodawanie do swiata
  this -> swiat -> append(this);
}



Organizm::Organizm(char ikona, int sila, int inicjatywa, Swiat * swiat)
{
  this -> wiek = 0;
  this -> ikona = ikona;
  this -> sila = sila;
  this -> inicjatywa = inicjatywa;
  this -> x = rand() % (swiat -> getXsize() - 3) + 1;
  this -> y = rand() % (swiat -> getYsize() - 3) + 1;
  this -> swiat = swiat;

  //Dodawanie do swiata
  this -> swiat -> append(this);
}



void Organizm::rysowanie()
{
    swiat -> drawEntity(&ikona, x, y);
}



bool Organizm::outOfworld(int new_x, int new_y) const
{
    return (new_x >= swiat -> getXsize() - 1 || new_y >= swiat -> getYsize() - 1 || new_x < 1 || new_y < 1);
}



// Metoda rozmnażania (inna niż move() w zwierze.h, bo zwierze nie sprawdza ws)
bool Organizm::canSpawn(int typOrganizmu)
{

    int prev_x = x;
    int prev_y = y;

    // Iteruj przez wszystkie możliwe zmiany położenia
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            // Nie sprawdzaj tej samej pozycji
            if (i == 0 && j == 0)
                continue;

            // Sprawdź nową lokalizację
            x = prev_x + i;
            y = prev_y + j;

            Organizm * result = swiat -> isfree(this);

            switch (typOrganizmu)
            {
              case roslina_t:
                    if (result == nullptr && !outOfworld(x, y))
                    {
                        // Przywróć poprzednie wartości i zwróć true
                        x = prev_x;
                        y = prev_y;
                        return true;
                    }
                    break;

              case zwierze_t:
                    if ((result == nullptr && !outOfworld(x, y)) || (result != nullptr && result -> getKrolestwo() == roslina_t && !outOfworld(x, y)))
                    {
                        // Przywróć poprzednie wartości i zwróć true
                        x = prev_x;
                        y = prev_y;
                        return true;
                    }
                    break;

              case lis_t:
                    if ((result == nullptr && !outOfworld(x, y)) || (result != nullptr && result -> getSila() < this -> sila && !outOfworld(x, y)))
                    {
                        // Przywróć poprzednie wartości i zwróć true
                        x = prev_x;
                        y = prev_y;
                        return true;
                    }
                    break;
            }
        }
    }

    // Przywróć poprzednie wartości i zwróć false
    x = prev_x;
    y = prev_y;
    return false;
}



bool Organizm::overlap(Organizm * inny)
{
  return (this -> x == inny -> x && this -> y == inny -> y);
}



Organizm * Organizm::walka(Organizm * inny)
{
  // Porownuje 2 organizmy, ktore walczą, zwraca wskaznik na przegrany organizm (aby go usunac)
  if (this -> sila > inny -> sila || (this -> sila == inny -> sila && this -> wiek > inny -> wiek))
    return inny;
  else
    return this;
}



void Organizm::debugInfo() const
{
  std::cout << "[" << *gatunek << "] S: " << sila << " I: " << inicjatywa << " W: " << wiek << "\n";
  // std::cout << "x : " << x << " y : " << y << " mem: " << this << " krolestwo: " << krolestwo << "\n";
}



void Organizm::saveParameters(ostream & os) const
{
  os << *gatunek << "\n";
  os << ikona << "\n";
  os << krolestwo << "\n";
  os << sila << "\n";
  os << inicjatywa << "\n";
  os << x << "\n";
  os << y << "\n";
  os << wiek << "\n";
}
