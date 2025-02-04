#include <iostream>
#include "MonThread.hpp"

using namespace std;

MonThread::MonThread(const unsigned long numero) {
    mon_numero = numero;
}


void MonThread::operator()(void)
{
    cout << mon_numero;
}
