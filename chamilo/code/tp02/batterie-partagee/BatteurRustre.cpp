#include "Batterie.hpp"
#include "Batteur.hpp"
#include "BatteurRustre.hpp"

using namespace std;

BatteurRustre::BatteurRustre(const unsigned long numero_, Batterie& batterie_) :
  Batteur(numero_,batterie_)
{}

void BatteurRustre::operator()(void)
{
  for (unsigned long i=0; i<NB_FRAPPES; i++)
    batterie.frapper_ensemble(numero%2);
}
