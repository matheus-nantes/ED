#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"kdTree.h"

no * criarNO(data *  dados){
    no * aux = (no*)malloc(sizeof(no));
    aux->dados = dados;
    aux->dir =NULL;
    aux->esq =NULL;
    aux->pai = NULL;
    return aux;
}

//inserirNO(raiz,aux,'x');//começa no x pois o compara com o primeiro nó ( "nível x"), e depois vai intercalando entre x e y ao passar de nivel.     
void inserirNO(no ** raiz, no * recebido, char param){
    if(*raiz == NULL){
        *raiz = recebido;
    }
    else{
        if(param == 'x'){
            if((*raiz)->x > recebido->x){//o novo nó é menor
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    (*raiz)->esq = recebido;
                    recebido->pai = *raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    inserirNO(&((*raiz)->esq), recebido, 'y');//invertendo o parametro, de x para y

                }
            }
            else{//o novo nó é maior ou igual á raiz
                if((*raiz)->dir == NULL){//não tem filho a direita
                    (*raiz)->dir = recebido;
                    recebido->pai = *raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    inserirNO(&((*raiz)->dir), recebido, 'y');//invertendo o parametro, de x para y
                }
            }
        }
        else{//parametro é y
            if((*raiz)->y > recebido->y){//o novo nó é menor em y
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    (*raiz)->esq = recebido;
                    recebido->pai = *raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    inserirNO(&((*raiz)->esq), recebido, 'x');//invertendo o parametro, de y para x
                }
            }
            else{//o novo nó é maior ou igual á raiz
                if((*raiz)->dir == NULL){//não tem filho a direita
                    (*raiz)->dir = recebido;
                    recebido->pai = *raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    inserirNO(&((*raiz)->dir), recebido, 'x');//invertendo o parametro, de y para x
                }
            }
        }
    }
}

void montarKD(no **raiz, no ** indice){
    no * p = *indice;
    while(p->dir != NULL){//acha o fim da lista
        p=p->dir;
    }
    //organiza e cria recursivamente a KDTREE "balanceada"
    construirKD(raiz, indice, *indice, p, 'x');
    
}

void construirKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro){
    
    no * fimProx = NULL;
    no * inicioProx = NULL;
    if(inicio->dir == fim){
        inicio->pai = NULL;//zera os campos de referencia dos nózes a ser inserido
        inicio->dir = NULL;
        inicio->esq = NULL;

        fim->pai = NULL;//zera os campos de referencia dos nózes a ser inserido
        fim->dir = NULL;
        fim->esq = NULL;
        if(parametro=='x'){
            if(inicio->x < fim->x){//comparo os dois únicos nós da sublista, e insiro o menor, depois o maior
                
                inserirNO(raiz,inicio,'x');
                inserirNO(raiz,fim,'x');
            }
            else{
                inserirNO(raiz,fim,'x');
                inserirNO(raiz,inicio,'x');
            }
        }
        else{
            if(inicio->y < fim->y){
                inserirNO(raiz,inicio,'x');
                inserirNO(raiz,fim,'x');
            }
            else{
                inserirNO(raiz,fim,'x');
                inserirNO(raiz,inicio,'x');
            }
        }
    }
    else if(inicio == fim){
        inserirNO(raiz,inicio,'x');//insiro o único nó restante na sublista
    }
    else{//se há mais de um valor na metade recebida, devemos achar a mediana
        //ordenar
        int total = insertionSort(indice, inicio, fim, parametro);
        int meio = total/2;
        no * mediana = (no*)malloc(sizeof(no));

        no * p = inicio;
        
        //achar mediana

        for(int i = 0; i < meio; i++){
            p=p->dir;
        }
        mediana = p;//guarda o endereço que vai ser inserido
        fimProx = mediana->pai;
        inicioProx = mediana->dir;
        fimProx->dir = inicioProx;//ou pai->dir = mediana->dir
        //inserir valor médio
        mediana->pai = NULL;//zera os campos de referencia do nó a ser inserido
        mediana->dir = NULL;
        mediana->esq = NULL;
        inserirNO(raiz,mediana,'x');//não podemos usar mais o endereço mediana, pois agora ele pertence á KDTREE

        //repetir
        if(parametro == 'x'){
            construirKD(raiz, indice, inicio,fimProx,'y');//organiza a metade a esquerda em y
            construirKD(raiz,indice,inicioProx,fim,'y');//organiza a metade a direita em y
        }
        else{
            construirKD(raiz, indice, inicio,fimProx,'x');//organiza a metade a esquerda em x
            
            construirKD(raiz,indice,inicioProx,fim,'x');//organiza a metade a direita em x
        }
    }
}

