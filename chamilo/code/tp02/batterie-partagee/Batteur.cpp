#include "Batterie.hpp"
#include "Batteur.hpp"

using namespace std;

Batteur::Batteur(const unsigned long numero_, Batterie& batterie_) :
  numero(numero_),
  batterie(batterie_)
{}
