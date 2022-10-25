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

    for(int i = 0 ; i < N ; i+=5){
        v[i].distancia_minima = 1000000000;
        v[i+1].distancia_minima = 1000000000;
        v[i+2].distancia_minima = 1000000000;
        v[i+3].distancia_minima = 1000000000;
        v[i+4].distancia_minima = 1000000000;
   }


    float distancia_min1 = 10000000;
    float distancia_min2 = 10000000;
    float distancia_min3 = 10000000;
    float distancia_min4 = 10000000;
    float distancia_min5 = 10000000;

    for (int i = 0; i < N; i+=5) {
        for (int j = 0; j < K; j++) {
            distancia_min1 = distance(v[i], cluster[j]);
            distancia_min2 = distance(v[i+1], cluster[j]);
            distancia_min3 = distance(v[i+2], cluster[j]);
            distancia_min4 = distance(v[i+3], cluster[j]);
            distancia_min5 = distance(v[i+4], cluster[j]);
            if (v[i].distancia_minima > distancia_min1) {
                v[i].distancia_minima = distancia_min1;
                v[i].clusters = j;
            }
            if (v[i+1].distancia_minima > distancia_min2) {
                v[i+1].distancia_minima = distancia_min2;
                v[i+1].clusters = j;
            }
            if (v[i+2].distancia_minima > distancia_min3) {
                v[i+2].distancia_minima = distancia_min3;
                v[i+2].clusters = j;
            }
            if (v[i+3].distancia_minima > distancia_min4) {
                v[i+3].distancia_minima = distancia_min4;
                v[i+3].clusters = j;
            }
            if (v[i+4].distancia_minima > distancia_min5) {
                v[i+4].distancia_minima = distancia_min5;
                v[i+4].clusters = j;
            }

        }
    }  
}

float mean_x(Ponto v[], int j){
    float sum = 0;
    float counter = 0;

    for(int i = 0 ; i < N ;i+=10){
        if(v[i].clusters == j){
            sum += v[i].x;
            counter++;
        }
        if(v[i+1].clusters == j){
            sum += v[i+1].x;
            counter++;
        }
        if(v[i+2].clusters == j){
            sum += v[i+2].x;
            counter++;
        }
        if(v[i+3].clusters == j){
            sum += v[i+3].x;
            counter++;
        }
        if(v[i+4].clusters == j){
            sum += v[i+4].x;
            counter++;
        }
        if(v[i+5].clusters == j){
            sum += v[i+5].x;
            counter++;
        }
        if(v[i+6].clusters == j){
            sum += v[i+6].x;
            counter++;
        }
        if(v[i+7].clusters == j){
            sum += v[i+7].x;
            counter++;
        }
        if(v[i+8].clusters == j){
            sum += v[i+8].x;
            counter++;
        }
        if(v[i+9].clusters == j){
            sum += v[i+9].x;
            counter++;
        }
    }
    return sum/counter;
}

float mean_y(Ponto v[], int j){
    float sum = 0;
    float counter = 0;

    for(int i = 0 ; i < N ; i+=10){
        if(v[i].clusters == j){
            sum += v[i].y;
            counter++;
        }
        if(v[i+1].clusters == j){
            sum += v[i+1].y;
            counter++;
        }
        if(v[i+2].clusters == j){
            sum += v[i+2].y;
            counter++;
        }
        if(v[i+3].clusters == j){
            sum += v[i+3].y;
            counter++;
        }
        if(v[i+4].clusters == j){
            sum += v[i+4].y;
            counter++;
        }
        if(v[i+5].clusters == j){
            sum += v[i+5].y;
            counter++;
        }
        if(v[i+6].clusters == j){
            sum += v[i+6].y;
            counter++;
        }
        if(v[i+7].clusters == j){
            sum += v[i+7].y;
            counter++;
        }
        if(v[i+8].clusters == j){
            sum += v[i+8].y;
            counter++;
        }
        if(v[i+9].clusters == j){
            sum += v[i+9].y;
            counter++;
        }
    }
    return sum/counter;
}

int comparer(float f1, float f2) {
    float precision = 0.0000001;
    if (((f1 - precision) < f2) &&
        ((f1 + precision) > f2)) {
        return 1;
    } else {
        return 0;
    }
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
    
    if(changed_location != 0){
        do{
            for(int i = 0 ; i < K ; i++){
                cluster_updated[i].x = mean_x(v,i);
                cluster_updated[i].y = mean_y(v,i); 
            }
            for(int i = 0 ; i < K ; i++){
                cluster[i].x = cluster_updated[i].x;
                cluster[i].y = cluster_updated[i].y; 
            }
            colocar(v, cluster);
            counter++;

        } while (changed_location != 1);
    }

    while (changed_location != 0) {
        
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
    }

    printf("\nResult:\n");
    for (int i = 0; i < K; i++) {
        printf("x: %.3f, y: %.3f\n", cluster[i].x, cluster[i].y);
    }
    printf("counter: %d\n", counter);
    
    return 0;
}