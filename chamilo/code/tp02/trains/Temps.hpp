#ifndef TEMPS_HPP_
#define TEMPS_HPP_

#include "Positions.hpp"

// Classe avec opérateur parenthèses défini
class Temps
{
public :
  Temps(bool& actif_, Positions& positions_);
  void operator()(void);

private :
  bool& actif;
  Positions& positions;
};

#endif // TEMPS_HPP_
