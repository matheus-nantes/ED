#include<stdlib.h>
#include<stdio.h>
#include "kdTree.h"

void montarLista(no ** indice,char nomeArq[30]){
    data * dados = (data*) malloc(sizeof(data));
    no * aux;
    no * p = NULL;
    float auxX,auxY;
    int cont = 0;
    FILE * arq;
    arq = fopen(nomeArq, "r");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
    }
    while (fscanf(arq, "%d,%[^,],%f,%f,%d,%d,%d,%d,%s\n",&(dados->codIBGE),&(dados->nome), &auxX,&auxY, &(dados->capital), &(dados->uf),&(dados->siafi),&(dados->ddd),&(dados->fuso)) !=EOF && cont < 10)
    {   
        cont ++;
        aux = criarNO(dados);
        aux->x = auxX; 
        aux->y = auxY;
        
        if(*indice == NULL){
            *indice = aux;
            aux -> pai = NULL;
        }
        else{
            p = *indice;
            while(p->dir != NULL){//procura a "ultima" posicao da lista
                p = p->dir;
            }
            p->dir = aux;
            aux->pai = p;
        }
        dados = (data *)malloc(sizeof(data));
    }
    fclose(arq);
}


int main(){

    no * indiceLista = NULL;
    montarLista(&indiceLista,"municipios.txt");

    no * raiz = NULL;
    montarKD(&raiz, &indiceLista);

    printf("\nArvore construida");

    int input = 0;
    while(input != -1){
        printf("\nEscollha um opcao:\n1-Mostrar mais proxima\n2-Mostrar as 5 mais proximas\n3-Encerrar\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                printf("\nInformar as coordenadas, no formato 'latitude longitude'\n");
                float lat, lon;
                scanf("%f %f",&lat,&lon);
                no * encontrado = encontrarMaisProximo(raiz,lat,lon);
                printf("\nValores achado: [%f,%f]",encontrado->x,encontrado->y);
                break;
            case 2:
                printf("Informar as coordenadas, no formato 'latitude longitude'");
                break;
            case 3:
                destruir(raiz);
                free(raiz);
                input=-1;  
                printf("\nArvore destruida");              
                break;
            default:
                printf("\nOpcao invalida");
                break;
        }
    }

    return 0;
}