#ifndef WIRTUALNY_SWIAT_H_
      #define WIRTUALNY_SWIAT_H_

      #include "canva.h"
      #include <vector>
      #include <fstream>

      using std::ostream;
      using std::ofstream;

      class Organizm;

      class Swiat : public Canvas
      {
        private:

              int iloscOrganizmow;
              int tura;
              std::vector<Organizm*> organizmy;

              void rysujSwiat(ostream & out = std::cout) const;
              void sortujOrganizmy();

        public:
              Swiat(int size_x, int size_y, char background, char border);
              Swiat();
              Swiat(const Swiat&);

               ~Swiat();

              bool wykonajTure();
              void drawEntity(char * icon, int x, int y);
              bool append(Organizm * nastepnyOrganizm);
              bool remove(Organizm * ten_organizm);
              Organizm * isfree(Organizm * organizm);
              void _toFile(ostream & os);
              bool save();
              bool load();

              int getXsize() {return size_x;}
              int getYsize() {return size_y;}
              int getTura() {return tura;}
      };

#endif
