
#include<stdio.h>
#include<stdlib.h>

#define N 10000000
#define K 4

typedef struct Ponto {
    float x, y;
    int cluster;
} Ponto;

Ponto *cluster, *ponto;

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

int mean() {
    int changed_location = 0;
    float sum_x[K];
    float sum_y[K];
    int counter[K];

    for(int i = 0 ;  i < K  ; i++){
        sum_x[i] = 0.0;
        sum_y[i] = 0.0;    
        counter[i] = 0;
    }

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
            changed_location = 1;
        }
    }

    return changed_location;
}

int main() {
    ponto = (Ponto *) malloc(N * sizeof(Ponto));
    cluster = (Ponto *) malloc(K * sizeof(Ponto));
    int changed_location = 1;
    int counter = 0;
    inicializa();
    colocar();

    while (changed_location == 1) {
        changed_location = mean();
        changed_location == 1 ? colocar(): 0;
        changed_location == 1 ? counter++: 0;
    }

    for (int i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %i\n", cluster[i].x, cluster[i].y, cluster[i].cluster);
    }
    printf("Iterations: %d\n", counter);
    return 0;
}