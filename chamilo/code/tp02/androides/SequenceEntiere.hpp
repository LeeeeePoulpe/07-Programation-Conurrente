#ifndef SEQUENCE_ENTIERE_HPP_
#define SEQUENCE_ENTIERE_HPP_

#include <mutex>

class SequenceEntiere
{
public :
  SequenceEntiere(unsigned int numero_initial=0);
  unsigned int nouveau_numero(void);

private :
  unsigned int numero;
  std::mutex mon_mutex;
};

#endif // SEQUENCE_ENTIERE_HPP_
