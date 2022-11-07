#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#define N 10000000
#define K 4

typedef struct Ponto {
    float x, y;
    int cluster;
} Ponto;

Ponto *cluster, *ponto;

void alloc() {
    ponto = (Ponto *) malloc(N * sizeof(Ponto));
    cluster = (Ponto *) malloc(K * sizeof(Ponto));
}

int comparar(float f1, float f2) {
    if (fabs(f1 - f2) <= 0.000000){
        return 1;
    }
    return 0;
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

float distance(Ponto p1, Ponto p2) {
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

void colocar() {
    for (int i = 0; i < N; i++) {
        float distancia = 1000000000;
        for (int j = 0; j < K; j++) {
            float d = distance(ponto[i], cluster[j]);
            if (d < distancia) {
                distancia = d;
                ponto[i].cluster = j;
            }
        }
    }
}

int mean() {
    int changed_location = 0;
    for (int j = 0; j < K; j++) {
        float sum_x = 0, sum_y = 0;
        int counter = 0;
        for (int i = 0; i < N; i++) {
            if (ponto[i].cluster == j) {
                sum_x += ponto[i].x;
                sum_y += ponto[i].y;
                counter++;
            }
        }
        //printf("NEW Cluster %i: (%f, %f), %i\n", j, sum_x / counter, sum_y / counter, counter);
       // printf("OLD Cluster %i: (%f, %f), %i\n", j, cluster[j].x, cluster[j].y, cluster[j].cluster);

        if (comparar(cluster[j].x, sum_x / counter) == 0 && comparar(cluster[j].y, sum_y / counter) == 0) {
            changed_location = 1;
            cluster[j].x = sum_x / counter;
            cluster[j].y = sum_y / counter;
            cluster[j].cluster = counter;
        }
    }

    return changed_location;
}

int main() {
    int changed_location = 1;
    int counter = 0;
    alloc();
    inicializa();
    colocar();

    while (changed_location == 1) {
        changed_location = mean();

        if (changed_location == 1) {
            colocar();
            counter++;
        }
    }

    printf("\nResult:\n");
    for (int i = 0; i < K; i++) {
        printf("Center: (%.3f, %.3f) : Size: %i\n", cluster[i].x, cluster[i].y, cluster[i].cluster);
    }
    printf("Iterations: %d\n", counter);
    return 0;
}