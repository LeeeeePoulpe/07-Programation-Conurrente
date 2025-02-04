#ifndef VOIE_VILLE_HPP_
#define VOIE_VILLE_HPP_

#include <mutex>

class VoieVille
{
  friend class Trajet;

public :
  VoieVille();

private :
  char nom;     // nom de la ville reliée à la voie
  std::mutex m; // utilisé par les trains pour protéger l'accès à la voie

  static unsigned long compteur;
};

#endif //VOIE_VILLE_HPP_
