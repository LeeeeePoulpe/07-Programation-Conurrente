#ifndef ANDROIDE_HPP_
#define ANDROIDE_HPP_

#include <random>
#include "Ecran.hpp"

// Classe avec opérateur parenthèses défini
class Androide
{
public :
  //--TODO-- à remplacer et compléter --TODO--/
  Androide(Ecran& ecran_);
  //-----------------------------/

public :
  static int const COTE_ESPACE; // l'espace à inspecter est un carré de COTE_ESPACE unités de côté

private :
  //--TODO-- à compléter --TODO--/
  //-----------------------------/
  Ecran& ecran;
  std::default_random_engine gen;  // générateur aléatoire

  void maj_coord(int& coord);
  void marche_aleatoire(void);
};

#endif // ANDROIDE_HPP_
