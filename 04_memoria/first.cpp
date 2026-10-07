#include <iostream>
using namespace std;

void firstFit(int blockSize[], int m, const int processSize[], int n)
{
    // Arreglo dinámico para guardar el bloque asignado a cada proceso (-1 si no se asigna)
    int* allocation = new int[n];

    for (int i = 0; i < n; ++i) 
		allocation[i] = -1;

    // Algoritmo First-Fit
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;              // asigna bloque j al proceso i
                blockSize[j] -= processSize[i]; // reduce espacio libre del bloque
                break;                          // pasa al siguiente proceso
            }
        }
    }

    // Salida
    cout << "\nNo. Proceso\tTamano Proceso\tNo. Bloque\n";
    for (int i = 0; i < n; ++i) {
        cout << " " << (i + 1) << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1) 
		cout << (allocation[i] + 1);
        else
		cout << "No Asignado";
        cout << "\n";
    }

    delete[] allocation; // libera memoria
}

int main()
{
    int blockSize[]   = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 301};

    int m = sizeof(blockSize)   / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, m, processSize, n);
    return 0;
}
