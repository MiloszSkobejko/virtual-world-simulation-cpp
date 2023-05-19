#include <iostream>
#include "WirtualnySwiat.h"
#include "wilk.h"
#include "owca.h"
#include "trawa.h"
#include "lis.h"
#include "guarana.h"
#include "wilcze_jagody.h"
#include "zolw.h"
#include "leniwiec.h"

// Dodac do sciezki canva.cpp, WirtualnySwiat.cpp organizm.cpp

/*
      SYMULATOR ŚWIATA WIRTUALNEGO
        Miłosz Skobejko 187224
*/

int main (void)
{
  {

      Swiat * Ziemia = new Swiat(40,20,' ', '#');

      char option = 'o';

      while (option != 'x')
      {

        Ziemia -> wykonajTure();
        option = getchar();

        switch (option)
        {
          case 's':
            /* ZAPISZ SWIAT DO PLIKU */
              getchar();

              try
              {
                Ziemia -> save();
                std::cout << "Pomyslnie zapisano plik!" << std::endl;
                Canvas::clear_buffer();
              }
              catch (const char *error)
              {
                std::cout << error << std::endl;
                Canvas::clear_buffer();
              }
              break;


          case 'l':
            /* WCZYTAJ SWIAT Z PLIKU */
              getchar();

              try
              {
                Ziemia -> load();
                std::cout << "Pomyslnie wczytano plik!" << std::endl;
                Canvas::clear_buffer();
              }
              catch (const char *error)
              {
                std::cout << error << std::endl;
                Canvas::clear_buffer();
              }
              break;


          case 'x':
              getchar();
              std::cout << "Konczenie programu\n";
              Canvas::clear_buffer();
              break;


          case '\n':
              break;


          default:
              getchar();

        }
      }

      delete Ziemia;
  }




  return 0;
}
