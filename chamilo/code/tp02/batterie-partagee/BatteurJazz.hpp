#ifndef BATTEUR_JAZZ_HPP_
#define BATTEUR_JAZZ_HPP_

#include "Batteur.hpp"
#include "Batterie.hpp"

// Classe avec opérateur parenthèses défini
class BatteurJazz : public Batteur
{
public :
  BatteurJazz(const unsigned long numero_, Batterie& batterie_);
  void operator()(void);
};

#endif // BATTEUR_JAZZ_HPP_
