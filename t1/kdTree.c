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
        *raiz = recebido;
    }
    else{
        if(param == 'x'){
            if(recebido->compara((*raiz)->dados,recebido->dados,param) == 1){//o novo nó é maior em latitude
                if((*raiz)->esq == NULL){//se não houver filho a esquerda, inserimos lá
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
        inicio->pai = NULL;//zera os campos de referencia do nó a ser inserido
        inicio->dir = NULL;
        inicio->esq = NULL;

        fim->pai = NULL;//zera os campos de referencia do outro nó a ser inserido
        fim->dir = NULL;
        fim->esq = NULL;

        if(inicio->compara(inicio->dados,fim->dados,parametro)==1){//comparo os dois únicos nós da sublista, e insiro o menor, depois o maior
            //se "fim" for menor, insiro ele primeiro, depois "fim"
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
            if(atual != menor){//se o elemento "selecionado" não for o menor do subconjunto a direita dele...
                troca(atual, menor);//troca ele de posição com o menor elemento do subconjunto, fazendo com que a lista fique ordenada crescentemente
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
    if(recebido!=NULL && recebido->esq != NULL){
        no * p = recebido->esq;//vai pro filho a esquerda
        while(p->dir != NULL){//enquanto houver filho a direita
            p=p->dir;//percorre até achar o predecessor (preciso verificar no retorno se não é nulo)
        }
        return p;//retorna o predecessor
    }
    else{
        return NULL;
    }
}

no * sucessor(no * recebido){
    if(recebido != NULL && recebido->dir != NULL){
        no * p = recebido->dir;//vai pro filho a direita
        while(p->esq != NULL){//enquanto houver filho a esquerda
            p=p->esq;//percorre até achar o sucessor
        }
        return p;//retorna o predecessor (preciso verificar no retrno se não é nulo)
    }
    else{
        return NULL;
    }
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

no * buscaNO(no * raiz, no * recebido, char param){//se o nó existir, retorna ele mesmo, senão, retorna o pai que esse nó teria
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

no ** kProx(int k,no * recebido,  double (* distancia)(const void * a, const void * b, char param)){
    no ** lista =  (no**) calloc(k,sizeof(no*));
    no * pai = NULL;
    int contTotal = 0, contp = 0, conts = 0, metade = k/2, controle = 0;
    no * pred = predecessor(recebido);
    no * suc = sucessor(recebido);

    
    if(pred != NULL){//se possuir predecessor
        lista[contTotal++] = pred;//adiciona ele
        while(pred->pai != recebido && contp < metade){//enquanto o predecessor não for o filho imediatamente á esquerda do "recebido" e não tiver atingido o "limite de predecessores"(no caso ideal, metade da lista é de predecessores e metade de sucessores)
            pred = pred->pai;//avança o predecessor um "nível" á cima
            lista[contTotal++] = pred;//adicona "novo predecessor"
            contp++;//aumenta a "quantidade de predecessores"
        }
    }

    if(suc != NULL){//se houver sucessor
        lista[contTotal++] = suc;//adiciona ele
        while(suc->pai != recebido && conts < metade){//enquanto o sucessor não for o filho imediatamente á direita do recebido e não tiver atingido o "limite de sucessores"
            suc = suc->pai;//avança o sucessor "um nível acima"
            lista[contTotal++] = suc;//adiciona o "novo sucessor"
            conts++;//aumenta a "quantidade de sucessores"
        }
    }

    if(pred != NULL){
        while(contTotal < k && pred->pai != recebido){//se ainda faltar elementos na lista, e houver predecessores para inserir
            pred = pred->pai;//subimos um nível novamente
            lista[contTotal++] = pred;
        }
    }

    if(suc != NULL){
        while(contTotal < k && suc->pai != recebido){//se ainda faltar elementos na lista, e ainda houver sucessor para inserir
            suc = suc->pai;//subimos um nível noevamente
            lista[contTotal++] = suc;
        }
    }
    
    //se faltar elementos e não houver mais nenhum descendente do nó para inserir na lista, subimos a busca em um nível
    while(contTotal < k){//este while faz com que a "subida de nível do recebido" seja realizada enquanto for preciso
        if(recebido->pai != NULL){//se não for a raiz
            pai = recebido->pai;
            lista[contTotal++] = pai;//adicionamos o pai á lista

            if(pai->esq == recebido){//se o recebido é um filho a esquerda, devemos procurar na subárvore á direita
                if(pai->dir != NULL){//se houver irmão
                    lista[contTotal++] = pai->dir;//adicionamos o irmão
                    recebido = pai->dir;//atualizamos o "recebido", para que a busca seja realizada agora na subarvore do irmão

                    pred = predecessor(recebido);

                    suc = sucessor(recebido);

                    if(pred != NULL){//se o irmão possuir predecessor
                        lista[contTotal++] = pred;//adicionamos ele
                        while(pred->pai != recebido && contTotal<k){//e continuamos procurando nos predecessores, subindo de nível, enquanto for possível e preciso
                            pred = pred->pai;
                            lista[contTotal++] = pred;
                        }
                    }

                    if(suc != NULL){    //se o irmão possuir sucessor
                        lista[contTotal++] = suc;//adiconamos ele
                        while(suc->pai != recebido && contTotal<k){//e continuamos inserindo os sucessores, enquanto for preciso e possível
                            suc = suc->pai;
                            lista[contTotal++] = suc;
                        }
                    }

                }

            }
            else{//o recebido é um filho a direita

                //os casos deste else são os mesmos do "seu if correspondente"

                if(pai->esq != NULL){//se houver irmão
                    lista[contTotal++] = pai->esq;//adicionamos o irmão
                    recebido = pai->esq;//atualizamos o "recebido", para que a busca seja realizada agora na subarvore do irmão

                    pred = predecessor(recebido);

                    suc = sucessor(recebido);

                    if(pred != NULL){
                        lista[contTotal++] = pred;
                        while(pred->pai != recebido && contTotal<k){
                            pred = pred->pai;
                            lista[contTotal++] = pred;
                        }
                    }

                    if(suc != NULL){    
                        lista[contTotal++] = suc;
                        while(suc->pai != recebido && contTotal<k){
                            suc = suc->pai;
                            lista[contTotal++] = suc;
                        }
                    }

                }

            }
        }
    }
    return lista;  //após todas essas operações retorna a lista com os k vizinhos mais próximos
}

void destruir(no * raiz){
    if(raiz->esq != NULL){//procura nó folha pela esquerda
         destruir(raiz->esq);
    }
    if(raiz->dir != NULL){
        destruir(raiz->dir);//procura nó folha pela direita
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);//se chegar em um nó folha o exclui. Através da recursão, vem excluindo tudo de baixo pra cima
    }
}