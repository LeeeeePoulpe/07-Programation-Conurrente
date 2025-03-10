#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

class Element
{
public :
  Element(){}
  Element(const unsigned long num_prod_);
  void traitement(void);
  int getNumProd(void);
  int getNumCons(void);
  void setNumCons(unsigned long num_cons_);

private :
  int num_prod;
  int num_cons;
};

#endif // ELEMENT_HPP_
