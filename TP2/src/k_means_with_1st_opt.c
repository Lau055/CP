
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <float.h>

typedef struct Ponto {
    float x, y;
    int cluster;
} Ponto;

Ponto *cluster, *ponto;
int K =0, N = 0, T =0;

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

    #pragma omp parallel for schedule(dynamic,600000)

    for (int i = 0; i < N/2; i++) {
        float distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            float d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;
        }
    }
    #pragma omp parallel for schedule(dynamic,600000)

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
    for (int j = 0; j < K; j++) {
        float sum_x = 0, sum_y = 0;
        int counter = 0;
        #pragma omp parallel for reduction(+:sum_x,sum_y,counter) schedule(dynamic,600000)
        for (int i = 0; i < N/2; i++) {
            if (ponto[i].cluster == j) {
                sum_x += ponto[i].x;
                sum_y += ponto[i].y;
                counter++;
            }
        }
        #pragma omp parallel for reduction(+:sum_x,sum_y,counter) schedule(dynamic,600000)
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
            cluster[j].x = aux_x;
            cluster[j].y = aux_y;
            cluster[j].cluster = counter;
        }
    }
}

int main(int argc, char * argv[]) {
    argc < 4 ?  exit(0) : 0;
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    T = atoi(argv[3]);

    ponto = (Ponto *) malloc(N * sizeof(Ponto));
    cluster = (Ponto *) malloc(K * sizeof(Ponto));
    inicializa();
    colocar();

    omp_set_num_threads(T);
    #pragma omp for
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