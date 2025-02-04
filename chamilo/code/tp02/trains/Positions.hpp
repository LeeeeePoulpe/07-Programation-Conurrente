#ifndef POSITIONS_HPP_
#define POSITIONS_HPP_

#include <vector>
#include <mutex>

#include "Trajet.hpp"

class Positions
{
public :
  Positions(const unsigned long nb_threads, std::vector<VoieVille>& voies_villes);

  // fonction utilisée pour la création des threads trains
  Trajet& getTrajet(const unsigned long numero);

  // fonctions changeant l'état du train numero
  void sePreparer(const unsigned long numero);      // Le train se prépare à partir
  void partir(const unsigned long numero);          // Le train part de la gare et est sur le segment de la ville de départ
  void arriverJonction(const unsigned long numero); // Le train atteint la jonction
  void partirJonction(const unsigned long numero);  // Le train s'engage sur la portion suivante
  void arriver(const unsigned long numero);         // Le train arrive à destination

  // fonction utilisée par Temps pour les affichages réguliers
  void afficherPositions(void);

private :
  std::vector<char> position; // Position des différents trains sur les voies
  std::mutex mutex_position; // indépendant de la synchronisation des trains : juste pour l'affichage

  std::vector<Trajet> trajets; // Pas d'écriture après initialisation : ressource non critique

  void afficherNouvellesPositions(const unsigned long numero, const std::string& message);
  void testerCollisions(void);
};

#endif // POSITIONS_HPP_
