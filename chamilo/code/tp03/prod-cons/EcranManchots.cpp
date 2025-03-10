#include <curses.h>
#include <mutex>
#include <thread>
#include <chrono>

#include "EcranManchots.hpp"
#include "Element.hpp"

using namespace std;
using namespace std::chrono;

static const int cote_x = 7;
static const int cote_y = 5;

static const int origine_x = 5;
static const int origine_y = 5;

// tempo pour que l'on ait du temps pour voir les manchots
// dans le tampon avant d'être immédiatement consommés
static const duration<double> tempo(milliseconds(200));

static void dessiner_tete_ecriture(const int num_case)
{
  mvaddch(origine_y+num_case*cote_y+static_cast<int>(0.5*(1+cote_y)),
          origine_x+3*cote_x-1,'>');
  refresh();
}

static void effacer_tete_ecriture(const int num_case)
{
  mvaddch(origine_y+num_case*cote_y+static_cast<int>(0.5*(1+cote_y)),
          origine_x+3*cote_x-1,' ');
  refresh();
}

static void dessiner_tete_lecture(const int num_case)
{
  mvaddch(origine_y+num_case*cote_y+static_cast<int>(0.5*(1+cote_y)),
          origine_x+4*cote_x+1,'<');
  refresh();
}

static void effacer_tete_lecture(const int num_case)
{
  mvaddch(origine_y+num_case*cote_y+static_cast<int>(0.5*(1+cote_y)),
          origine_x+4*cote_x+1,' ');
  refresh();
}

static void dessiner_case(const int x, const int y)
{
  mvaddch(y,x,'+');
  mvaddch(y+cote_y,x,'+');
  mvaddch(y+cote_y,x+cote_x,'+');
  mvaddch(y,x+cote_x,'+');
  mvhline(y,x+1,'-',cote_x-1);
  mvhline(y+cote_y,x+1,'-',cote_x-1);
  mvvline(y+1,x,'|',cote_y-1);
  mvvline(y+1,x+cote_x,'|',cote_y-1);
}

static void dessiner_fond(const unsigned long nb_prod,
                          const unsigned long taille,
                          const unsigned long nb_cons,
                          const unsigned long famille)
{
  int x = origine_x;
  int y = origine_y;

  mvaddstr(y-1,x-1,"Producteurs");
  for (int i=0; i<static_cast<int>(nb_prod); i++)
  {
    attron(COLOR_PAIR(i+2));
    dessiner_case(x,y+i*(1+cote_y)+1);
    attroff(COLOR_PAIR(i+2));
  }

  x+=3*cote_x;
  mvaddstr(y-1,x,"Tampon");
  for (int i=0; i<static_cast<int>(taille); i++)
    dessiner_case(x,y+i*cote_y+1);

  dessiner_tete_ecriture(0);
  dessiner_tete_lecture(0);

  x+=3*cote_x;
  mvaddstr(y-1,x+1,"Consommateurs");
  for (int i=0; i<static_cast<int>(nb_cons); i++)
    for (int j=0; j<static_cast<int>(famille); j++)
      dessiner_case(x+j*cote_x+1,y+i*(1+cote_y)+1);
}

EcranManchots::EcranManchots(const unsigned long nb_prod,
                             const unsigned long taille_,
                             const unsigned long nb_cons,
                             const unsigned long famille) :
  taille(static_cast<int>(taille_)),
  tete_ecriture(0),
  tete_lecture(0)
{
  short f,b;
  initscr();
  start_color();
  assume_default_colors(COLOR_BLACK,COLOR_WHITE);
  pair_content(0,&f,&b);
  for (int i=0; i<static_cast<int>(nb_prod)+1; i++)
    init_pair(static_cast<short>(1+i),1+i%6,b);
  curs_set(0);
  dessiner_fond(nb_prod,taille_,nb_cons,famille);
  refresh();
}

EcranManchots::~EcranManchots(void)
{
  endwin();
}

static void dessiner_manchot(const int x, const int y, const short couleur)
{
  attron(COLOR_PAIR(couleur));
  mvaddstr(y,x,  "(o_");
  mvaddstr(y+1,x,"(/)_");
  attroff(COLOR_PAIR(couleur));
  refresh();
}

static void dessiner_manchot_absent(const int x, const int y, const short couleur)
{
  if (couleur) attron(COLOR_PAIR(couleur));
  mvaddch(y,x+1,  '?');
  if (couleur) attroff(COLOR_PAIR(couleur));
  refresh();
}

static void effacer_manchot(const int x, const int y)
{
  mvaddstr(y,x,  "   ");
  mvaddstr(y+1,x,"    ");
  refresh();
}

void EcranManchots::dessiner_creer_manchot(Element& e)
{
  lock_guard<mutex> verrou(m);
  dessiner_manchot(origine_x+2,origine_y+(e.getNumProd()-1)*(1+cote_y)+3,static_cast<short>(e.getNumProd()+1));
  this_thread::sleep_for(tempo);
}

void EcranManchots::dessiner_demander_manchot(const int numcons, const int nummanchot)
{
  lock_guard<mutex> verrou(m);
  dessiner_manchot_absent(origine_x+(6+nummanchot)*cote_x+3,numcons*(1+cote_y)+2,0);
  this_thread::sleep_for(tempo);
}

void EcranManchots::dessiner_deposer_manchot(Element& e)
{
  lock_guard<mutex> verrou(m);
  effacer_manchot(origine_x+2,origine_y+(e.getNumProd()-1)*(1+cote_y)+3);

  dessiner_manchot(origine_x+3*cote_x+2,
                   origine_y+tete_ecriture*cote_y+3,static_cast<short>(e.getNumProd()+1));

  // avance la tête d'écriture de façon circulaire
  effacer_tete_ecriture(tete_ecriture);
  tete_ecriture=(tete_ecriture+1)%taille;
  dessiner_tete_ecriture(tete_ecriture);

  this_thread::sleep_for(tempo);
}

void EcranManchots::dessiner_retirer_manchot(Element& e, const int nummanchot)
{
  lock_guard<mutex> verrou(m);
  effacer_manchot(origine_x+3*cote_x+2,
                  origine_y+tete_lecture*cote_y+3);

  dessiner_manchot(origine_x+(6+nummanchot)*cote_x+3,
                          e.getNumCons()*(1+cote_y)+2,static_cast<short>(e.getNumProd()+1));

  // avance la tête de lecture de façon circulaire
  effacer_tete_lecture(tete_lecture);
  tete_lecture=(tete_lecture+1)%taille;
  dessiner_tete_lecture(tete_lecture);

  this_thread::sleep_for(tempo);
}
