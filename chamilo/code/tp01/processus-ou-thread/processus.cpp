#include <iostream>
#include <functional>
#include <system_error>
#include <unistd.h> // pour fork()
#include <sys/wait.h> // pour wait() and co

using namespace std;

// classe pour exécuter une fonction void(void), dans un nouveau processus
class ProcessusSecondaire
{
  private :
    pid_t pid;

  public :
    ProcessusSecondaire(function<void(void)> fonction_fils)
    {
      pid=fork();
      if (pid==-1)
        throw system_error(errno, system_category()); // en cas de pb une exception est levée
      if (pid==0) // le fils simule le thread
      {
        fonction_fils();
        exit(EXIT_SUCCESS); // le thread n'exécute que la fonction passée en argument
      }
    }

    void join(void)
    {
      if (waitpid(pid,NULL,0) == -1)
        throw system_error(errno, system_category()); // en cas de pb une exception est levée
    }
};

static int var_globale=0;

// fonction principale destinée au deuxième fil d'exécution
static void fonction_a_executer(void)
{
  var_globale++;
  cout << "Valeur globale dans le secondaire : " << var_globale << endl;
}

int main(void)
{
  // création
  ProcessusSecondaire secondaire(fonction_a_executer);

  // synchronisation
  secondaire.join();

  cout << "Valeur globale dans le principal  : " << var_globale << endl;

  return EXIT_SUCCESS;
}
