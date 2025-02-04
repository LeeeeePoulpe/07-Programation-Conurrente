#ifndef BATTEUR_HPP_
#define BATTEUR_HPP_

#include "Batterie.hpp"

// Classe de base avec données communes aux différents types de batteurs
class Batteur
{
public :
  Batteur(const unsigned long numero_, Batterie& batterie_);

protected :
  const unsigned long numero;
  Batterie& batterie;

  static unsigned long const NB_FRAPPES = 1000000;
};

#endif // BATTEUR_HPP_
