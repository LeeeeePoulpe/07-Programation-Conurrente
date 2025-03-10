#ifndef RENDEZVOUS_HPP_
#define RENDEZVOUS_HPP_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class RendezVous
{
public:
  RendezVous(const unsigned long nb_threads_);
  ~RendezVous();
  void rvReveilleurUnique(void);
  void rvCascade(void);
  void afficher(const unsigned long numero, const std::string& message, const unsigned long num_rendez_vous);

private:
  const unsigned long nb_threads;
  //--TODO-- à compléter --TODO--/
  //-----------------------------/

  // pour l'affichage (indépendant du pb de synchro du rendez-vous)
  std::mutex mutex_flux_sortie;
};

#endif // RENDEZVOUS_HPP_
