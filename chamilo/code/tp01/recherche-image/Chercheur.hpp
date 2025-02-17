#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_
#include "ImagePPM.hpp"
#include "SearchImageData.hpp"

// Classe avec opérateur parenthèses défini
class Chercheur
{
public:
  Chercheur(t_image &subImg, t_image &queryImg, SearchImageData &data);
  void operator()(void);

private:
  t_image &subImage;
  t_image &query;
  SearchImageData &result;
};

#endif // MONTHREAD_HPP_
