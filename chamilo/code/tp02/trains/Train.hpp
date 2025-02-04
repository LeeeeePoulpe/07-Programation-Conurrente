#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "Trajet.hpp"
#include "Positions.hpp"

// Classe avec opérateur parenthèses défini
class Train
{
public :
  Train(const unsigned long numero_, Positions& positions_);
  void operator()(void);

private :
  const unsigned long numero;
  Trajet& trajet;
  Positions& positions;

};

#endif // TRAIN_HPP_
