#ifndef _LISTA_
#define _LISTA_

#define MAXCHAR 100


typedef struct data{
    int codIBGE;
    char nome[MAXCHAR];
    int capital;
    int uf;
    int siafi;
    int ddd;
    char fuso[100];
}data;

typedef struct fastFood{
    int id;
    char address[MAXCHAR];
    char categories[MAXCHAR];
    char city[MAXCHAR];
    char country[MAXCHAR];
    char name[MAXCHAR];
    int postalCode;
    char province[MAXCHAR];
    char websites[2000];
} fastFood;

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

no * criarNO(void *  dados);

void inserirNO(no ** raiz, no * recebido, char param);

void montarKD(no **raiz, no ** indice);

void construirKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro);

int insertionSort(no**indice, no * atual, no * fim, char parametro);

void troca(no * x, no * y);

no * encontrarMaisProximo(no * raiz, float lat, float lon);

no * buscaNO(no * raiz, float lat, float lon, char param);

float calculaDistancia(no * a, no * b);

no * cincoProx(no * recebido);

void destruir(no * raiz);


#endif
