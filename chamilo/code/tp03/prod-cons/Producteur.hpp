#ifndef PRODUCTEUR_HPP_
#define PRODUCTEUR_HPP_

#include "Tampon.hpp"

// Classe avec opérateur parenthèses défini
class Producteur
{
public :
  Producteur(const unsigned long numero_, const unsigned long nb_elems_, Tampon& tampon_);
  void operator()(void);

private :
  const unsigned long numero;
  const unsigned long nb_elems;
  Tampon& tampon;
};

#endif // PRODUCTEUR_HPP_
