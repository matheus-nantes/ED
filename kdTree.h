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


no * criarNO(data *  dados);

void inserirNO(no ** raiz, no * recebido);


#endif
