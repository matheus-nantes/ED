#ifndef _LISTA_
#define _LISTA_

#define MAXCHAR 100


typedef struct _node{
    struct _node * pai;
    struct _node * esq;
    struct _node * dir;
    void * dados;
    int (* compara)(const void *a, const void *b, char param);
}no;



void montarLista(no ** raiz,char nomeArq[30]);

no * criarNO(void *  dados, int (* compara)(const void * a, const void * b, char param));

void inserirNO(no ** raiz, no * recebido, char param);

void montarKD(no **raiz, no ** indice);

void construirKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro);

int insertionSort(no**indice, no * atual, no * fim, char parametro);

void troca(no * x, no * y);

no * predecessor(no * recebido);

no * sucessor(no * recebido);

no * encontrarMaisProximo(no * raiz,no * recebido,  double (* distancia)(const void * a, const void * b, char param));

no * buscaNO(no * raiz, no * recebido, char param);

no ** kProx(int k, no * recebido,  double (*distancia)(const void * a, const void * b, char param));

void destruir(no * raiz);


#endif
