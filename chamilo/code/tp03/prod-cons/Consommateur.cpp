#include "Consommateur.hpp"
#include "Tampon.hpp"

Consommateur::Consommateur(const unsigned long numero_,
                           const unsigned long nb_elems_,
                           Tampon& tampon_) :
  numero(numero_),
  nb_elems(nb_elems_),
  tampon(tampon_)
{}

void Consommateur::operator()(void)
{
  for (unsigned long i=0; i<nb_elems; i++)
    tampon.retirer_element(numero,i).traitement();
}
