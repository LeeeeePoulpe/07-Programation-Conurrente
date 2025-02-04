#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>  //pour getpid()
#include <sys/syscall.h> //pour syscall()

/*-------------------------------------------------------------------------------
 * Macro pour éviter les warnings "unused ..." dans une version intermédiaire.
 * A enlever lorsqu'elle n'est plus utilisée.
 * -----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

using namespace std;

static void ma_fonction(void)
{
  cout << "Je suis le thread " << this_thread::get_id()
       << " de tid " << syscall(SYS_gettid)
       << ", thread de " << getpid()
       << " fils de " << getppid() << endl;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "Usage : " << argv[0] << " nb_threads" << endl;
    exit(EXIT_FAILURE);
  }

  unsigned long nb_threads = stoul(argv[1]);

  // création des threads
  vector<thread> mes_threads;
  //--TODO-- à remplacer --TODO--/
  UNUSED(nb_threads);
  UNUSED(ma_fonction);
  //-----------------------------/

  // attente des threads
  //--TODO-- à compléter --TODO--/
  //-----------------------------/

  cout << "Je suis le thread " << this_thread::get_id()
       << " de tid " << syscall(SYS_gettid)
       << ", thread de " << getpid()
       << " fils de " << getppid() << endl;

  return EXIT_SUCCESS;
}
