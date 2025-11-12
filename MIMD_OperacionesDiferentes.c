#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define N 100
#define NUM_HILOS 4

float datos[N];

typedef struct {
    int inicio;
    int fin;
    int operacion;
} Tarea;

void* procesar(void* arg) {
    Tarea* t = (Tarea*) arg;
    for (int i = t->inicio; i <= t->fin; i++) {
        switch (t->operacion) {
            case 0: datos[i] = pow(datos[i], 3); break;      // elevar al cubo
            case 1: datos[i] = log(datos[i]); break;         // logaritmo natural
            case 2: datos[i] = cos(datos[i]); break;         // coseno
            case 3: datos[i] = exp(datos[i] / 100.0); break; // exponencial 
            default: break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_HILOS];
    Tarea tareas[NUM_HILOS];
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    for (int i = 0; i < N; i++) {
        datos[i] = (float)(i + 1);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        tareas[i].inicio = i * 25;
        tareas[i].fin = tareas[i].inicio + 24;
        tareas[i].operacion = i;
        pthread_create(&hilos[i], NULL, procesar, &tareas[i]);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        if(i==0){
            printf("\n\t=====================Elevado al Cubo=================\t\n");
        }else if(i==25){
            printf("\n\t=====================Logaritmo natural=================\t\n");

        }else if(i==50){
            printf("\n\t=====================Coseno=================\t\n");

        }else if(i==75){
            printf("\n\t=====================Exponencial=================\t\n");

        }
        printf("datos[%d] = %.4f\n", i, datos[i]);
        
    }

    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.6f segundos\n", tiempo);

    return 0;
}
