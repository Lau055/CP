#include<stdio.h>
#include<stdlib.h>


#define N 100
#define K 4

typedef struct Ponto
{
    float x,y;
    int clusters;
    float distancia_minima;
}Ponto;

Ponto* Ponto_ini(){

    Ponto* p = malloc(sizeof(Ponto));
    p->x = 0;
    p->y = 0;
    p->clusters = -1;
    p->distancia_minima = 1000000000;

    return p;
}

Ponto* Ponto_ini_with_values(float this_x, float this_y){

    Ponto* p = malloc(sizeof(Ponto));
    p->x = this_x;
    p->y = this_y;
    p->clusters = -1;
    p->distancia_minima = 1000000000;

    return p;
}

void printer_array(struct Ponto v[]){

    for(int i = 0 ;  i < N ; i++){
        printf("Ponto %i = (%f,%f)\n",i,v[i].x,v[i].y);
    }
} 


double distance(Ponto* p1 , Ponto* p2){
    return (p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y);
}

void inicializa(){
    struct Ponto v[N];
    srand(10);
    for(int i = 0 ;  i < N ; i++){
        v[i].x = (float) rand() / RAND_MAX;
        v[i].y = (float) rand() / RAND_MAX;
    }
    printer_array(v);

    
}

int main(){
    inicializa();
}
