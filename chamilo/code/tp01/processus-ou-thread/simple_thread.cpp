#include <iostream>
#include <thread>
#include <unistd.h>  //pour getpid()
#include <sys/syscall.h> //pour syscall()

/*-------------------------------------------------------------------------------
 * Macro pour éviter les warnings "unused ..." dans une version intermédiaire.
 * A enlever lorsqu'elle n'est plus utilisée.
 * -----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

using namespace std;

static void ma_fonction (void)
{
  cout << "Je suis le thread " << this_thread::get_id()
       << " de tid " << syscall(SYS_gettid)
       << ", thread de " << getpid()
       << " fils de " << getppid() << endl;

}

int main (void)
{
  //--TODO-- à remplacer --TODO--/
  thread mon_thread;
  UNUSED(ma_fonction);
  //-----------------------------/

  // attente du thread
  //--TODO-- à compléter --TODO--/
  //-----------------------------/

  cout << "Je suis le thread " << this_thread::get_id()
       << " de tid " << syscall(SYS_gettid)
       << ", thread de " << getpid()
       << " fils de " << getppid() << endl;

  return EXIT_SUCCESS;
}
