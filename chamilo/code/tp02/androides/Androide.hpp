#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_

#include <random>
#include "SequenceEntiere.hpp"
#include "Ecran.hpp"

// Classe avec opérateur parenthèses défini
class Androide
{
public :
  Androide(SequenceEntiere& seq_, Ecran& ecran_);
  void operator()(void);

private :
  unsigned long numero;
  SequenceEntiere& seq;
  Ecran& ecran;
  std::default_random_engine gen;  // générateur aléatoire

  static int const COTE_ESPACE; // l'espace à inspecter est un carré de COTE_ESPACE unités de côté

  void maj_coord(int& coord);
  void marche_aleatoire(void);
};

#endif // MONTHREAD_HPP_
