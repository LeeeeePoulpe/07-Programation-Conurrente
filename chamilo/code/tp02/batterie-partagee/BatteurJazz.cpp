#include "Batterie.hpp"
#include "Batteur.hpp"
#include "BatteurJazz.hpp"

using namespace std;

BatteurJazz::BatteurJazz(const unsigned long numero_, Batterie& batterie_) :
  Batteur(numero_,batterie_)
{}

void BatteurJazz::operator()(void)
{
  for (unsigned long i=0; i<NB_FRAPPES; i++)
    batterie.frapper_decale(numero%2);
}
