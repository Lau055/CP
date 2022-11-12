
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <float.h>

#define N 10000000
#define K 4

typedef struct Ponto {
    float x, y;
    int cluster;
} Ponto;

Ponto *cluster, *ponto;

int comparar(float f1, float f2) {
    return f1 - f2 == 0;
}

void inicializa() {
    srand(10);
    for (int i = 0; i < N; i++) {
        ponto[i].x = (float) rand() / RAND_MAX;
        ponto[i].y = (float) rand() / RAND_MAX;
    }

    for (int i = 0; i < K; i++) {
        cluster[i].x = ponto[i].x;
        cluster[i].y = ponto[i].y;
        cluster[i].cluster = 0;
    }

}

void colocar() {

    for (int i = 0; i < N/2; i++) {
        float distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            float d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;
        }
    }

    for (int i = N/2; i < N; i++) {
        float distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            float d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;
        }
    }
}

void mean() {
    int changed_location = 0;
    #pragma omp parallel num_threads(2)
    #pragma omp for
    for (int j = 0; j < K; j++) {
        float sum_x = 0, sum_y = 0;
        int counter = 0;
        for (int i = 0; i < N/2; i++) {
            if (ponto[i].cluster == j) {
                sum_x += ponto[i].x;
                sum_y += ponto[i].y;
                counter++;
            }
        }

        for (int i = N/2; i < N; i++) {
            if (ponto[i].cluster == j) {
                sum_x += ponto[i].x;
                sum_y += ponto[i].y;
                counter++;
            }
        }

        float aux_x = sum_x / counter;
        float aux_y = sum_y / counter;
        if ((cluster[j].x- aux_x) != 0 || (cluster[j].y - aux_y) != 0) {
            changed_location = 1;
            cluster[j].x = aux_x;
            cluster[j].y = aux_y;
            cluster[j].cluster = counter;
        }
    }
}

int main() {
    ponto = (Ponto *) malloc(N * sizeof(Ponto));
    cluster = (Ponto *) malloc(K * sizeof(Ponto));
    int changed_location = 1;
    int counter = 0;
    inicializa();
    colocar();

    for(int i = 0 ; i < 20; i++){
        mean();
        colocar();
    }

    for (int i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %i\n", cluster[i].x, cluster[i].y, cluster[i].cluster);
    }
    printf("Iterations: %d\n", 20);
    return 0;
}
