#ifndef _LISTA_
#define _LISTA_

typedef struct data{
    double x;
    double y;
    int val;
}data;

typedef struct _node{
    double x;
    double y;
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

coordenadas * lerDados(char nomeArq[20]);

no * criarNO(data *  dados);

void inserirNO(no ** raiz, no * recebido, char param);

void balancear(no ** raiz, coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro);

int ordenar(coordenadas ** lista, coordenadas * inicio, coordenadas * fim, char parametro);

no * contruirKDTREE(coordenadas * lista);


#endif
