#ifndef TRAWA_H_
    #define TRAWA_H_

    #include "roslina.h"

    class Trawa : public Roslina
    {
      private:
            static const char icon = '*';
            static const int sila = 0;
            static const int inicjatywa = 0;
            static const int TRAWA_SPREAD_CHANCE = 82;
            const std::string nazwa = "Trawa";


      public:
            Trawa(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Roslina(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              spread_chance = TRAWA_SPREAD_CHANCE;
            }

            Trawa(int x, int y, Swiat * swiat) : Roslina(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              spread_chance = TRAWA_SPREAD_CHANCE;
            }

            Trawa(Swiat * swiat) : Roslina(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
              spread_chance = TRAWA_SPREAD_CHANCE;
            }

      // Nie ma potrzeby definiowania żadnych wlasnych konstruktorow kopiujacych, destruktorow itp
      // Pamiec jest statyczna


            void kolizja() override
            {

                int prev_x = x;
                int prev_y = y;
                int _timeout = 0;

                do
                {
                  x += (rand() % 3) - 1;
                  y += (rand() % 3) - 1;

                  // w razie wpadniecia w petle nieskonczoną, bo metoda canMove() zadziala zle
                  if (_timeout++ > 100)
                  {
                    x = prev_x;
                    y = prev_y;
                    return;
                  }


                } while (outOfworld(x, y) || (x == prev_x && y == prev_y) || swiat -> isfree(this) != nullptr);


                // Utworzenie nowego organizmu
                new Trawa(this -> x,this -> y,swiat);

                x = prev_x;
                y = prev_y;

            }

            Organizm * kolizja(Organizm * inny) override
            {
                // nigdy nie wykorzystana przy trawie, trawa nie ma specyfikacji przy kolizji z innym organizmem
                return nullptr;
            }
    };

#endif
