#ifndef _LISTA_
#define _LISTA_

typedef struct data{
    int codIBGE;
    char nome[100];
    int capital;
    int uf;
    int siafi;
    int ddd;
    char fuso[100];
}data;

typedef struct _node{
    float x;
    float y;
    struct _node * pai;
    struct _node * esq;
    struct _node * dir;
    void * dados;
}no;

typedef struct _coord{
    double x;
    double y;
    struct _coord * prox;
}coordenadas;

void lerDados(no ** raiz,char nomeArq[30]);

no * criarNO(data *  dados);

void inserirNO(no ** raiz, no * recebido, char param);

void balancear(no ** raiz, coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro);

int ordenar(coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro);

no * contruirKDTREE(coordenadas * lista);


#endif
