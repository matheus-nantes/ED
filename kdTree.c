#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"kdTree.h"

no * criarNO(void *  dados, int (* compara)(const void * a, const void * b, char param)){
    no * aux = (no*)malloc(sizeof(no));
    aux->dados = dados;
    aux->dir =NULL;
    aux->esq =NULL;
    aux->pai = NULL;
    aux->compara =  compara;
    return aux;
}

void inserirNO(no ** raiz, no * recebido, char param){//x é longitude, e y é latitude
    
    recebido->esq = NULL;
    recebido->dir = NULL;
    if(*raiz == NULL){
        printf("\nPrimeiro");
        *raiz = recebido;
    }
    else{
        if(param == 'x'){
            if(recebido->compara((*raiz)->dados,recebido->dados,param) == 1){//o novo nó é maior em latitude
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
            if((*raiz)->compara((*raiz)->dados, recebido->dados,param) == 1){//o novo nó é menor em longitude
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

void montarKD(no **raiz, no ** indice){//índice é a primeira posicao da lista
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

        if(inicio->compara(inicio->dados,fim->dados,parametro)==1){//comparo os dois únicos nós da sublista, e insiro o menor, depois o maior
            //se "fim" for menor, insiro ele primeiro
            inserirNO(raiz,fim,'x');
            inserirNO(raiz,inicio,'x');
        }
        else{//senão, insiro "inicio" e depois "fim"
            inserirNO(raiz,inicio,'x');
            inserirNO(raiz,fim,'x');
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
                if(p->compara(menor->dados, p->dados,parametro)==1){//se p->dados for menor que menor->dados...
                    menor = p; //...atualizamos o menor
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

   no * aux = calloc(1, sizeof(no));//troca apenas dos valores dos nós
   aux->dados = x->dados;

   x->dados = y->dados;

   y->dados = aux->dados;
}

no * predecessor(no * recebido){
    no * p = recebido->esq;//vai pro filho a esquerda
    if(p != NULL){//se houver filho a esquerda
        while(p->dir != NULL){//enquanto houver filho a direita
            p=p->dir;//percorre até achar o predecessor (preciso verificar no retrno se não é nulo)
        }
    }
    return p;//retorna o predecessor
}

no * sucessor(no * recebido){
    no * p = recebido->dir;//vai pro filho a direita
    if(p != NULL){//se houver filho a direita
        while(p->esq != NULL){//enquanto houver filho a esquerda
            p=p->esq;//percorre até achar o sucessor
        }
    }
    return p;//retorna o predecessor (preciso verificar no retrno se não é nulo)
}


no * encontrarMaisProximo(no * raiz,no * recebido,  double (* distancia)(const void * a, const void * b, char param)){
    
    //encontrar onde o nó esta/deveria estar
    no * encontrado = buscaNO(raiz,recebido,'x');
    no * pred = NULL;
    no * suc = NULL;
    no * p = NULL; 
    //se o nó não existir, significa que o nó que foi retornado é o seu "pai",caso os valores estivessem na arvore
    if(encontrado->compara(encontrado->dados,recebido->dados,'x') != -1 && encontrado->compara(encontrado->dados, recebido->dados, 'y') != -1){//se todos os campos do "encotrado", que é o nó que a função busca nó retornou for diferente do "recebido", significa que foi retornado o pai se um nó com tais valores existisse na estrutura, ou seja, o nó mais próximo é seu pai
        return encontrado;
    }
    else{//se o nó existir na árvore, e devemos verificar dentre o antecessor ou o sucessor, qual é o mais proximo
    //pegar os dois nós mais próximos
        pred = predecessor(encontrado);
       
        suc = sucessor(encontrado);

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
            double disPred,disPredX, disPredY, disSuc, disSucX, disSucY;

            disPredX = distancia(encontrado->dados, pred->dados,'x');
            disPredY = distancia(encontrado->dados, pred->dados,'y'); 
            
            disSucX = distancia(encontrado->dados, suc->dados,'x');
            disSucY = distancia(encontrado->dados, suc->dados,'y');
            
            disPred = (disPredX*disPredX)+(disPredY*disPredY);//a^2 + b^2
            disSuc = (disSucX*disSucX)+(disSucY*disSucY);//a^2 + b^2

            disPred = sqrt(disPred);
            disSuc = sqrt(disSuc);

            if(disPred < disSuc){
                return pred;
            }
            else{
                return suc;
            }
        }
    }

}

no * buscaNO(no * raiz, no * recebido, char param){//se o nó existir, retorna ele mesmo, senão, retorn o pai que esse nó teria
    if(raiz == NULL){
        printf("Não há dados na estrutura");
    }
    else if(raiz->compara(raiz->dados,recebido->dados,'x') == -1 && raiz->compara(raiz->dados,recebido->dados,'y') == -1){//se o nó existe na arvore, ou seja, se os valores recebidos estão em algum nó na estrutura
        return raiz;
    }
    else{
        if(param == 'x'){
            if(raiz->compara(raiz->dados, recebido->dados, 'x') == 1){//o novo nó é menor
                if(raiz->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    return raiz;
                }
                else{
                    buscaNO(raiz->esq, recebido, 'y');
                }
            }
            else{//o nó é maior ou igual á raiz
                if(raiz->dir == NULL){//não tem filho a direita
                    return  raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    buscaNO(raiz->dir, recebido, 'y');//invertendo o parametro, de x para y
                }
            }
        }
        else{//parametro é y
            if(raiz->compara(raiz->dados, recebido->dados,'y') == 1){//o novo nó é menor em y
                if(raiz->esq == NULL){//se não houver filho a esquerda, enserimos lá
                    return raiz;
                }
                else{//se houver filho a esquerda, verificamos onde deve ser inserido
                    buscaNO(raiz->esq,recebido, 'x');//invertendo o parametro, de y para x
                }
            }
            else{//o novo nó é maior ou igual á raiz
                if(raiz->dir == NULL){//não tem filho a direita
                    return  raiz;
                }
                else{//tem filho a direita, comparamos novamente
                    buscaNO(raiz->dir, recebido, 'x');//invertendo o parametro, de y para x
                }

            }
        }
    }

}

no ** cincoProx(int k, no * recebido,  double (* distancia)(const void * a, const void * b, char param)){
    no ** lista =  (no**) calloc(k,sizeof(no*));
    no* pred = predecessor(recebido);
    no * suc = sucessor(recebido);
    no * pai = NULL;
    int cont = 0, contp = 0, conts = 0, metade = k/2, controle = 0;

    while(cont < k && controle < k){
        if(contp <= metade){
            if(pred != NULL){
                lista[cont] = pred;
                pred = predecessor(pred);
                contp++;
            }
        }
        if(conts < metade+1){
            if(suc != NULL){
                lista[cont] = pred;
                suc = sucessor(pred);
                conts++;
            }
        }
        controle++;
    }

    if(cont < k){
        pai = recebido->pai;
        lista[cont] = pai;
        cont ++;
    }
    return lista;
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