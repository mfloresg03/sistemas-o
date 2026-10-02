#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

    pid_t pid = fork();

    if (pid < 0) {

        cerr << "Error al crear el proceso hijo" << endl;
        return 1;

    } else if (pid == 0) {

        cout << "HIJO"
             << " | PID = " << getpid()
             << " | PPID = " << getppid()
             << endl;

    } else {

        cout << "PADRE"
             << " | PID = " << getpid()
             << " | PID del hijo = " << pid
             << endl;
    }

    return 0;
}

