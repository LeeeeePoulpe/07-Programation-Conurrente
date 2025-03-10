#ifndef ECRAN_MANCHOTS_HPP_
#define ECRAN_MANCHOTS_HPP_

#include <mutex>

#include "Element.hpp"

class EcranManchots
{
public :
  EcranManchots(const unsigned long nb_prod,
                const unsigned long taille_,
                const unsigned long nb_cons,
                const unsigned long famille);
  ~EcranManchots();
  EcranManchots(const EcranManchots&) = delete;
  EcranManchots& operator=(const EcranManchots&) = delete;

  void dessiner_creer_manchot(Element& e);
  void dessiner_demander_manchot(const int numcons, const int nummanchot);
  void dessiner_deposer_manchot(Element& e);
  void dessiner_retirer_manchot(Element& e, const int nummanchot);

private :
  std::mutex m;

  int taille;
  int tete_ecriture;
  int tete_lecture;
};
#endif // ECRAN_MANCHOTS_HPP_
