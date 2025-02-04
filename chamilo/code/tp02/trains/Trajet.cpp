#include <iostream>
#include <vector>
#include <random>

#include "VoieVille.hpp"
#include "Trajet.hpp"

using namespace std;

default_random_engine Trajet::gen;

/*----------------------------------------------------------*
 *        Création des trajets                              *
 *----------------------------------------------------------*/

// Les trajets des trains partent de chaque ville successivement...
static unsigned long calcul_ville_depart(const unsigned long numero, const unsigned long nb_villes)
{
  return numero%nb_villes;
}

// ...pour rejoindre une des autres villes choisie au hasard
static unsigned long calcul_ville_arrivee(const unsigned long numero, const unsigned long nb_villes,
                                          default_random_engine& gen_)
{
  uniform_int_distribution<unsigned long> dis(0,nb_villes-1);
  unsigned long res = dis(gen_);
  // Tant que c'est la même ville, refait un tirage
  while (res == numero%nb_villes)
    res = dis(gen_);
  return res;
}

Trajet::Trajet(const unsigned long numero, vector<VoieVille>& voies_villes) :
  voieVilleDepart(voies_villes.at(calcul_ville_depart(numero, voies_villes.size()))),
  voieVilleArrivee(voies_villes.at(calcul_ville_arrivee(numero, voies_villes.size(),gen)))
{
  // Entête de la simulation : affichage des trajets des différents trains
  cout << voieVilleDepart.nom << "->" << voieVilleArrivee.nom << "|";
}

/*----------------------------------------------------------*
 *        Pour l'affichage des positions                    *
 *----------------------------------------------------------*/

char Trajet::getDepart(void)
{
  return voieVilleDepart.nom;
}

char Trajet::getArrivee(void)
{
  return voieVilleArrivee.nom;
}

/*-----------------------------------------------------------------------------*
 *        Synchronisation sur les voies à emprunter                            *
 *-----------------------------------------------------------------------------*/
void Trajet::reserverDepart(void)
{
  voieVilleDepart.m.lock();
}

void Trajet::libererDepart(void)
{
  voieVilleDepart.m.unlock();
}

void Trajet::reserverArrivee(void)
{
  voieVilleArrivee.m.lock();
}

void Trajet::libererArrivee(void)
{
  voieVilleArrivee.m.unlock();
}

bool Trajet::departAvantArrivee(void)
{
  return ( voieVilleDepart.nom < voieVilleArrivee.nom );
}
