#ifndef ZOLW_H_
    #define ZOLW_H_

    #include "zwierze.h"

    class Zolw : public Zwierze
    {
      private:
            static const char icon = 'Z';
            static const int sila = 2;
            static const int inicjatywa = 1;
            static const int CHANCE_TO_STAY = 75;
            static const int defend = 5;
            const std::string nazwa = "Zolw";


      public:
            Zolw(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Zolw(char ikona, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Zolw(int x, int y, Swiat * swiat) : Zwierze(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Zolw(Swiat * swiat) : Zwierze(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
            }

        // Nie ma potrzeby definiowania żadnych wlasnych konstruktorow kopiujacych, destruktorow itp
        // Pamiec jest statyczna
            void akcja() override
            {

                if (rand() % 100 > CHANCE_TO_STAY)
                {
                  std::cout << "Zolw postanowil sie ruszyc\n";

                  int prev_x = x;
                  int prev_y = y;

                  move();

                  // Sprawdzanie, czy pole na ktore ma sie ruszyc organizm jest wolne, zajete przez
                  // ten sam gatunek, czy zajete przez inny.

                  Organizm * result = swiat -> isfree(this);


                  // Pole jest zajety przez ten sam gatunek i dochodzi (XD) do rozmnażania
                  if (result == this && wiek > 10)
                  {
                    x = prev_x;
                    y = prev_y;

                    if (canSpawn(zwierze_t))
                      kolizja();
                    else
                      std::cout << "Male zwierze " << *gatunek << " nie moze przyjsc na swiat. Za malo miejsca!\n";
                  }


                  // Pole jest zajety przez inny gatunek i dochodzi do walki
                  // Atakakujacym jest zawsze organizm wywolujacy funkcje walka().
                  // Czyli ten ktora ma aktualnie ruch
                  if (result != nullptr && result != this)
                  {

                        Organizm * temp = result -> kolizja(this);


                      // Jesli walka zwroci this to organizm przegral i musi sie usunac (przegrywa tez z wilczymi jagodami)
                      // temp zawiera wynik metody kolizja(Organizm *), w zaleznosci od kombinacji wykonuje sie jedna z ponizszych
                      // opcji: walka(z innym) konczy sie porazka lub kolizja() z innym organizmem konczy sie porazka = usuniecie siebie
                      // kolizja() == inny organizm, znaczy, ze ten organizm odparl atak i nie zostanie usuniety. kolizja() == null znaczy,
                      // ze drugi organizm przegral
                      if (walka(result) == this || temp == this)
                      {
                          std::cout << result -> getGatunek() << " zjadl " << this -> getGatunek() << "\n";

                          swiat -> remove(this);
                          return;
                      }
                      else if (temp == result)
                      {
                          // Atak sie nie udal, wracanie na poprzednia pozycje
                          std::cout << result -> getGatunek() << " odparl atak " << this -> getGatunek() << "\n";
                          x = prev_x;
                          y = prev_y;
                      }
                      else
                      {
                          // Tutaj 2 organizm (*result) przegral
                          swiat -> remove(result);
                          std::cout << this -> getGatunek() << " zjadl " << result -> getGatunek() << "\n";
                      }
                  }
                }
                else
                {
                  std::cout << "zolw nigdzie sie nie rusza\n";
                }


                // Wyswietlanie i starzenie sie
                this -> rysowanie();
                wiek++;
                return;
            }



            void kolizja() override
            {

                int prev_x = x;
                int prev_y = y;
                int _timeout = 0;

                Organizm * result;

                do
                {
                  result = swiat -> isfree(this);

                  x += (rand() % 3) - 1;
                  y += (rand() % 3) - 1;

                  // w razie wpadniecia w petle nieskonczoną, bo metoda canSpawn() zadziala zle
                  if (_timeout++ > 200)
                  {
                    x = prev_x;
                    y = prev_y;
                    return;
                  }

                } while (outOfworld(x, y) || (x == prev_x && y == prev_y) || (result != nullptr && result -> getKrolestwo() == zwierze_t));

                std::cout << "Narodzil sie nowy Zolw!\n";
                new Zolw(this -> x, this -> y, swiat);

                x = prev_x;
                y = prev_y;
          }



          Organizm * kolizja(Organizm * inny) override
          {

            // Odpiera atak organizmow o sile < defend (domyslnie 5)

            if (inny -> getSila() < defend)
              return this;
            return nullptr;
          }
    };

#endif
