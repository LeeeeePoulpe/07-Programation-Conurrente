#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_

#include "SectionCritique.hpp"

// Classe avec opérateur parenthèses défini
class MonThread
{
public :
  MonThread(const unsigned long numero_, SectionCritique& sc_);
  void operator()();

private :
  const unsigned long numero;
  SectionCritique& sc;
  static unsigned long en_cours;
  static std::mutex mutex_cout;
};

#endif // MONTHREAD_HPP_
