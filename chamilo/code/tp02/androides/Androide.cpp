#include <iostream>
#include <random>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <sys/syscall.h>

#include "Androide.hpp"
#include "Ecran.hpp"
#include "SequenceEntiere.hpp"

using namespace std;
using namespace std::chrono;

int const Androide::COTE_ESPACE = 20; // l'espace à inspecter est un carré de 20 unités de côté

Androide::Androide(SequenceEntiere& seq_, Ecran& ecran_) :
  numero(0), // valeur arbitraire en attendant le démarrage du thread
  seq(seq_),
  ecran(ecran_)
{}

void Androide::maj_coord(int& coord)
{
  uniform_int_distribution<int> dis(-1,1);
  coord += dis(gen);
}

void Androide::marche_aleatoire(void)
{
  gen = default_random_engine(static_cast<unsigned long>(syscall(SYS_gettid)));
  uniform_int_distribution<int> dis(5,5+COTE_ESPACE);
  int x = 5 + dis(gen);
  int y = 5 + dis(gen);

  for (int i = 0; i < 20; i++)
  {
    ecran.efface_car(x,y);
    maj_coord(x);
    maj_coord(y);
    ecran.affiche_car(static_cast<char>(numero+'0'),x,y);
    this_thread::sleep_for(milliseconds(500));
  }
  ecran.affiche_car('*',x+1,y);
}

void Androide::operator()(void)
{
  // récupération d'un numéro unique parmi 0,1,...
  numero = seq.nouveau_numero();

  // mis en action de l'androïde
  marche_aleatoire();
}
