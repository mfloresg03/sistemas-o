#include <iostream>
#include <vector>

using namespace std;

void nextFit(vector<int>& bloques, vector<int>& procesos) {
    int n_bloques = bloques.size();
    int n_procesos = procesos.size();
    vector<int> asignacion(n_procesos, -1);
    int j = 0;

    for (int i = 0; i < n_procesos; i++) {
        int conteo = 0;
        while (conteo < n_bloques) {
            if (bloques[j] >= procesos[i]) {
                asignacion[i] = j;
                bloques[j] -= procesos[i];
                break;
            }
            j = (j + 1) % n_bloques;
            conteo++;
        }
    }

    cout << "\nNo. Proceso\tTamano Proceso\tNo. Bloque\n";
    for (int i = 0; i < n_procesos; i++) {
        cout << " " << i + 1 << "\t\t" << procesos[i] << "\t\t";
        if (asignacion[i] != -1)
            cout << asignacion[i] + 1;
        else
            cout << "No Asignado";
        cout << endl;
    }
}

int main() {
    vector<int> bloques = {100, 500, 200, 300, 600};
    vector<int> procesos = {212, 417, 112, 381};

    nextFit(bloques, procesos);

    return 0;
}
