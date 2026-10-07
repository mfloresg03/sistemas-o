#include <iostream>
#include <vector>

using namespace std;

void mejorAjuste(vector<int>& bloques, vector<int>& procesos) {
    int n_bloques = bloques.size();
    int n_procesos = procesos.size();
    vector<int> asignacion(n_procesos, -1);

    for (int i = 0; i < n_procesos; i++) {
        int mejorIdx = -1;
        for (int j = 0; j < n_bloques; j++) {
            if (bloques[j] >= procesos[i]) {
                if (mejorIdx == -1 || bloques[j] < bloques[mejorIdx]) {
                    mejorIdx = j;
                }
            }
        }

        if (mejorIdx != -1) {
            asignacion[i] = mejorIdx;
            bloques[mejorIdx] -= procesos[i];
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

    mejorAjuste(bloques, procesos);

    return 0;
}
