#ifndef LENIWIEC_H_
    #define LENIWIEC_H_

    #include "zwierze.h"

    class Leniwiec : public Zwierze
    {
      private:
            static const char icon = 'E';
            static const int sila = 2;
            static const int inicjatywa = 1;
            static const int defend = 5;
            const std::string nazwa = "Leniwiec";

            bool lastMove;


      public:
            Leniwiec(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              lastMove = false;
            }

            Leniwiec(char ikona, int x, int y, Swiat * swiat) : Zwierze(ikona, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              lastMove = false;
            }

            Leniwiec(int x, int y, Swiat * swiat) : Zwierze(icon, sila, inicjatywa, x, y, swiat)
            {
              gatunek = &nazwa;
              lastMove = false;
            }

            Leniwiec(Swiat * swiat) : Zwierze(icon, sila, inicjatywa, swiat)
            {
              gatunek = &nazwa;
              lastMove = false;
            }

        // Nie ma potrzeby definiowania żadnych wlasnych konstruktorow kopiujacych, destruktorow itp
        // Pamiec jest statyczna
            void akcja() override
            {

                if (lastMove == false)
                {
                  //std::cout << "Leniwiec przemieszcza sie\n";
                  Zwierze::akcja();
                  lastMove = true;
                }
                else
                {
                  std::cout << "Leniwiec ruszal sie ostatnio, teraz zostaje na swoim miejscu\n";
                  lastMove = false;

                   // Wyswietlanie i starzenie sie
                   this -> rysowanie();
                   wiek++;
                }

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

                std::cout << "Narodzil sie nowy Leniwiec!\n";
                new Zolw(this -> x, this -> y, swiat);

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
