#include<stdio.h>
#include<stdlib.h>


#define N 100
#define K 4

typedef struct Ponto {
    float x, y;
    int clusters;
    float distancia_minima;
} Ponto;

Ponto *Ponto_ini() {

    Ponto *p = malloc(sizeof(Ponto));
    p->x = 0;
    p->y = 0;
    p->clusters = -1;
    p->distancia_minima = 1000000000;

    return p;
}

Ponto *Ponto_ini_with_values(float this_x, float this_y) {

    Ponto *p = malloc(sizeof(Ponto));
    p->x = this_x;
    p->y = this_y;
    p->clusters = -1;
    p->distancia_minima = 1000000000;

    return p;
}

void printer_array(Ponto cluster[K][N]) {

    for (int i = 0; i < K; i++) {

        printf("Cluster %i:\n", i);
        int k = sizeof(cluster[i]);
        printf("%d", k);
        for (int j = 0; j < N; j++) {
            printf("Pontos %d = (%f,%f)\n", j, cluster[i][j].x, cluster[i][j].y);
        }
    }
}


double distance(Ponto p1, Ponto *p2) {
    return (p2->x - p1.x) * (p2->x - p1.x) + (p2->y - p1.y) * (p2->y - p1.y);
}

void inicializa(Ponto v[N], Ponto cluster[K][N]) {
    srand(10);
    for (int i = 0; i < N; i++) {
        v[i].x = (float) rand() / RAND_MAX;
        v[i].y = (float) rand() / RAND_MAX;
    }

    for (int i = 0; i < K; i++) {
        cluster[i]->x = v[i].x;
        cluster[i]->y = v[i].y;
    }

}

void point_saver(Ponto v, Ponto cluster[K][N], int j) {
    for (int i = 0; i < N; i++) {
        if ((cluster[j][i].x == 0) && (cluster[j][i].y == 0)) {
            cluster[j][i] = v;
            break;
        }
    }
}

void colocar(Ponto v[N], Ponto cluster[K][N]) {
    float distancia_min;
    int aux;
    for (int i = 0; i < N; i++) {
        aux = -1;
        distancia_min = 1000000000;
        for (int j = 0; j < K; j++) {
            distancia_min = distance(v[i], cluster[j]);
            if (v[i].distancia_minima < distancia_min) {
                v[i].distancia_minima = distancia_min;
                v[i].clusters = j;
                aux = j;
            }
        }
        point_saver(v[i], cluster, aux);
    }

    //printer_array(cluster);
}
int compare_float(float f1, float f2) {
    float precision = 0.0000001;
    if (((f1 - precision) < f2) &&
        ((f1 + precision) > f2)) {
        return 1;
    } else {
        return 0;
    }
}

int mean_cluster(Ponto cluster[K][N]) {
    double sum_x = 0;
    double sum_y = 0;
    int counter = 0;
    int changed_location = 0;
    for (int j = 0; j < K; j++) {
        sum_x = 0;
        sum_y = 0;
        counter = 0;
        for (int i = 0; i < N; i++) {
            if ((cluster[j][i].x == 0) && (cluster[j][i].y == 0)) {
                break;
            }
            sum_x += cluster[j][i].x;
            sum_y += cluster[j][i].y;
            counter++;
        }
        if (compare_float(cluster[j]->x, sum_x / counter) != 1 || compare_float(cluster[j]->y, sum_y / counter) !=1) {
            //printf("OLD -> x: %f, y: %f\n", cluster[j]->x, cluster[j]->y);
            //printf("NEW -> x: %f, y: %f\n", sum_x / counter, sum_y / counter);
            cluster[j]->x = sum_x / counter;
            cluster[j]->y = sum_y / counter;
            changed_location = 1;
        }
    }
    return changed_location;
}


int main() {
    struct Ponto v[N] = {0};
    struct Ponto cluster[K][N] = {0};
    int changed_location = 0, counter = 0;
    inicializa(v, cluster);
    colocar(v, cluster);
    do {
        changed_location = mean_cluster(cluster);
        if (changed_location) {
            colocar(v, cluster);
            counter++;
        }
    } while (changed_location != 0);

    printf("\nResult:\n");
    for (int i = 0; i < K; i++) {
        printf("x: %f, y: %f\n", cluster[i]->x, cluster[i]->y);
    }
    printf("counter: %d\n", counter);
    return 0;
}