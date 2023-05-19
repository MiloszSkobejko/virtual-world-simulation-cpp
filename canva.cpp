#include "canva.h"
#include <iostream>

using std::cout;
using std::endl;

/*************************** KONSTRUKTOR ZWYKŁY ********************************/
Canvas::Canvas(int s_x, int s_y, char bg, char brd)
{

  // Aby nie utworzyc planszy za duzej lub z ujemnych wartosci
  if (s_x <= 1 || s_y <= 1 || s_x > MAX_CANVA_SIZE || s_y > MAX_CANVA_SIZE)
  {
    s_x = DEFAULT_CANVA_SIZE;
    s_y = DEFAULT_CANVA_SIZE;
  }

  this -> size_x = s_x;
  this -> size_y = s_y;
  this -> background = bg;
  this -> border = brd;


  // Utworzenie Canvy
  canva = new char * [s_x];

  for (int i = 0; i < s_x; i++)
    canva[i] = new char[s_y];

  // Wypełnianie wartosciami
  fillEmpty();
}



/************************** KONSTRUKTOR DOMYŚLNY *******************************/
Canvas::Canvas()
{
  this -> size_x = DEFAULT_CANVA_SIZE;
  this -> size_y = DEFAULT_CANVA_SIZE;
  this -> background = ' ';
  this -> border = '#';
  
  // Utworzenie Canvy
  canva = new char * [DEFAULT_CANVA_SIZE];

  for (int i = 0; i < DEFAULT_CANVA_SIZE; i++)
    canva[i] = new char[DEFAULT_CANVA_SIZE];

  // Wypełnianie wartosciami pustego plotna
  fillEmpty();
}



/************************** KONSTRUKTOR KOPIUJĄCY ******************************/
Canvas::Canvas(const Canvas &original)
{
  canva = new char * [original.size_x];

  for (int i = 0; i < original.size_x; i++)
    canva[i] = new char[original.size_y];

  this -> size_x = original.size_x;
  this -> size_y = original.size_y;
  this -> background = original.background;
  this -> border = original.border;

  for (int y = 0; y < this -> size_y; y++)
    for (int x = 0; x < this -> size_x; x++)
      canva[x][y] = original.canva[x][y];
}



/******************************** DESTRUKTOR ***********************************/
Canvas::~Canvas()
{
  delete [] canva;
}



/************************** WYPEŁNIANIE WAROŚCIAMI *****************************/
void Canvas::fillEmpty()
{
  // Wypełnienie wartosciami
  for (int y = 0; y < this -> size_y; y++) {
    for (int x = 0; x < this -> size_x; x++) {

      if (x == 0 || x == this -> size_x - 1 || y == 0 || y == this -> size_y - 1)
        canva[x][y] = this -> border; /* Inny znak na ramkę */
      else
        canva[x][y] = this -> background;
    }
  }
}



/******************************* WYŚWIETLANIE **********************************/
void Canvas::print(ostream & out) const
{
  for (int y = 0; y < this -> size_y; y++)
  {
    for (int x = 0; x < this -> size_x; x++)
      out << canva[x][y];

    out << '\n';
  }
}



/************************** CZYSZCZENIE KONSOLI ********************************/
void Canvas::ClearConsoleScreen() /* UWAGA, METODA STATYCZNA */
{
  system("cls");
}
