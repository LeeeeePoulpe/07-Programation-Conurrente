#include <curses.h>
#include <mutex>

#include "Ecran.hpp"

using namespace std;

mutex Ecran::m; // construction du mutex partagé entre les éventuels plusieurs écrans partageant le même terminal

Ecran::Ecran(void)
{
  initscr();
  curs_set(0);
  refresh();
}

Ecran::~Ecran(void)
{
  endwin();
}

void Ecran::efface_car(const int x, const int y)
{
  lock_guard<mutex> verrou(m);
  mvaddch(y, x, ' ');
  refresh();
}

void Ecran::affiche_car(const char c, const int x, const int y)
{
  lock_guard<mutex> verrou(m);
  mvaddch(y, x, c);
  refresh();
}

void Ecran::affiche_chaine(const char *s, const int x, const int y)
{
  lock_guard<mutex> verrou(m);
  mvaddstr(y, x, s);
  refresh();
}
