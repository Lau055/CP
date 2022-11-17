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

    #pragma omp parallel for

    for (int i = 0; i < N/2; i++) {
        float distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            float d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;
        }
    }
    #pragma omp parallel for 

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
    float sum_x[K];
    float sum_y[K];
    int counter[K];

    for(int i = 0 ;  i < K  ; i++){
        sum_x[i] = 0.0;
        sum_y[i] = 0.0;    
        counter[i] = 0;
    }

    #pragma omp parallel for reduction(+:sum_x,sum_y,counter) schedule(guided,N/3)
    for(int i = 0 ;  i < N ; i++){
        sum_x[ponto[i].cluster] += ponto[i].x;
        sum_y[ponto[i].cluster] += ponto[i].y;
        counter[ponto[i].cluster] ++;
    }

    for(int i = 0 ; i < K ; i++){
        float aux_x = sum_x[i] / counter[i];
        float aux_y = sum_y[i] / counter[i];
        if ((cluster[i].x- aux_x) != 0 || (cluster[i].y - aux_y) != 0) {
            cluster[i].x = aux_x;
            cluster[i].y = aux_y;
            cluster[i].cluster = counter[i];
        }
    }
}

int main(int argc, char * argv[]) {
    N = atoi(argv[1]);
    K = atoi(argv[2]);
    T = argv[3] ? atoi(argv[3]) : 0;

    ponto = (Ponto *) malloc(N * sizeof(Ponto));
    cluster = (Ponto *) malloc(K * sizeof(Ponto));
    inicializa();
    colocar();

    omp_set_num_threads(T);
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