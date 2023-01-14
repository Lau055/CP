#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <pthread.h>


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
    float d;
    float distancia;
    for (int i = 0; i < N/2; i++) {
        distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;
            //printf("Analisys :T%d cluster (%f,%f), ponto (%f,%f)\n", id, cluster[j].x,
            //cluster[j].y,ponto[i].x,ponto[i].y);
        }
    }
    for (int i = N/2; i < N; i++) {
        distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            d = (cluster[j].x - ponto[i].x) * (cluster[j].x - ponto[i].x) +
                      (cluster[j].y - ponto[i].y) * (cluster[j].y - ponto[i].y);
            ponto[i].cluster = (d < distancia ? j : ponto[i].cluster);
            distancia = d < distancia ? d : distancia;

            //printf("Analisys :T%d cluster (%f,%f), ponto (%f,%f)\n", id, cluster[j].x,
            //cluster[j].y,ponto[i].x,ponto[i].y);
        }
    }

}

void mean() {
    float sum_x[K];
    float sum_y[K];
    int counter[K];
    float aux_x,aux_y;

    for(int i = 0 ;  i < K  ; i++){
        sum_x[i] = 0.0;
        sum_y[i] = 0.0;    
        counter[i] = 0;
    }
    
    #pragma omp parallel for schedule(static,N) reduction(+:sum_x[:K],sum_y[:K],counter[:K])
    for(int i = 0 ;  i < N ; i++){
        sum_x[ponto[i].cluster] += ponto[i].x;
        sum_y[ponto[i].cluster] += ponto[i].y;
        counter[ponto[i].cluster] ++;
    }
    for(int i = 0 ; i < K ; i++){
        aux_x = sum_x[i] / counter[i];
        aux_y = sum_y[i] / counter[i];
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
    omp_set_num_threads(T);
    colocar();

    for(int i = 0 ; i < 20; i++){
        mean();
        colocar();
    }

    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %i\n", cluster[i].x, cluster[i].y, cluster[i].cluster);
    }
    printf("Iterations: %d\n", 20);
    return 0;
}