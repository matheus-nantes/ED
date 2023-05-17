#include<stdio.h>
#include<stdlib.h>
#include"kdTree.h"

void lerDados(no ** raiz,char nomeArq[30]){
    data * dados = (data*) malloc(sizeof(data));
    no * aux;
    float auxX,auxY;
    int cont = 0;
    FILE * arq;
    arq = fopen(nomeArq, "r");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
    }
    while (fscanf(arq, "%d,%[^,],%f,%f,%d,%d,%d,%d,%s\n",&(dados->codIBGE),&(dados->nome), &auxX,&auxY, &(dados->capital), &(dados->uf),&(dados->siafi),&(dados->ddd),&(dados->fuso)) !=EOF && cont <=10)
    {   
        cont ++;
        aux = criarNO(dados);
        aux->x = auxX; 
        aux->y = auxY;
        inserirNO(raiz,aux,'x');//começa no x pois o compara com o primeiro nó ( "nível x"), e depois vai intercalando entre x e y ao passar de nivel.
        dados = calloc(1, sizeof(data));
    }
    fclose(arq);
}


no * criarNO(data *  dados){
    no * aux = calloc(1,sizeof(no));
    aux->dados = dados;
    return aux;
}

void inserirNO(no ** raiz, no * recebido, char param){
    if(*raiz == NULL){
        *raiz = recebido;
        printf("\ninseriu o primeiro lugar o valor: [%f,%f]\n",recebido->x,recebido->y);
    }
    else{
        if(param == 'x'){
            if((*raiz)->x > recebido->x){//o novo nó é menor
                printf("\nX: Recebido %.6f  menor que raiz %.6f", recebido->x, (*raiz)->x);
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    printf("\nBotou na esquerda\n");
                    (*raiz)->esq = recebido;
                    recebido->pai = *raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    printf("\nChamou no FE");
                    inserirNO(&((*raiz)->esq), recebido, 'y');//invertendo o parametro, de x para y

                }
            }
            else{//o novo nó é maior ou igual á raiz
                printf("\nX: Recebido %.6f  maior que raiz %.6f", recebido->x, (*raiz)->x);
                printf("\n filhoD : %p", (*raiz)->dir);
                if((*raiz)->dir == NULL){//não tem filho a direita
                    printf("\nBotou na direita\n");
                    (*raiz)->dir = recebido;
                    recebido->pai = *raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    printf("\nChamou no FD");
                    inserirNO(&((*raiz)->dir), recebido, 'y');//invertendo o parametro, de x para y
                }
            }
        }
        else{//parametro é y
            if((*raiz)->y > recebido->y){//o novo nó é menor em y
            printf("\nY: Recebido %f  menor que raiz %f", (*raiz)->y, recebido->y);
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    printf("\nBotou na esquerda\n");
                    (*raiz)->esq = recebido;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    printf("\nChamou no FE");
                    inserirNO(&((*raiz)->esq), recebido, 'x');//invertendo o parametro, de y para x
                }
            }
            else{//o novo nó é maior ou igual á raiz
                printf("\nY: Recebido %f  maior que raiz %f", recebido->y, (*raiz)->y);
                printf("\n filhoD : %p", (*raiz)->dir);
                if((*raiz)->dir == NULL){//não tem filho a direita
                    printf("\nBotou na direita\n");
                    (*raiz)->dir = recebido;
                }
                else{//tem filho a direita, comparamos novamente
                    printf("\nChamou no FD");
                    inserirNO(&((*raiz)->dir), recebido, 'x');//invertendo o parametro, de y para x
                }

            }
        }
        //--------


    }

}
/*
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
*/
/*
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
*/
/*
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
*/



int main(){

    no * raiz = NULL;
    lerDados(&raiz,"municipios.txt");

    return 0;
}