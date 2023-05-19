#ifndef WILCZE_JAGODY_H_
    #define WILCZE_JAGODY_H_

    #include "roslina.h"

    class WilczeJagody : public Roslina
    {
      private:
            static const char icon = '^';
            static const int boost = 3;
            static const int sila = 0;
            static const int inicjatywa = 0;
            static const int WILCZEJAG_SPREAD_CHANCE = 98;
            const std::string nazwa = "WilczeJagody";


      public:
            WilczeJagody(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Roslina(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              spread_chance = WILCZEJAG_SPREAD_CHANCE;
            }

            WilczeJagody(int x, int y, Swiat * swiat) : Roslina(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              spread_chance = WILCZEJAG_SPREAD_CHANCE;
            }

            WilczeJagody(Swiat * swiat) : Roslina(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
              spread_chance = WILCZEJAG_SPREAD_CHANCE;
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
                new WilczeJagody(this -> x,this -> y,swiat);

                x = prev_x;
                y = prev_y;

            }



            Organizm * kolizja(Organizm * inny) override
            {
                // Zabija atakujacy organizm

                if (inny == nullptr) return nullptr;

                std::cout << inny -> getGatunek() << " zjadl Wilcze Jagody i zginal\n";
                swiat -> remove(this);

                return inny;
            }
    };

#endif
