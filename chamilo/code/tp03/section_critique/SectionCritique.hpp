#ifndef SECTIONCRITIQUE_HPP_
#define SECTIONCRITIQUE_HPP_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class SectionCritique
{
public:
  SectionCritique(const unsigned long nb_libre_);
  ~SectionCritique();
  void entrer();
  void sortir();

private:
  unsigned long nb_libre;
  //--TODO-- à compléter --TODO--/


  //-----------------------------/
};

#endif // SECTIONCRITIQUE_HPP_