int insertionSort(no**indice, no * atual, no * fim, char parametro){
    no * menor;
    no * prox = NULL;
    no * p = NULL;
    int cont = 1;
    while(atual != fim){
        menor = atual;
        p = atual->dir;
        if(fim != NULL){
            while(p != fim->dir){
                if(parametro == 'x'){
                    if(p->x < menor->x){
                        menor = p;
                    }
                }
                else{
                    if(p->y < menor->y){
                        menor = p;
                    }
                }
                p = p->dir;
            }
            if(atual != menor){
                troca(atual, menor);
            }
            cont ++;
            atual = atual->dir;
        }
    }
    return cont;
}

void troca(no * x, no * y){

   no * aux = calloc(1, sizeof(no));
   aux->x = x->x;
   aux->y = x->y;
   aux->dados = (data*)x->dados;

   x->x = y->x;
   x->y = y->y;
   x->dados = (data*)y->dados;

   y->x = aux->x;
   y->y = aux->y;
   y->dados = (data*)aux->dados;

    free(aux);
}

float calculaDistancia(no * a, no * b){//a é o que esta sendo procurado
    float x = a->x - b->x;
    float y = a->y - b->y;
    x = x*x;
    y = y*y;
    return sqrt(x+y);
}

no * encontrarMaisProximo(no * raiz,float lat, float lon){
    
    //encontrar onde o nó esta/deveria estar
    no * encontrado = buscaNO(raiz,lat,lon,'x');
    no * pred = NULL;
    no * suc = NULL;
    no * p = NULL; 
    //se o nó não existir, significa que o nó que foi retornado é o seu "pai",caso os valores estivessem na arvore
    if(encontrado->x != lat && encontrado->y != lon){
        return encontrado;
    }
    else{//se o nó existir na árvore, e devemos verificar dentre o antecessor ou o sucessor, qual é o mais proximo
    //pegar os dois nós mais próximos
        if(encontrado->esq != NULL){//o nó possui filho a esquerda
            p = encontrado->esq;
            while(p->dir!=NULL){//procuramos o predecessor
                p = p->dir;
            }
            pred = p;
        }
        if(encontrado->dir != NULL){//o nó possui filho a direita
            p = encontrado->dir;
            while(p->esq != NULL){//procuramos o sucessor
                p = p->esq;
            }
            suc = p;
        }
        if(pred == NULL && suc == NULL){//se o nó não possui nem predecessor, nem sucessor, retornamos o pai
            return encontrado->pai;
        }
        else if(pred == NULL && suc != NULL){//se o nó só possui sucessor
            return suc;
        }
        else if(pred != NULL && suc == NULL){//se o nó só possui predecessor
            return pred;
        }
        else{//descobrir qual é o menor
            float disPred, disSuc;
            disPred = calculaDistancia(encontrado,pred);
            disSuc = calculaDistancia(encontrado,suc);
            if(disPred < disSuc){
                return pred;
            }
            else{
                return suc;
            }
        }
    }

}

no * buscaNO(no * raiz, float lat, float lon, char param){//se o nó existir, retorna ele mesmo, senão, retorn o pai que esse nó teria
    if(raiz == NULL){
        printf("Não há dados na estrutura");
    }
    else if(raiz->x == lat && raiz->y == lon){
        return raiz;
    }
    else{
        if(param == 'x'){
            if(raiz->x > lat){//o novo nó é menor
                if(raiz->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    return raiz;
                }
                else{
                    buscaNO(raiz->esq, lat,lon, 'y');
                }
            }
            else{//o nó é maior ou igual á raiz
                if(raiz->dir == NULL){//não tem filho a direita
                    return  raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    buscaNO(raiz->dir, lat,lon, 'y');//invertendo o parametro, de x para y
                }
            }
        }
        else{//parametro é y
            if(raiz->y > lon){//o novo nó é menor em y
                if(raiz->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    return raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    buscaNO(raiz->esq, lat,lon, 'x');//invertendo o parametro, de y para x
                }
            }
            else{//o novo nó é maior ou igual á raiz
                if(raiz->dir == NULL){//não tem filho a direita
                    return  raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    buscaNO(raiz->dir, lat,lon, 'x');//invertendo o parametro, de y para x
                }

            }
        }
    }

}

void destruir(no * raiz){
    if(raiz->esq != NULL){
         destruir(raiz->esq);
    }
    if(raiz->dir != NULL){
        destruir(raiz->dir);
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
    }
}