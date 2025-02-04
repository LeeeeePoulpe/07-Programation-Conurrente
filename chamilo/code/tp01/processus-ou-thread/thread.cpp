#include <iostream>
#include <thread>




using namespace std;



























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
  thread secondaire(fonction_a_executer);

  // synchronisation
  secondaire.join();

  cout << "Valeur globale dans le principal  : " << var_globale << endl;

  return EXIT_SUCCESS;
}
