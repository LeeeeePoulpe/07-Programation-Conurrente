#ifndef TAMPON_HPP_
#define TAMPON_HPP_

#include "Element.hpp"
#include "EcranManchots.hpp"

class Tampon
{
public :
  Tampon(EcranManchots& ecran_);
  virtual ~Tampon();

  virtual void deposer_element(Element e) = 0;
  virtual Element retirer_element(const unsigned long numcons, const unsigned long nummanchot) = 0;

protected :
  EcranManchots& ecran;
};

#endif // TAMPON_HPP_
