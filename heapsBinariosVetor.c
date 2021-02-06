#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void troca(int v[], int i1, int i2){

    int aux;

    aux=v[i1];
    v[i1]=v[i2];
    v[i2]=aux;
}

void bottom_UP_Min(int v[], int n, int n1){

    int meio=(n-1)/2;

    if(meio < 0)
        return;

    for(int i=0;i<n1;i++){

        if(((meio*2 + 2) <= n1)){

            //printf("carai\n");
            if((v[meio] > v[meio*2 + 1]) || (v[meio] > v[meio*2 + 2])){
                
                //printf("carai1\n");
                if(v[meio*2 + 1] < v[meio*2 + 2]){
                    //printf("carai2\n");
                    troca(v, meio , meio*2+1);
                    meio=meio*2+1;
                }
                else{
                    //printf("carai3\n");
                    troca(v, meio , meio*2+2);
                    meio=meio*2+2;
                }
            }
        }
        else{
            if(((meio*2 + 1) <= n1)){
                if(v[meio] > v[meio*2 + 1]){
                    troca(v, meio , meio*2+1);
                }
            }
            break;
        }
    }

    //for(int i=0;i<(n1+1);i++)
    //    printf("%d ", *(v+i));
    //printf("\n");

    bottom_UP_Min(v,n-1,n1);
}


void bottom_UP_Max(int v[], int n, int n1){

    int meio=(n-1)/2;

    if(meio < 0)
        return;

    for(int i=0;i<n1;i++){

        if(((meio*2 + 2) <= n1)){

            //printf("carai\n");
            if((v[meio] < v[meio*2 + 1]) || (v[meio] < v[meio*2 + 2])){
                
                //printf("carai1\n");
                if(v[meio*2 + 1] > v[meio*2 + 2]){
                    //printf("carai2\n");
                    troca(v, meio , meio*2+1);
                    meio=meio*2+1;
                }
                else{
                    //printf("carai3\n");
                    troca(v, meio , meio*2+2);
                    meio=meio*2+2;
                }
            }
        }
        else{
            if(((meio*2 + 1) <= n1)){
                if(v[meio] < v[meio*2 + 1]){
                    troca(v, meio , meio*2+1);
                }
            }
            break;
        }
    }

    //for(int i=0;i<(n1+1);i++)
    //  printf("%d ", *(v+i));
    //printf("\n");

    bottom_UP_Max(v,n-1,n1);
}

void main(){
    
    int n;
    printf("Digite o tamanho do vetor:");
    scanf("%d", &n);

    int v[n];

    srand(time(NULL));

    for(int i=0;i<n;i++)
       v[i]= rand() % 100;

    for(int i=0;i<n;i++)
        printf("%d ", *(v+i));

    printf("\n");

    //printf("vai a merda1\n");
    bottom_UP_Max(v,n-1,n-1);
    //printf("vai a merda2\n");

    printf("Heap de Max:");
    for(int i=0;i<n;i++)
        printf("%d ", *(v+i));
    
    printf("\n\n");

    //for(int i=0;i<n;i++)
    //   v[i]= rand() % 100;

    for(int i=0;i<n;i++)
        printf("%d ", *(v+i));
    printf("\n");

    bottom_UP_Min(v,n-1,n-1);

    printf("Heap de Min:");
    for(int i=0;i<n;i++)
        printf("%d ", *(v+i));

    free(v);
}