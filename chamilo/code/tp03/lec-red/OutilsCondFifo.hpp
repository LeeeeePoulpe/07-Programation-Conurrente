#ifndef OUTILS_COND_FIFO_HPP_
#define OUTILS_COND_FIFO_HPP_

//--TODO-- à compléter --TODO--/
//-----------------------------/

#include "Outils.hpp"

class OutilsCondFifo : public Outils
{
public :
  OutilsCondFifo();

  void debut_lecture(void) override;
  void fin_lecture(void) override;
  void debut_ecriture(void) override;
  void fin_ecriture(void) override;

private :
  //--TODO-- à compléter --TODO--/
  //-----------------------------/
};

#endif // OUTILS_COND_FIFO_HPP_
