#include<stdio.h>
#include<stdlib.h>


#define N 10000000
#define K 4

typedef struct Ponto {
    float x, y;
    int clusters;
} Ponto;

Ponto Ponto_ini() {

    struct Ponto p;
    p.x = 0;
    p.y = 0;
    p.clusters = -1;

    return p;
}

float distance(Ponto p1, Ponto p2) {
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

void inicializa(Ponto v[], Ponto cluster[K]) {
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

    float distancia_min1=0;
    float distancia_min2=0;
    float distancia_min3=0;
    float distancia_min4=0;
    int aux = 0;

    for(int i = 0 ;  i < N/2 ;i++){
        distancia_min1 = distance(v[i],cluster[0]);
        distancia_min2 = distance(v[i],cluster[1]);
        distancia_min3 = distance(v[i],cluster[2]);
        distancia_min4 = distance(v[i],cluster[3]);

        v[i].clusters = (distancia_min1 <= distancia_min2 && distancia_min1 <= distancia_min3 && distancia_min1 <= distancia_min4)? 0 : 
        (distancia_min2 <= distancia_min1 && distancia_min2 <= distancia_min3 && distancia_min2 <= distancia_min4)? 1 :
        (distancia_min3 <= distancia_min2 && distancia_min3 <= distancia_min1 && distancia_min3 <= distancia_min4)? 2 : 3;

    }
}

float mean_x(Ponto v[], int j){
    float sum = 0;
    float counter = 0;

    for(int i = 0 ; i < N ;i++){
        if(v[i].clusters == j){
            sum += v[i].x;
            counter++;
        }
    }
    return sum/counter;
}

float mean_y(Ponto v[], int j){
    float sum = 0;
    float counter = 0;

    for(int i = 0 ; i < N ; i++){
        if(v[i].clusters == j){
            sum += v[i].y;
            counter++;
        }
    }
    return sum/counter;
}

int comparer(float f1, float f2) {
    float precision = 0.0000001;
    return ((f1-precision < f2) && (f1+precision) > f2) ? 1 : 0;
}
int check(Ponto cluster[],Ponto cluster_updated[]){

    for(int i = 0 ; i < K ; i++){
        if((comparer(cluster[i].x,cluster_updated[i].x) != 1)||(comparer(cluster[i].y,cluster_updated[i].y) != 1)){
            return 1;
        }
    }
    return 0;
}

int main(){
    struct Ponto *v =(Ponto *) malloc(N*sizeof(Ponto));
    struct Ponto *cluster = (Ponto *) malloc(K*sizeof(Ponto));
    struct Ponto *cluster_updated= (Ponto *) malloc(K*sizeof(Ponto));
    int changed_location = 1;
    int counter = 0;

    inicializa(v, cluster);
    colocar(v, cluster);

    do {
        for(int i = 0 ; i < K ; i++){
            cluster_updated[i].x = mean_x(v,i);
            cluster_updated[i].y = mean_y(v,i);
        }
        changed_location = check(cluster,cluster_updated);
        if (changed_location == 1) {
            for(int i = 0 ; i < K ; i++){
                cluster[i].x = cluster_updated[i].x;
                cluster[i].y = cluster_updated[i].y; 
            }
            colocar(v, cluster);
            counter++;
        }
    }while (changed_location != 0);

    printf("\nResult:\n");
    for (int i = 0; i < K; i++) {
        printf("x: %.3f, y: %.3f\n", cluster[i].x, cluster[i].y);
    }
    printf("counter: %d\n", counter);
    
    return 0;
}