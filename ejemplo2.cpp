
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

    cout << "Inicio del programa" << endl;

    fork();
    fork();

    cout << "Proceso PID = "
         << getpid()
         << ", PPID = "
         << getppid()
         << endl;

    return 0;
}

