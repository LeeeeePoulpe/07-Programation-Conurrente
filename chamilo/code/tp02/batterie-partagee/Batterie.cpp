#include <iostream>
#include <mutex>

#include "Batterie.hpp"

using namespace std;

Batterie::Batterie()
{ toms[0] = 0; toms[1] = 0;}

void Batterie::frapper_decale(const unsigned long cote)
{
    mutex_toms[cote].lock();
    mutex_toms[1-cote].lock();
    toms[cote]+=1;    // un coup sur le tom à la gauche du batteur
    toms[1-cote]+=2;  // deux coups sur le tom à la droite du batteur
    mutex_toms[cote].unlock();
    mutex_toms[1-cote].unlock();
}

void Batterie::frapper_ensemble(const unsigned long cote)
{
    mutex_toms[cote].lock();
    mutex_toms[1-cote].lock();
    toms[cote]+=1;  // un coup sur un tom
    toms[1-cote]+=1;  // un coup sur l'autre tom
    mutex_toms[cote].unlock();
    mutex_toms[1-cote].unlock();
}

void Batterie::afficher(void)
{
  cout << "Le tom de gauche a reçu " << toms[0] << " coups." << endl;
  cout << "Le tom de droite a reçu " << toms[1] << " coups." << endl;
}
