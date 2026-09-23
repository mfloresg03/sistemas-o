#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex; // Declaración del mutex

// Función del hilo
void* hilo_funcion_con_mutex(void* arg) {
	pthread_mutex_lock(&mutex); // Bloquear el mutex
	printf("Hola desde el hilo %d\n", (int)(long)arg);
	pthread_mutex_unlock(&mutex); // Desbloquear el mutex
	pthread_exit(NULL);
}

void ejecutar_con_hilos(int num_hilos) {
	pthread_t hilos[num_hilos];

	// Inicializar el mutex
	pthread_mutex_init(&mutex, NULL);

	// Medición de tiempo
	clock_t start, end;
	start = clock(); // Inicio del temporizador

	//Crear hilos
	for (long i = 0; i < num_hilos; i++) {
		pthread_create(&hilos[i], NULL, hilo_funcion_con_mutex, (void*)i);
	}

	// ESperar a que los hilos terminen
	for (int i = 0; i < num_hilos; i++) {
		pthread_join(hilos[i], NULL);
	}

	end = clock(); // Fin del temporizador

	// Destruir el mutex
	pthread_mutex_destroy(&mutex);

	//Calcular y mostrar el tiempo total de ejecución
	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Tiempo total de ejecución con %d hilos: %f segundos\n", num_hilos, cpu_time_used);
}

int main() {
	printf("Ejecutando con 1 hilo...\n");
	ejecutar_con_hilos(1);
	printf("Ejecutando con 5 hilos...\n");
        ejecutar_con_hilos(1);
	printf("Ejecutando con 10 hilos...\n");
        ejecutar_con_hilos(10);

	printf("Finalizó la ejecución del programa principal/n");
	return 0;
}

