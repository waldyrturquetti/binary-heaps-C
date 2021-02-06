#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct tno{

    int chave;
    struct tno *dir;
    struct tno *esq;
}TNO;

typedef struct tpilha{

    int chave;
    struct tpilha *prox;
}TPilha;

void imprimePreOrdem(TNO *raiz){

    if(raiz==NULL)
        return;

    printf("%d\n", raiz->chave);
    imprimePreOrdem(raiz->esq);
    imprimePreOrdem(raiz->dir);

}

void RemovePilha(TPilha **Pilha){

    TPilha *aux = (*Pilha);

    while(aux != NULL){

        (*Pilha) = (*Pilha)->prox; 
        free(aux);
        aux = *Pilha;
    }

    *Pilha=NULL;
}

void heapifyMax_Insere(TNO **raiz, TPilha *Pilha, int chave){

    int aux;

    if(Pilha ==  NULL)
        return;

    if(Pilha->chave == 0){
        heapifyMax_Insere(&((*raiz)->esq), Pilha->prox, chave);

        if(chave > (*raiz)->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->esq->chave;
            (*raiz)->esq->chave = aux;
        }
    }
    else{
        heapifyMax_Insere(&((*raiz)->dir), Pilha->prox, chave);
        
        if(chave > (*raiz)->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->dir->chave;
            (*raiz)->dir->chave = aux;
        }
    }
}

void heapifyMin_Insere(TNO **raiz, TPilha *Pilha, int chave){

    int aux;

    if(Pilha ==  NULL)
        return;

    if(Pilha->chave == 0){
        heapifyMin_Insere(&((*raiz)->esq), Pilha->prox, chave);

        if(chave < (*raiz)->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->esq->chave;
            (*raiz)->esq->chave = aux;
        }
    }
    else{
        heapifyMin_Insere(&((*raiz)->dir), Pilha->prox, chave);
        
        if(chave < (*raiz)->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->dir->chave;
            (*raiz)->dir->chave = aux;
        }
    }
}

void heapifyMax_Remove(TNO **raiz){
    
    int aux;

    if(*raiz ==  NULL)
        return;

    if(((*raiz)->dir != NULL) && ((*raiz)->esq != NULL)){

        if((*raiz)->esq->chave > (*raiz)->dir->chave){

            if((*raiz)->chave < (*raiz)->esq->chave){
                aux=(*raiz)->chave;
                (*raiz)->chave = (*raiz)->esq->chave;
                (*raiz)->esq->chave = aux;
            }
            else
                return;
                
            heapifyMax_Remove(&((*raiz)->esq));
            return;
        }
        else{

            if((*raiz)->chave < (*raiz)->dir->chave){
                aux=(*raiz)->chave;
                (*raiz)->chave = (*raiz)->dir->chave;
                (*raiz)->dir->chave = aux;
            }
            else
                return;
                
    
            heapifyMax_Remove(&((*raiz)->dir));
            return;
        }
    }

    if(((*raiz)->dir == NULL) && ((*raiz)->esq != NULL)){

        if((*raiz)->chave < (*raiz)->esq->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->esq->chave;
            (*raiz)->esq->chave = aux;
        }
       
        heapifyMax_Remove(&((*raiz)->esq));
    }

    return;
}

void heapifyMin_Remove(TNO **raiz){

    int aux;

    if(*raiz ==  NULL)
        return;

    if(((*raiz)->dir != NULL) && ((*raiz)->esq != NULL)){

        if((*raiz)->esq->chave < (*raiz)->dir->chave){

            if((*raiz)->chave > (*raiz)->esq->chave){
                aux=(*raiz)->chave;
                (*raiz)->chave = (*raiz)->esq->chave;
                (*raiz)->esq->chave = aux;
            }
            else
                return;
                
            heapifyMin_Remove(&((*raiz)->esq));
            return;
        }
        else{

            if((*raiz)->chave > (*raiz)->dir->chave){
                aux=(*raiz)->chave;
                (*raiz)->chave = (*raiz)->dir->chave;
                (*raiz)->dir->chave = aux;
            }
            else
                return;
                
    
            heapifyMin_Remove(&((*raiz)->dir));
            return;
        }
    }

    if(((*raiz)->dir == NULL) && ((*raiz)->esq != NULL)){

        if((*raiz)->chave > (*raiz)->esq->chave){
            aux=(*raiz)->chave;
            (*raiz)->chave = (*raiz)->esq->chave;
            (*raiz)->esq->chave = aux;
        }
    }

    return;    
}

void inserePilha(TPilha **Pilha, int chave){ //chave seria o lado , 0:esq e 1:dir

    if(*Pilha == NULL){
        *Pilha = (TPilha*)malloc(sizeof(TPilha));

        (*Pilha)->chave = chave;
        (*Pilha)->prox=NULL;
        return;
    }

    TPilha *aux=(TPilha*)malloc(sizeof(TPilha));

    aux->chave = chave;
    aux->prox = *Pilha;
    *Pilha = aux;

    return;  
} 

