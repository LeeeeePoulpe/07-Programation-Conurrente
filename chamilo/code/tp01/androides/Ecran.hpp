#ifndef ECRAN_HPP_
#define ECRAN_HPP_

#include <mutex>

class Ecran
{
public:
  Ecran();
  ~Ecran();
  //  Ecran(const Ecran&) = delete;
  //  Ecran& operator=(const Ecran&) = delete;

  void efface_car(const int x, const int y);
  void affiche_car(const char c, const int x, const int y);
  void affiche_chaine(const char *s, const int x, const int y);

private:
  static std::mutex m; // static pour le cas où l'on aurait plusieurs écrans partageant le même terminal
};

#endif // ECRAN_HPP_
