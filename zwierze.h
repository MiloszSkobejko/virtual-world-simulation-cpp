#ifndef ZWIERZE_H_
      #define ZWIERZE_H_

      #include "organizm.h"
      #include <time.h>
      #include <iostream>

      class Zwierze : public Organizm
      {
        protected:
            void move()
            {

              int move_x;
              int move_y;

              do
              {
                move_x = (rand() % 3) - 1;
                move_y = (rand() % 3) - 1;

              } while (outOfworld(x + move_x, y + move_y) || (move_x == 0 && move_y == 0));


              x += move_x;
              y += move_y;
            }

            Zwierze(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat)
            : Organizm(ikona, sila, inicjatywa, x, y, swiat)
            {
              krolestwo = zwierze_t;
            }

            Zwierze(char ikona, int sila, int inicjatywa, Swiat * swiat)
            : Organizm(ikona, sila, inicjatywa, swiat)
            {
              krolestwo = zwierze_t;
            }


      public:
            virtual void akcja()
            {
              std::cout << *gatunek << " przemieszcza sie\n";

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


              // Wyswietlanie i starzenie sie
              this -> rysowanie();
              wiek++;
              return;
            }


            virtual void kolizja() = 0;
            virtual Organizm * kolizja(Organizm * inny) = 0;
      };


#endif
