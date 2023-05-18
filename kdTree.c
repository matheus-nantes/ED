#include<stdio.h>
#include<stdlib.h>
#include"kdTree.h"

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
    while (fscanf(arq, "%d,%[^,],%f,%f,%d,%d,%d,%d,%s\n",&(dados->codIBGE),&(dados->nome), &auxX,&auxY, &(dados->capital), &(dados->uf),&(dados->siafi),&(dados->ddd),&(dados->fuso)) !=EOF)
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

no * criarNO(data *  dados){
    no * aux = calloc(1, sizeof(no));
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
            printf("\nY: Recebido %f  menor que raiz %f",recebido->y, (*raiz)->y);
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    printf("\nBotou na esquerda\n");
                    (*raiz)->esq = recebido;
                    recebido->pai = *raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    printf("\nChamou no FE");
                    inserirNO(&((*raiz)->esq), recebido, 'x');//invertendo o parametro, de y para x
                }
            }
            else{//o novo nó é maior ou igual á raiz
                printf("\nY: Recebido %f  maior que raiz %f", recebido->y, (*raiz)->y);
                if((*raiz)->dir == NULL){//não tem filho a direita
                    printf("\nBotou na direita\n");
                    (*raiz)->dir = recebido;
                    recebido->pai = *raiz;
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

void montarKD(no **raiz, no ** indice){
    no * p = *indice;
    while(p->dir != NULL){
        p=p->dir;
    }
    //organiza e cria recursivamente a KDTREE "balanceada"
    organizarKD(raiz, indice, *indice, p, 'x');
    
}

void organizarKD(no ** raiz, no ** indice, no * inicio, no * fim, char parametro){
    
    no * fimProx = NULL;
    no * inicioProx = NULL;
    //printf("\n------Comparando de [%f, %f] até [%f %f]------",inicio->x,inicio->y,fim->x,fim->y);
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
            printf("\nentrou aqui");
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
        printf("\nNó solitário em sublista");
        inserirNO(raiz,inicio,'x');//insiro o único nó restante na sublista
    }
    else{//se há mais de um valor na metade recebida, devemos achar a mediana
        //ordenar
        int total = insertionSort(indice, inicio, fim, parametro);
        printf("\ntotal: %d", total);
        int meio = total/2;
        no * mediana = (no*)malloc(sizeof(no));

        no * p = inicio;
        
        //achar mediana

        for(int i = 0; i < meio; i++){
            p=p->dir;
        }
        mediana = p;//guarda o endereço que vai ser inserido
        printf("\n\n%d ",meio);
        fimProx = mediana->pai;
        inicioProx = mediana->dir;
        fimProx->dir = inicioProx;//ou pai->dir = mediana->dir
        //inserir valor médio
        printf("\nInserir Mediana: [%f, %f]",mediana->x,mediana->y);
        mediana->pai = NULL;//zera os campos de referencia do nó a ser inserido
        mediana->dir = NULL;
        mediana->esq = NULL;
        inserirNO(raiz,mediana,'x');//não podemos usar mais o endereço mediana, pois agora ele pertence á KDTREE

        //repetir
        if(parametro == 'x'){
            printf("------Let's ESQ: comparar de [%f, %f] até [%f %f]------\n",inicio->x,inicio->y,fimProx->x,fimProx->y);
            organizarKD(raiz, indice, inicio,fimProx,'y');//organiza a metade a esquerda
            
            printf("------Let's DIR: comparar de [%f, %f] até [%f %f]------\n",inicioProx->x,inicioProx->y,fim->x,fim->y);
            organizarKD(raiz,indice,inicioProx,fim,'y');//organiza a metade a direita
        }
        else{
            printf("------Let's ESQ: comparar de [%f, %f] até [%f %f]------\n",inicio->x,inicio->y,fimProx->x,fimProx->y);
            organizarKD(raiz, indice, inicio,fimProx,'x');//organiza a metade a direita
            
            printf("------let's DIR: comparar de [%f, %f] até [%f %f]------\n",inicioProx->x,inicioProx->y,fim->x,fim->y);
            organizarKD(raiz,indice,inicioProx,fim,'x');
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
            if(parametro == 'x'){
                printf("[ * %f * , %f]\n ",atual->x,atual->y);
            }
            else{
                printf("[%f,  * %f * ]\n ",atual->x,atual->y);
            }
            cont ++;
            atual = atual->dir;
        }
        else{
    }
    }
    if(parametro == 'x'){
        printf("[ * %f * , %f]\n ",atual->x,atual->y);
    }
    else{
        printf("[%f,  * %f * ]\n ",atual->x,atual->y);
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

    no * indiceLista = NULL;
    montarLista(&indiceLista,"municipios.txt");

    no * raiz = NULL;
    montarKD(&raiz, &indiceLista);

    printf("\nCabou");

    return 0;
}