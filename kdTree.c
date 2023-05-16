#include<stdio.h>
#include<stdlib.h>
#include"kdTree.h"

no * criarNO(data *  dados){
    no * aux = calloc(1,sizeof(no));
    aux->dados = dados;
    aux->x = dados->x;
    aux->y = dados->y;
    //printf("%d",((data *)(aux->dados))->val);
    return aux;
}

void inserirNO(no ** raiz, no * recebido){
    printf("\nBora inserir");
    if(*raiz == NULL){
        printf("\nta nula");
        *raiz = recebido;
        printf("\ninseriu o primeiro lugar");
    }
    else{
        printf("Valores: %p raiz: %.0f |  %p recebido %.0f", *raiz, (*raiz)->x,recebido, recebido->x);
        if((*raiz)->x > recebido->x){//o novo nó é menor
            printf("\nRecebido %f  é menor que raiz %f", (*raiz)->x, recebido->x);
            if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                printf("\nBotou na esquerda");
                (*raiz)->esq = recebido;
            }
            else{//se houver filho a esquerda, verificamos onde deve ser inserido
                printf("\nChamou no FE");
                inserirNO(&((*raiz)->esq), recebido);
            }
        }
        else{//o novo nó é maior ou igual á raiz
            printf("\nRecebido %f  é maior que raiz %f", recebido->x, (*raiz)->x);
            printf("\n filhoD : %p", (*raiz)->dir);
            if((*raiz)->dir == NULL){//não tem filho a direita
                printf("\nBotou na direita");
                (*raiz)->dir = recebido;
            }
            else{//tem filho a direita, comparamos novamente
                printf("\nChamou no FD");
                inserirNO(&((*raiz)->dir), recebido);
            }

        }
    }

}



int main(){

    //criando raiz
    no * raiz = NULL;

    data * dados = malloc(sizeof(data));
    dados->x = 10;
    dados->y = 10;
    dados->val = 10;
    //salvou os dados

    no * criado = criarNO(dados);//criou um novo nó

    inserirNO(&raiz, criado);
    printf("\nCabou");
    printf("+++%p+++\n", raiz);

    printf("--%d--\n", ((data *)(raiz->dados))->val);

    dados = calloc(1,sizeof(data));
    dados->x = 11;
    dados->y = 11;
    dados->val = 21;
    criado = criarNO(dados);//criou um novo nó
    inserirNO(&raiz, criado);
    printf("\nCabou");
    printf("+++%p+++\n", raiz);

    dados = calloc(1,sizeof(data));
    dados->x = 9;
    dados->y = 9;
    dados->val = 9;
    criado = criarNO(dados);//criou um novo nó
    inserirNO(&raiz, criado);
    printf("+++%p+++\n", raiz);

    dados = calloc(1,sizeof(data));
    dados->x = 12;
    dados->y = 12;
    dados->val =22;
    criado = criarNO(dados);//criou um novo nó
    inserirNO(&raiz, criado);
    printf("+++%p+++\n", raiz);


    return 0;
}