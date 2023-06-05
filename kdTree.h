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



void montarLista(no ** raiz,char nomeArq[30]);//métood usado para criar uma "lista encadeada" de nós, para que possa ser encontrada a mediana do conjunto de valores. Os nós desta lista são transferidos para a árvore, por isso não há a necessidade de dar free neles

no * criarNO(void *  dados, int (* compara)(const void * a, const void * b, char param));//cria um nó

void inserirNO(no ** raiz, no * recebido, char param);//insere um nó na árvore, nó este que é a mediana

void montarKD(no **raiz, no ** indice);//encontra o fim da lista encadeada e passa para o método construirKD< que é onde a magia acontece

void construirKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro);//através dos métodos insertionSort, inserirNO e troca, este método encontra a mediana, insere na árvore, remove da lista encadeada, subdivide a lista em dois subconjuntos e chama recursivamente ele mesmo nos subconjuntos da esquerda e direita, até que todos os nós seja inserido na árvore

int insertionSort(no**indice, no * atual, no * fim, char parametro);//método de ordenação adaptado para uma lista encadeada de nós

void troca(no * x, no * y);//troca os VALORES de dois nós

no * predecessor(no * recebido);//encontra o predecessor de um nó informado

no * sucessor(no * recebido);//encontra o sucessor do nó informado

no * encontrarMaisProximo(no * raiz,no * recebido,  double (* distancia)(const void * a, const void * b, char param));//encontra o nó mais próximo de uma coordenada informada. Se a cordenada pertencer á um nó na estrutura, ele encontra o nó mais próximo entre seu predecessor ou sucessor. Senão, encontra o pai dessas coordenadas, caso elas  estivessem na estrutura, que é o nó mais próximo mais provável neste caso

no * buscaNO(no * raiz, no * recebido, char param);//encontra um nó de acordo com as coordenadas passadas. Se as coordenadas existirem na árvore, retorna o nó que as possui, senão, retorna o pai dessas coordenadas caso elas estivessem na estrutura

no ** kProx(int k, no * recebido,  double (*distancia)(const void * a, const void * b, char param));//busca os k vizinhos mais próximos de uma coordenada fornecida

void destruir(no * raiz);//destrói toda a estrutura


#endif
