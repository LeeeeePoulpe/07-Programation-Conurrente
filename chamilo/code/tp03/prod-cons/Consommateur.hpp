#ifndef CONSOMMATEUR_HPP_
#define CONSOMMATEUR_HPP_

#include "Tampon.hpp"

// Classe avec opérateur parenthèses défini
class Consommateur
{
public :
  Consommateur(const unsigned long numero_, const unsigned long nb_elems_, Tampon& tampon_);
  void operator()(void);

private :
  const unsigned long numero;
  const unsigned long nb_elems;
  Tampon& tampon;
};

#endif // CONSOMMATEUR_HPP_
