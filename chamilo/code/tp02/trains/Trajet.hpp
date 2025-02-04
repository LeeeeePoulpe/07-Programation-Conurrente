#ifndef TRAJET_HPP_
#define TRAJET_HPP_

#include <vector>
#include <random>

#include "VoieVille.hpp"

class Trajet
{
public :
  Trajet(const unsigned long numero, std::vector<VoieVille>& voies_villes);

  // fonctions de synchronisation sur les voies à emprunter
  void reserverDepart(void);
  void libererDepart(void);
  void reserverArrivee(void);
  void libererArrivee(void);

  bool departAvantArrivee(void);

  // pour affichage des positions
  char getDepart(void);
  char getArrivee(void);

private :
  VoieVille& voieVilleDepart;
  VoieVille& voieVilleArrivee;

  static std::default_random_engine gen;
};

#endif // TRAJET_HPP_
