#ifndef ROSLINA_H_
      #define ROSLINA_H_

      #include "organizm.h"
      #include <time.h>
      #include <iostream>

      class Roslina : public Organizm
      {

        protected:
              // Szansa na zasianie kolejnej rosliny obok, u mnie taka sama dla każdej roslinki
              int spread_chance;

              Roslina(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat)
              : Organizm(ikona, sila, inicjatywa, x, y, swiat)
              {
                krolestwo = roslina_t;
              }

              Roslina(char ikona, int sila, int inicjatywa, Swiat * swiat)
              : Organizm(ikona, sila, inicjatywa, swiat)
              {
                krolestwo = roslina_t;
              }


        public:
              void akcja()
              {
                if (wiek == 0 && swiat -> getTura() > 1)
                {
                  wiek++;
                  this -> rysowanie();
                  return;
                }

                //std::cout << *gatunek << " probuje sie rozprzestrzenic:\n";

                // Rozprzestrzenianie sie rosliny w metodzie kolizja()
                if ((rand() % 100) > spread_chance && canSpawn(roslina_t))
                  kolizja();
                //else
                  //std::cout << "proba nieudana\n";


                this -> rysowanie();
                wiek++;
                return;
              }


              virtual void kolizja() = 0;
              virtual Organizm * kolizja(Organizm * inny) = 0;
      };


#endif
