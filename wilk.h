#ifndef WILK_H_
    #define WILK_H_

    #include "zwierze.h"

    class Wilk : public Zwierze
    {
      private:
            static const char icon = 'W';
            static const int sila = 9;
            static const int inicjatywa = 5;
            const std::string nazwa = "Wilk";


      public:
            Wilk(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Wilk(char ikona, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Wilk(int x, int y, Swiat * swiat) : Zwierze(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Wilk(Swiat * swiat) : Zwierze(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
            }

      // Wilk nie ma specyfikacji metody akcja(), dlatego nie jest tu nadpisana

      // Nie ma potrzeby definiowania żadnych wlasnych konstruktorow kopiujacych, destruktorow itp
      // Pamiec jest statyczna


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

                std::cout << "Narodzil sie nowy Wilk! (x: " <<  this -> x << " y: " << this -> y << ")\n";
                new Wilk(this -> x, this -> y, swiat);

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
