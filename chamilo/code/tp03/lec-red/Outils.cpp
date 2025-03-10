#include <iostream>
#include <iomanip>

#include "Outils.hpp"

using namespace std;

Outils::~Outils() = default; // nécessaire avec méthode virtuelle

void Outils::afficher_message(const unsigned long colonne, const string& message)
{
  const unsigned long largeur = message.size();
  lock_guard<mutex> verrou(mutex_flux_sortie);

  cout << setw(static_cast<int>(9*colonne+largeur)) << message << endl;
}
