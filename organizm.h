#ifndef ORGANIZM_H_
    #define ORGANIZM_H_

    #include <iostream>

    using std::ostream;

    class Swiat;

    class Organizm
    {
        protected:

              enum {zwierze_t = 0, roslina_t = 1, lis_t = 2,};

              char ikona;
              const std::string * gatunek;
              int krolestwo;

              int sila;
              int inicjatywa;
              int x;  //polozenie x na canvie
              int y;  //polozenie y na canvie
              int wiek;

              Swiat * swiat;

              Organizm(char ikona, int sila, int inicjatywa, int x, int y, Swiat * swiat);
              Organizm(char ikona, int sila, int inicjatywa, Swiat * swiat);

              bool outOfworld(int new_x, int new_y) const;

              virtual void rysowanie();

              // Metoda rozmnażania (inna niż move() w zwierze.h, bo zwierze nie sprawdza ws)
              bool canSpawn(int typOrganizmu);

      public:

              virtual void akcja() = 0;
              virtual void kolizja() = 0;
              virtual Organizm * kolizja(Organizm * inny) = 0;

              bool overlap(Organizm * inny);
              Organizm * walka(Organizm * inny);
              void debugInfo() const;
              void saveParameters(ostream & os) const;

              const std::string getGatunek() const {return *gatunek;}
              int getInicjatywa() const {return inicjatywa;}
              int getSila() const {return sila;}
              int getKrolestwo() const {return krolestwo;}
              void ZwiekszSile(const int value)  {sila += value;};
    };

#endif
