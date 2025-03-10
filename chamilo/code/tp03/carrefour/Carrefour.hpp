#ifndef CARREFOUR_HPP_
#define CARREFOUR_HPP_

#include <string>
#include <mutex>
//--TODO-- à compléter --TODO--/
//-----------------------------/

class Carrefour
{
public :
  Carrefour();
  void entrer_dans_carrefour(unsigned int voie);
  void sortir_du_carrefour(unsigned int voie);
  void basculer_sur(unsigned int nouvelle_voie_verte);

  // constantes pour les voies
  static const unsigned int nb_voies = 2;
  static const unsigned int voie_principale = 0;
  static const unsigned int voie_secondaire = 1;

private :
  // outils de synchronisation
  //--TODO-- à compléter --TODO--/
  //-----------------------------/

  // variables partagées pour la synchronisation
  unsigned int voie_verte;           // voie dont le feu est vert
  bool automobile_engagee;  // == true si une automobile est engagée sur le carrefour

  // pour l'affichage
  std::mutex mutex_affichage;
public :
  void afficherMessageCommutation(unsigned int voie, std::string message);
  void afficherMessageAuto(unsigned int voie, unsigned long numero, std::string message);
};

#endif // CARREFOUR_HPP_
