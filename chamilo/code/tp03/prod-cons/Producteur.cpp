#include <thread>
#include <chrono>

#include "Producteur.hpp"
#include "Tampon.hpp"

using namespace std;
using namespace std::chrono;

Producteur::Producteur(const unsigned long numero_, const unsigned long nb_elems_, Tampon& tampon_) :
  numero(numero_),
  nb_elems(nb_elems_),
  tampon(tampon_)
{}

void Producteur::operator()(void)
{
  for (unsigned long i=0; i<nb_elems; i++)
  {
    this_thread::sleep_for(milliseconds(2000+numero*500));
    tampon.deposer_element(Element(numero));
  }
}
