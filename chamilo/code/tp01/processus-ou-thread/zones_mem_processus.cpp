#include <iostream>
#include <sstream>
#include <system_error>
#include <unistd.h> // pour fork()
#include <sys/wait.h> // pour wait() and co
#include <stdlib.h> // pour system()

using namespace std;

static int var_globale;

static void ma_fonction(int var_pile_fonc)
{
  cout << "var_pile_fonc " << var_pile_fonc << " : adresse " << &var_pile_fonc << endl;
  cout << "--------------------------------------" << endl;
}

int main(void)
{
  int var_pile_main[2] = {1,2};

  cout << "--------------------------------------" << endl;
  cout << "var_globale     : adresse " << &var_globale << endl;
  cout << "var_pile_main   : adresse " << &var_pile_main << endl;
  cout << "--------------------------------------" << endl;

  // Création d'un processus fils
  int res=fork();
  if (res==-1)
    throw system_error(errno, system_category());

  if (res==0) // le fils
  {
    ma_fonction(var_pile_main[1]);
  }
  else // le père
  {
    // Attente du processus fils
    waitpid(res,NULL,0);

    ma_fonction(var_pile_main[0]);

    // affichage de l'espace mémoire logique du processus
    ostringstream oss;
    oss << "cat /proc/" << getpid() << "/maps";
    if( system(oss.str().c_str()) != 0)
      throw;
    cout << "--------------------------------------" << endl;
  }

  return EXIT_SUCCESS;
}
