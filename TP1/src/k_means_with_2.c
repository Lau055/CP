#include<stdio.h>
#include<stdlib.h>

#define N 10000000
#define K 4

typedef struct Ponto {
    float x, y;
    int clusters;
    float distancia_minima;
} Ponto;

Ponto Ponto_ini() {

    struct Ponto p;
    p.x = 0;
    p.y = 0;
    p.clusters = -1;
    p.distancia_minima = 1000000000;

    return p;
}

float distance(Ponto p1, Ponto p2) {
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

void inicializa(Ponto v[N], Ponto cluster[K]) {
    srand(10);
    for (int i = 0; i < N; i++) {
        v[i].x = (float) rand() / RAND_MAX;
        v[i].y = (float) rand() / RAND_MAX;
    }

    for (int i = 0; i < K; i++) {
        cluster[i].x = v[i].x;
        cluster[i].y = v[i].y;
    }

}

void colocar(Ponto v[], Ponto cluster[]) {

    for (int i = 0; i < N; i += 5) {
        v[i].distancia_minima = 1000000000;
        v[i + 1].distancia_minima = 1000000000;
        v[i + 2].distancia_minima = 1000000000;
        v[i + 3].distancia_minima = 1000000000;
        v[i + 4].distancia_minima = 1000000000;
    }


    float distancia_min1 = 10000000;
    float distancia_min2 = 10000000;
    float distancia_min3 = 10000000;
    float distancia_min4 = 10000000;
    float distancia_min5 = 10000000;

    for (int i = 0; i < N; i += 5) {
        for (int j = 0; j < K; j++) {
            distancia_min1 = distance(v[i], cluster[j]);
            distancia_min2 = distance(v[i + 1], cluster[j]);
            distancia_min3 = distance(v[i + 2], cluster[j]);
            distancia_min4 = distance(v[i + 3], cluster[j]);
            distancia_min5 = distance(v[i + 4], cluster[j]);
            if (v[i].distancia_minima > distancia_min1) {
                v[i].distancia_minima = distancia_min1;
                v[i].clusters = j;
            }
            if (v[i + 1].distancia_minima > distancia_min2) {
                v[i + 1].distancia_minima = distancia_min2;
                v[i + 1].clusters = j;
            }
            if (v[i + 2].distancia_minima > distancia_min3) {
                v[i + 2].distancia_minima = distancia_min3;
                v[i + 2].clusters = j;
            }
            if (v[i + 3].distancia_minima > distancia_min4) {
                v[i + 3].distancia_minima = distancia_min4;
                v[i + 3].clusters = j;
            }
            if (v[i + 4].distancia_minima > distancia_min5) {
                v[i + 4].distancia_minima = distancia_min5;
                v[i + 4].clusters = j;
            }

        }
    }
}

int comparar(float f1, float f2) {
    float precision = 0.000001;
    if (((f1 - precision) < f2) &&
        ((f1 + precision) > f2)) {
        return 1;
    } else {
        return 0;
    }
}

int mean(struct Ponto v[N], struct Ponto cluster[K]) {
    int changed = 0;
    for (int j = 0; j < K; j++) {
        float sumx = 0, sumy = 0;
        int counter = 0;
        for (int i = 0; i < N; i+=10 ) {
            if(v[i].clusters == j){
                sumx += v[i].x;
                sumy += v[i].y;
                counter++;
            }
            if(v[i+1].clusters == j){
                sumx += v[i+1].x;
                sumy += v[i+1].y;
                counter++;
            }
            if(v[i+2].clusters == j){
                sumx += v[i+2].x;
                sumy += v[i+2].y;
                counter++;
            }
            if(v[i+3].clusters == j){
                sumx += v[i+3].x;
                sumy += v[i+3].y;
                counter++;
            }
            if(v[i+4].clusters == j){
                sumx += v[i+4].x;
                sumy += v[i+4].y;
                counter++;
            }
            if(v[i+5].clusters == j){
                sumx += v[i+5].x;
                sumy += v[i+5].y;
                counter++;
            }
            if(v[i+6].clusters == j){
                sumx += v[i+6].x;
                sumy += v[i+6].y;
                counter++;
            }
            if(v[i+7].clusters == j){
                sumx += v[i+7].x;
                sumy += v[i+7].y;
                counter++;
            }
            if(v[i+8].clusters == j){
                sumx += v[i+8].x;
                sumy += v[i+8].y;
                counter++;
            }
            if(v[i+9].clusters == j){
                sumx += v[i+9].x;
                sumy += v[i+9].y;
                counter++;
            }
        }

        if (comparar(cluster[j].x, sumx / counter) != 1 && comparar(cluster[j].y, sumy / counter) != 1) {
            //printf("OLD - %i - %f,%f\n", j, cluster[j].x, cluster[j].y);
            //printf("NEW - %i - %f,%f\n", j, sumx/counter, sumy/counter);
            cluster[j].x = sumx / counter;
            cluster[j].y = sumy / counter;
            cluster[j].clusters = counter;
            changed = 1;
        }
    }
    return changed;
}

int main() {
    struct Ponto *v = (Ponto *) malloc(N * sizeof(Ponto));
    struct Ponto *cluster = (Ponto *) malloc(K * sizeof(Ponto));
    int changed_location = 0;
    int counter = 0;

    inicializa(v, cluster);
    colocar(v, cluster);

    do {
        changed_location = mean(v, cluster);
        colocar(v, cluster);
        counter++;

    } while (changed_location != 0);


    printf("\nResult:\n");
    for (int i = 0; i < K; i++) {
        printf("x: %.3f, y: %.3f\n", cluster[i].x, cluster[i].y);
    }
    printf("counter: %d\n", counter);

    return 0;
}