#ifndef CONSOLECANVA_
      #define CONSOLECANVA_

      #include <iostream>
      #include <stdlib.h>

      using std::ostream;

      class Canvas
      {

      protected:
              static const int DEFAULT_CANVA_SIZE = 20;
              static const int MAX_CANVA_SIZE = 120;

              int size_x;
              int size_y;
              char background;
              char border;
              char ** canva;

              void fillEmpty();


      public:
              /*********** STATYCZNE ***********/
              static void ClearConsoleScreen();
              static inline void clear_buffer(void)
              {
                while (std::cin.get() != '\n');
              }

              /************* KONSTR ************/
              //konstruktory zwykłe
              Canvas(int size_x, int size_y, char background, char border);
              Canvas();

              //konstruktor kopiujący
              Canvas(const Canvas &);

              //destruktor
              virtual ~Canvas(void);

              /************ METODY *************/
              virtual void print(ostream & out = std::cout) const;
      };

#endif
