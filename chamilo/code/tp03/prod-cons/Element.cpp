#include <thread>
#include <chrono>

#include "Element.hpp"

using namespace std;
using namespace std::chrono;

Element::Element(const unsigned long num_prod_) :
  num_prod(static_cast<int>(num_prod_)),
  num_cons(0)
{}

void Element::traitement(void)
{
  this_thread::sleep_for(milliseconds(2000+num_cons*500));
}

int Element::getNumProd(void)
{
  return num_prod;
}

int Element::getNumCons(void)
{
  return num_cons;
}

void Element::setNumCons(unsigned long num_cons_)
{
  num_cons=static_cast<int>(num_cons_);
}
