#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main() {
    string comando;

    while (true) {
        cout << "SO> ";
        cin >> comando;

        if (comando == "salir") {
            cout << "Finalizando interprete..." << endl;
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            cerr << "Error al crear el proceso hijo." << endl;
            continue;
        }

        if (pid == 0) {
            // Proceso hijo
            string ruta = "/bin/" + comando;

            execl(ruta.c_str(), comando.c_str(), (char *)NULL);

            // Solo se ejecuta si exec falla
            cerr << "Error al ejecutar el comando: " << comando << endl;
            return 1;

        } else {
            // Proceso padre
            int estado;
            waitpid(pid, &estado, 0);
        }
    }

    return 0;
}
