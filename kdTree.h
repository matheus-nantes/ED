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

void montarLista(no ** raiz,char nomeArq[30]);

no * criarNO(data *  dados);

void inserirNO(no ** raiz, no * recebido, char param);

void montarKD(no **raiz, no ** indice);

void construirKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro);

int insertionSort(no**indice, no * atual, no * fim, char parametro);

void troca(no * x, no * y);

no * encontrarMaisProximo(no * raiz, float lat, float lon);

no * buscaNO(no * raiz, float lat, float lon, char param);

float calculaDistancia(no * a, no * b);

void destruir(no * raiz);


#endif
