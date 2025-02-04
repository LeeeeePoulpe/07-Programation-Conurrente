#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_
#include <mutex>

// Classe avec opérateur parenthèses défini
class MonThread
{
public :
  MonThread(const unsigned long);
  void operator()(void);

private :
  unsigned long mon_numero;
};

#endif // MONTHREAD_HPP_
