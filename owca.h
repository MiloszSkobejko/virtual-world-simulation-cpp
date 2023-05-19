#ifndef OWCA_H_
    #define OWCA_H_

    #include "zwierze.h"

    class Owca : public Zwierze
    {
      private:
            static const char icon = 'O';
            static const int sila = 4;
            static const int inicjatywa = 4;
            const std::string nazwa = "Owca";


      public:
            Owca(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Owca(char ikona, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Owca(int x, int y, Swiat * swiat) : Zwierze(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
            }

            Owca(Swiat * swiat) : Zwierze(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
            }

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

                std::cout << "Narodzila sie nowa Owca!\n";
                new Owca(this -> x, this -> y, swiat);

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
