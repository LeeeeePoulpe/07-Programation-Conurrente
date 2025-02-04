#include <thread>
#include <chrono>

#include "Positions.hpp"
#include "Temps.hpp"

using namespace std;
using namespace std::chrono;

Temps::Temps(bool& actif_, Positions& positions_) :
  actif(actif_),
  positions(positions_)
{}

void Temps::operator()(void)
{
  while (actif)
  {
    // afficher les positions des trains toutes les "tempo" secondes
    positions.afficherPositions();
    this_thread::sleep_for(milliseconds(400)); // tempo
  }
}
