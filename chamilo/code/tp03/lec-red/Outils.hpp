#ifndef OUTILS_HPP_
#define OUTILS_HPP_

#include <string>
#include <mutex>

class Outils
{
public :
  Outils() {}
  virtual ~Outils();     // nécessaire avec méthode virtuelle

  virtual void debut_lecture(void) = 0;
  virtual void fin_lecture(void) = 0;
  virtual void debut_ecriture(void) = 0;
  virtual void fin_ecriture(void) = 0;

  void afficher_message(const unsigned long colonne, const std::string& message);

protected :
  // pour l'affichage
  std::mutex mutex_flux_sortie;
};

#endif // OUTILS_HPP_
