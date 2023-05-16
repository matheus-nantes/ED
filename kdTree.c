#include<stdio.h>
#include<stdlib.h>
#include"kdTree.h"

coordenadas * lerDados(char nomeArq[20]){
    float x, y;
    coordenadas * lista = NULL;
    coordenadas * aux;
    coordenadas * p;
    FILE * arq;
    arq = fopen("dados.txt", "r");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
    }
    int result;
    while (fscanf(arq, "%f %f\n",&x, &y) !=EOF)
    {   
        aux = calloc(1, sizeof(coordenadas));
        aux->x = x;
        aux->y = y;

        if(lista == NULL){
         lista = aux;
        }
        else{
            p = lista;

            while(p->prox != NULL){
                p = p->prox;
            }
            p->prox = aux;
        }
    }
    fclose(arq);
    return lista;
}


no * criarNO(data *  dados){
    no * aux = calloc(1,sizeof(no));
    aux->dados = dados;
    aux->x = dados->x;
    aux->y = dados->y;
    //printf("%d",((data *)(aux->dados))->val);
    return aux;
}

void inserirNO(no ** raiz, no * recebido, char param){
    printf("\nBora inserir");
    if(*raiz == NULL){
        printf("\nta nula");
        *raiz = recebido;
        printf("\ninseriu o primeiro lugar");
    }
    else{
        printf("Parametro %c | Valores: %p raiz: %.0f |  %p recebido %.0f",param, *raiz, (*raiz)->x,recebido, recebido->x);
        if(param == 'x'){
            if((*raiz)->x > recebido->x){//o novo nó é menor
                printf("\nRecebido %f  é menor que raiz %f", (*raiz)->x, recebido->x);
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    printf("\nBotou na esquerda");
                    (*raiz)->esq = recebido;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    printf("\nChamou no FE");
                    if(param == 'x'){
                        inserirNO(&((*raiz)->esq), recebido, 'y');
                    }
                    else{
                        inserirNO(&((*raiz)->esq), recebido, 'x');
                    }
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
                    if(param == 'x'){
                    inserirNO(&((*raiz)->dir), recebido, 'y');
                    }
                    else{
                        inserirNO(&((*raiz)->dir), recebido, 'x');
                    }
                }

            }
        }
        //-----------
        else{
            if((*raiz)->y > recebido->y){//o novo nó é menor
            printf("\nRecebido %f  é menor que raiz %f", (*raiz)->x, recebido->x);
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    printf("\nBotou na esquerda");
                    (*raiz)->esq = recebido;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    printf("\nChamou no FE");
                    if(param == 'x'){
                        inserirNO(&((*raiz)->esq), recebido, 'y');
                    }
                    else{
                        inserirNO(&((*raiz)->esq), recebido, 'x');
                    }
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
                    if(param == 'x'){
                    inserirNO(&((*raiz)->dir), recebido, 'y');
                    }
                    else{
                        inserirNO(&((*raiz)->dir), recebido, 'x');
                    }
                }

            }
        }
        //--------


    }

}

void balancear(no ** raiz, coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro){//recebe a lista a ser ordenada, e qual o valor a ser comparado ( x ou y)
    printf("Bora balancear\n");
    int meio = ordenar(lista, inicio, fim, parametro);
    printf("Ordenou\n");

    coordenadas * p = inicio;
    coordenadas * antP= NULL;
    printf("\n");
    while(p != NULL){
        printf("X: %.0f|Y: %.0f\n", p->x, p->y);
        p= p->prox;
    }
    p=inicio;
    printf("\nmeio === %d\n",meio);
    for(int i = 0; i < meio-1; i++){
        antP = p;
        p = p->prox;
    }
    printf("elemento central: [%f,%f]",p->x, p->y);
    printf("\n Criar nó vazio");
    data * dados = NULL;
    dados = calloc(1, sizeof(data));
    printf("\n Criamos o novo nó");
    dados->x = p->x;
    dados->y = p->y;
    printf("\n Alteramos valores do novo nó");

    no * temp;
    temp = criarNO(dados);
    inserirNO(raiz,temp, parametro);
    
    if(parametro =='x'){
        balancear(raiz, lista, inicio,antP, 'y');
        balancear(raiz, lista, p->prox,fim, 'y');

    }
    else{
        balancear(raiz, lista, inicio,antP, 'x');
        balancear(raiz, lista, p->prox,fim, 'x');

    }
    
}

int ordenar(coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro){
    coordenadas * menor;
    coordenadas * aux = calloc(1,sizeof(coordenadas));
    coordenadas * p = inicio;
    coordenadas * q;
    int contador = 2;
    while(p != fim){//bubble sort
        contador++;
        q = p->prox;
        menor = p;
        printf("p: [%f, %f] | q: [%f, %f]\n", p->x,p->y,q->x,q->y);
        while(q != fim->prox){
            if(parametro == 'x'){
                if(q->x < menor->x){
                    menor = q;
                }
            }
            else{
                if(q->y < menor->y){
                    menor = q;
                }
            }
            q=q->prox;
        }
        printf("trocando [%f, %f] com [%f, %f]\n", p->x, p->y,menor->x, menor->y);
        aux->x = p->x;
        aux->y = p->y;

        p->x = menor->x;
        p->y = menor->y;

        menor->x = aux->x;
        menor->y = aux->y;
        p = p->prox;
        free(aux);
    }//fim do bubble sort
    return (int)((contador/2)+0.5);
}


no * contruirKDTREE(coordenadas * lista){
    no * raiz;
    coordenadas * inicio;
    coordenadas * fim; 
    inicio = lista;
    fim = lista;
    printf("Contruir KDTREE\n");

    while(fim->prox != NULL){
        fim = fim->prox;
    }    
    printf("Achou o fim\n");
    
    balancear(&raiz,&lista,inicio,fim, 'x');
    return raiz;
}




int main(){

    //criando raiz
    no * raiz = NULL;

    //data * dados = malloc(sizeof(data));
    //dados->x = 10;
    //dados->y = 10;
   // dados->val = 10;
    //salvou os dados

    //no * criado = criarNO(dados);//criou um novo nó

    //inserirNO(&raiz, criado);
    //printf("\nCabou");
    //printf("+++%p+++\n", raiz);
    
    coordenadas * lista = lerDados("dados.txt");
    printf("Criar KDTREE\n");
    raiz = contruirKDTREE(lista);

    return 0;
}