void AchaUltPosicao(TPilha **Pilha, int n1){

    if(n1 == 1)
        return;

    if( n1 % 2 == 0 )
        inserePilha(Pilha, 0);
    else
        inserePilha(Pilha, 1);

    
    AchaUltPosicao(Pilha, (n1/2));
}

void insereHeap_UltPosicao(TNO **raiz, TPilha *Pilha, int *n, int chave){

    if(Pilha ==  NULL && *raiz == NULL){

        *raiz = (TNO*)malloc(sizeof(TNO));
        if(*raiz == NULL)
            return;

        (*raiz)->chave = chave;
        (*raiz)->dir=NULL;
        (*raiz)->esq=NULL;
        
        *n = *n + 1; 
        
        return;
    }

    if(Pilha->chave == 0)
        insereHeap_UltPosicao(&((*raiz)->esq), Pilha->prox, n, chave);
    else
        insereHeap_UltPosicao(&((*raiz)->dir), Pilha->prox, n, chave);
}

void InsereHeapMax(TNO **raiz, int *n, int chave){

    if(*raiz==NULL){

        *raiz = (TNO*)malloc(sizeof(TNO));
        if(*raiz == NULL)
            return;

        (*raiz)->chave = chave;
        (*raiz)->dir=NULL;
        (*raiz)->esq=NULL;
        
        *n = *n + 1; 
        
        return;
    }

    TPilha *Pilha = NULL;
    AchaUltPosicao(&Pilha, (*n) + 1);
    insereHeap_UltPosicao(raiz, Pilha, n, chave);
    heapifyMax_Insere(raiz, Pilha, chave);
    RemovePilha(&Pilha);
}

void InsereHeapMin(TNO **raiz, int *n, int chave){

    if(*raiz==NULL){

        *raiz = (TNO*)malloc(sizeof(TNO));
        if(*raiz == NULL)
            return;

        (*raiz)->chave = chave;
        (*raiz)->dir=NULL;
        (*raiz)->esq=NULL;
        
        *n = *n + 1; 
        
        return;
    }

    TPilha *Pilha = NULL;
    AchaUltPosicao(&Pilha, (*n) + 1);
    insereHeap_UltPosicao(raiz, Pilha, n, chave);
    heapifyMin_Insere(raiz, Pilha, chave);
    RemovePilha(&Pilha);
}

int RemoveNoHeap(TNO **raiz, TPilha *Pilha, int *n){

    if(Pilha == NULL){
        int aux = (*raiz)->chave;

        free(*raiz);
        *raiz=NULL;
        (*n) = (*n) - 1;

        //printf("\n%d\n", aux);

        return aux;
    }

    if(Pilha->chave == 0)
        RemoveNoHeap(&((*raiz)->esq), Pilha->prox, n);
    else
        RemoveNoHeap(&((*raiz)->dir), Pilha->prox, n);
}

void RemoveHeapMax(TNO **raiz, int *n){

    if(*raiz == NULL)
        return;

    TPilha *Pilha = NULL;
    AchaUltPosicao(&Pilha, (*n));
    (*raiz)->chave = RemoveNoHeap(raiz, Pilha, n);
   //printf("\n%d\n", (*raiz)->chave);
    RemovePilha(&Pilha);
    heapifyMax_Remove(raiz);
}

void RemoveHeapMin(TNO **raiz, int *n){

    if(*raiz == NULL)
        return;

    TPilha *Pilha = NULL;
    AchaUltPosicao(&Pilha, (*n));
    (*raiz)->chave = RemoveNoHeap(raiz, Pilha, n);
    //printf("\n%d\n", (*raiz)->chave);
    RemovePilha(&Pilha);
    heapifyMin_Remove(raiz);
}


void main(){

    TNO *raiz=NULL;
    int n=0;

    InsereHeapMax(&raiz, &n, 34);
    InsereHeapMax(&raiz, &n, 11);
    InsereHeapMax(&raiz, &n, 9);
    InsereHeapMax(&raiz, &n, 90);
    InsereHeapMax(&raiz, &n, 65);
    InsereHeapMax(&raiz, &n, 32);
    InsereHeapMax(&raiz, &n, 22);
    InsereHeapMax(&raiz, &n, 67);

    imprimePreOrdem(raiz);

    TNO *raiz1=NULL;
    int n1=0;

    InsereHeapMin(&raiz1, &n1, 34);
    InsereHeapMin(&raiz1, &n1, 11);
    InsereHeapMin(&raiz1, &n1, 9);
    InsereHeapMin(&raiz1, &n1, 90);
    InsereHeapMin(&raiz1, &n1, 65);
    InsereHeapMin(&raiz1, &n1, 32);
    InsereHeapMin(&raiz1, &n1, 22);
    InsereHeapMin(&raiz1, &n1, 67);

    printf("\n");
    imprimePreOrdem(raiz1);

    RemoveHeapMax(&raiz, &n);
    RemoveHeapMax(&raiz, &n);
    RemoveHeapMax(&raiz, &n);

    printf("\n");
    imprimePreOrdem(raiz);

    RemoveHeapMin(&raiz1, &n1);
    RemoveHeapMin(&raiz1, &n1);
    RemoveHeapMin(&raiz1, &n1);

    printf("\n");
    imprimePreOrdem(raiz1);   
}