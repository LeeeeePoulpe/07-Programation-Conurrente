#include <iostream>
#include <thread>

#include "MonThread.hpp"
#include "SectionCritique.hpp"

using namespace std;
using namespace std::chrono;

MonThread::MonThread(const unsigned long numero_, SectionCritique& sc_) :
  numero(numero_),
  sc(sc_)
{}

void MonThread::operator()(void)
{
  for (unsigned long r=1; r <= 4; ++r)
  {
    this_thread::sleep_for(milliseconds(500)*(numero+1));
    sc.entrer();
    {
      lock_guard<mutex> verrou(mutex_cout);
      en_cours++;
      cout << en_cours;
      cout << " -> Thread " << numero << " entre en section critique" << endl;
    }
    this_thread::sleep_for(milliseconds(500)*(numero+1));
    {
      lock_guard<mutex> verrou(mutex_cout);
      en_cours--;
      cout << en_cours;
      cout << " <- Thread " << numero << "  sort de section critique" << endl;
    }
    sc.sortir();
    this_thread::sleep_for(milliseconds(500)*(numero+1));
    
  }
}
