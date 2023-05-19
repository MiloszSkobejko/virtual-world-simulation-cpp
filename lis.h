#ifndef LIS_H_
    #define LIS_H_

    #include "zwierze.h"

    class Lis : public Zwierze
    {
      private:
            static const char icon = 'L';
            static const int sila = 3;
            static const int inicjatywa = 7;
            const std::string nazwa = "Lis";


      public:
            Lis(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Lis(char ikona, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Lis(int x, int y, Swiat * swiat) : Zwierze(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Lis(Swiat * swiat) : Zwierze(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
            }

        // Nie ma potrzeby definiowania żadnych wlasnych konstruktorow kopiujacych, destruktorow itp
        // Pamiec jest statyczna
            void akcja() override
            {
              int prev_x = x;
              int prev_y = y;
              int _timeout = 0;

              Organizm * result;

              std::cout << "Lis przemyka w krzakach\n";

              // Specyfikacja lisa, nie ruszy sie na pole, na ktorym jest silniejszy organizm. (prawie nigdy)
              do {

                if (_timeout > 0)
                  std::cout << "Lis wyczul zagrozenie! Zmiana kierunku.\n";


                int move_x;
                int move_y;

                do
                {
                  move_x = (rand() % 3) - 1;
                  move_y = (rand() % 3) - 1;

                } while(outOfworld(x + move_x, y + move_y));

                x += move_x;
                y += move_y;

                result = swiat -> isfree(this);

                // w razie wpadniecia w petle nieskonczoną, bo metoda canSpawn() zadziala zle
                if (_timeout++ > 200)
                {
                  x = prev_x;
                  y = prev_y;
                  wiek++;

                  std::cout << "ERROR NIESK-PETLA LIS.\n";
                  return;
                }

              } while((result != nullptr && result -> getSila() > sila) && canSpawn(lis_t));


              result = swiat -> isfree(this);

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

                std::cout << "Narodzil sie nowy Lisek!\n";
                new Lis(this -> x, this -> y, swiat);

                x = prev_x;
                y = prev_y;
          }



          Organizm * kolizja(Organizm * inny) override
          {

            // Nie ma specyfikacji
            return nullptr;
          }
    };

#endif
