#include <iostream>

#include "TamponSBQ.hpp"
#include "Element.hpp"

using namespace std;

TamponSBQ::TamponSBQ(const unsigned long taille_, EcranManchots& ecran_) :
  Tampon(ecran_)
{
  (void)taille_;
}

void TamponSBQ::deposer_element(Element e)
{
  ecran.dessiner_creer_manchot(e);
  ecran.dessiner_deposer_manchot(e);
}

Element TamponSBQ::retirer_element(const unsigned long numcons, const unsigned long nummanchot)
{
  ecran.dessiner_demander_manchot(static_cast<int>(numcons),static_cast<int>(nummanchot));
  Element e;
  e.setNumCons(numcons);
  ecran.dessiner_retirer_manchot(e,static_cast<int>(nummanchot));
  return e;
}
