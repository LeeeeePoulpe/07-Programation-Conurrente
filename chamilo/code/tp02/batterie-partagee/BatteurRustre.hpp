#ifndef BATTEUR_RUSTRE_HPP_
#define BATTEUR_RUSTRE_HPP_

#include "Batteur.hpp"
#include "Batterie.hpp"

// Classe avec opérateur parenthèses défini
class BatteurRustre : public Batteur
{
public :
  BatteurRustre(const unsigned long numero_, Batterie& batterie_);
  void operator()(void);
};

#endif // BATTEUR_RUSTRE_HPP_
