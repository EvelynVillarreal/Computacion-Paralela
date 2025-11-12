#include <stdio.h>
#include <time.h>
#include <xmmintrin.h>
#include <locale.h>

#define N 100000003
#define REPETICIONES 50

float A[N], B[N], C[N];

void inicializar_vectores() {
    for (int i = 0; i < N; i++) {
        A[i] = (float)i;
        B[i] = (float)(2 * i);
    }
}

void suma_secuencial() {
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
}

void suma_simd_sse() {
    int i;
    for (i = 0; i < N; i += 4) {
        __m128 va = _mm_loadu_ps(&A[i]);
        __m128 vb = _mm_loadu_ps(&B[i]);
        __m128 vc = _mm_add_ps(va, vb);
        _mm_storeu_ps(&C[i], vc);
    }
    // Procesar los elementos restantes
    for (; i < N; i++) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    setlocale(LC_ALL,"");
    FILE *fp;
    fp = fopen("resultadosNoMulitple4.csv", "w");
    if (fp == NULL) {
        printf("Error al crear el archivo CSV.\n");
        return 1;
    }

    fprintf(fp, "iteracion,tiempo_secuencial,tiempo_simd,factor_aceleracion\n");

    double total_secuencial = 0.0;
    double total_simd = 0.0;

    printf("Inicializando vectores...\n");
    inicializar_vectores();

    for (int r = 0; r < REPETICIONES; r++) {
        clock_t start, end;
        double t_seq, t_simd;

        // --- Suma secuencial ---
        start = clock();
        suma_secuencial();
        end = clock();
        t_seq = (double)(end - start) / CLOCKS_PER_SEC;

        // --- Suma SIMD ---
        start = clock();
        suma_simd_sse();
        end = clock();
        t_simd = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(fp, "%d,%.6f,%.6f,%.2fx\n", r + 1, t_seq, t_simd,t_seq/t_simd);

        total_secuencial += t_seq;
        total_simd += t_simd;

        printf("Iteracion %02d , Seq: %.6f s | SIMD: %.6f s\n", r + 1, t_seq, t_simd);
    }

    double promedio_seq = total_secuencial / REPETICIONES;
    double promedio_simd = total_simd / REPETICIONES;
    double aceleracion = promedio_seq / promedio_simd;

    printf("\n----------------------------------\n");
    printf("Promedio secuencial: %.6f s\n", promedio_seq);
    printf("Promedio SIMD: %.6f s\n", promedio_simd);
    printf("Aceleracion promedio: %.2fx\n", aceleracion);
    printf("----------------------------------\n");
    printf("Datos guardados en 'resultados.csv'.\n");

    fclose(fp);
    return 0;
}
