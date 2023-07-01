#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "kdTree.h"

typedef struct cidade{
    int codIBGE;
    float latitude;
    float longitude;
    char nome[MAXCHAR];
    int capital;
    int uf;
    int siafi;
    int ddd;
    char fuso[100];
}cidade;

int compara_cidade(const void *a, const void *b, char param){
    cidade * a1;
    cidade * a2;
    a1 = (cidade *) a;
    a2 = (cidade *) b;
    float result = 0;
    if(param=='x'){//se for latitude
        result = (a1->latitude) - (a2->latitude);
    }
    else{
        result = (a1->longitude) - (a2->longitude);
    }
    if(result < -0.1){//se a2 for maior a1, retorna 0
        return 0;
    }
    else if(result >= -0.1 && result <= 0.1){//se for igual(com  um margem de "aproximação" mais ou menos 0.001) retorna -1
        return -1;
    }
    else{//se for menor retorna 1
        return 1;
    }
}

double distancia_cidade(const void *a, const void *b, char param){
    cidade * a1;
    cidade * a2;
    a1 = (cidade *) a;
    a2 = (cidade *) b;
    float result = 0;
    if(param=='x'){//se for latitude
        result = (a1->latitude) - (a2->latitude);
    }
    else{
        result = (a1->longitude) - (a2->longitude);
    }
    return result;
}


typedef struct fastFood{
    int id;
    float latitude;
    float longitude;
    char address[MAXCHAR];
    char city[MAXCHAR];
    char country[MAXCHAR];
    char name[MAXCHAR];
    char postalCode[100];
    char province[MAXCHAR];
    char websites[2000];
} fastFood;

int compara_fastfood(const void *a, const void * b, char param){
    fastFood * a1;
    fastFood * a2;
    a1 = (fastFood *) a;
    a2 = (fastFood *) b;
    float result = 0;
    if(param=='x'){//se for latitude
        result = a1->latitude - a2->latitude;
    }
    else{
        result = a1->longitude - a2->longitude;
    }
    if(result < -0.1){//se for menor, retorna 1
        return 1;
    }
     else if(result >= -0.1 && result <= 0.1){//se for igual(com  um margem de "aproximação" mais ou menos 0.1) retorna -1
        return -1;
    }
    else{//se for maior retorna 0
        return 0;
    }
}

double distancia_fastfood(const void *a, const void *b, char param){
    fastFood * a1;
    fastFood * a2;
    a1 = (fastFood *) a;
    a2 = (fastFood *) b;
    int result = 0;
    if(param=='x'){//se for latitude
        result = a1->latitude - a2->latitude;
    }
    else{
        result = a1->longitude - a2->longitude;
    }
    return result;
}

void print(no* recebido, char tipo){
    if(tipo == 'f'){//se os dados forem de um fast food
        printf("\n--------------------\nAdress: %s\nCity: %s\nCountry: %s\nLatitude:%f\nLongitude: %f\nName: %s\nPostal Code: %s\nProvince: %s\nWebsite: %s\n--------------------\n",
        ((fastFood*)(recebido->dados))->address,
        ((fastFood*)(recebido->dados))->city,
        ((fastFood*)(recebido->dados))->country,
        ((fastFood*)(recebido->dados))->latitude,
        ((fastFood*)(recebido->dados))->longitude,
        ((fastFood*)(recebido->dados))->name,
        ((fastFood*)(recebido->dados))->postalCode,
        ((fastFood*)(recebido->dados))->province,
        ((fastFood*)(recebido->dados))->websites);
    }
    else{//se os dados forem de uma cidade
        printf("\n--------------------\nCodigo IBGE: %d\nNome do municipio: %s\nCodigo UF: %d\nCapital: %d\nLatitude: %f\nLongitude: %f\nCodigo SIAFI: %d\nDDD: %d\nFuso Horario: %s\n--------------------\n",
        ((cidade*)(recebido->dados))->codIBGE,
        ((cidade*)(recebido->dados))->nome,
        ((cidade*)(recebido->dados))->uf,
        ((cidade*)(recebido->dados))->capital,
        ((cidade*)(recebido->dados))->latitude,
        ((cidade*)(recebido->dados))->longitude,
        ((cidade*)(recebido->dados))->siafi,
        ((cidade*)(recebido->dados))->ddd,
        ((cidade*)(recebido->dados))->fuso);
    }
}



void montarLista(no ** indice,char nomeArq[MAXCHAR]){
    no * aux;
    no * p = NULL;
    float auxX,auxY;
    int cont = 0;
    FILE * arq;
    arq = fopen(nomeArq, "r");
    while (arq == NULL)  // Se houve erro na abertura
    {
        printf("\n!!!Problemas na abertura do arquivo!!!\n");
        printf("\nInforme o nome do arquivo que estao os dados corretamente: ");
        scanf("%s",nomeArq);
        arq = fopen(nomeArq, "r");
    }
    if(strcmp(nomeArq,"municipios.txt")==0){
        cidade * cidad = (cidade*) malloc(sizeof(cidade));
        while (fscanf(arq, "%d,%[^,],%f,%f,%d,%d,%d,%d,%s\n",&(cidad->codIBGE),&(cidad->nome), &(cidad->latitude),&(cidad->longitude), &(cidad->capital), &(cidad->uf),&(cidad->siafi),&(cidad->ddd),&(cidad->fuso)) !=EOF)
        {   
            no * temp = criarNO(cidad,compara_cidade);
            cont ++;
            aux = criarNO(cidad, compara_cidade);

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
            cidad = (cidade *)malloc(sizeof(cidade));
        }
    }
    else if(strcmp(nomeArq,"fastFood.txt")==0){
        fastFood * fastfood = (fastFood*) malloc(sizeof(fastFood));
 
        while (fscanf(arq, "%d,%[^,],%[^,],%[^,],%f,%f,%[^,],%[^,],%[^,],%[^\n]\n",&(fastfood->id),fastfood->address,fastfood->city,fastfood->country,&(fastfood->latitude),&(fastfood->longitude),fastfood->name,fastfood->postalCode,fastfood->province,fastfood->websites)!=EOF)
        {
            cont ++;
            aux = criarNO(fastfood, compara_fastfood);
            
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
            fastfood = (fastFood *)malloc(sizeof(fastFood));
        }
    }
    printf("\nForam inseridos %d nos na estrutura\n",cont);
    fclose(arq);
}


int main(){

    no * indiceLista = NULL;
    char nomeArq[MAXCHAR];
    float lat, lon;
    printf("\nInforme o nome do arquivo que estao os dados: ");
    scanf("%s",nomeArq);
    no * aux = NULL;

    no * temp = NULL;

    no * raiz = NULL;

    cidade * tempC = NULL;

    fastFood * tempF = NULL;

    no * encontrado = NULL;

    no** listaprox = NULL;
   
   if(strcmp(nomeArq,"municipios.txt")==0){
        tempC = (cidade*) malloc(sizeof(cidade));
   }
   else{
        tempF = (fastFood*) malloc(sizeof(fastFood));
    }

    montarLista(&indiceLista,nomeArq);
    

    montarKD(&raiz, &indiceLista);


    //testes unitários verificando se a raiz é constante, pois como os dados são estáticos, a mediana deve permanecer a mesma sempre
    if(strcmp(nomeArq,"municipios.txt")==0){
        assert(((cidade*)raiz->dados)->codIBGE == 5205109);//se os dados forem de cidades, a mediana inicial, que é a raiz da árvore, deve ser o nó cujo codigoIBGE é 5205109, = Catalão
    }
    else{
        assert(((fastFood*)raiz->dados)->id == 4169);//se os dados forem de fastFood's a mediana inicial, que é a raiz da árvore, deve ser do nó cujo id é 4169 = Long John Silver's, Wichita-US
    }


    int input = 0;
    while(input != -1){
        printf("\n\n\n\nEscollha um opcao:\n1-Mostrar mais proxima\n2-Mostrar as 5 mais proximas\n3-Verificar se o no esta na arvore\n4-Encerrar\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                printf("\n\n\n\n---MAIS PROXIMA---\nInformar as coordenadas, no formato 'latitude longitude'\n");//esta trabalhando com cidades
                if(strcmp(nomeArq,"municipios.txt")==0){
                    scanf("%f %f",&(tempC->latitude),&(tempC->longitude));//lê os dados
                    aux = criarNO(tempC, compara_cidade);//cria um nó para poder comparar na estrutura
                    encontrado = encontrarMaisProximo(raiz,aux,distancia_cidade);//procura o nó mais proximo do tipo cidade, com o método de calcular distancia de cidades
                    print(encontrado,'c');//imprime o nó do tipo cidade
                }
                else{//esta trabalhando com fastFood's
                    scanf("%f %f",&(tempF->latitude),&(tempF->longitude));//lê os dados
                    aux = criarNO(tempF, compara_fastfood);//cria um novo nó para poder realizar a comparação na estrutura
                    encontrado = encontrarMaisProximo(raiz,aux,distancia_fastfood);//procura o nó mais proximo em fastFood, com o método de calcular distancia de fastFoods
                    print(encontrado,'f');//imprime o nó do tipo fastfood
                }
                break;
            case 2:
                printf("\n\n\n\n---K MAIS PROXIMAS---\nInformar as coordenadas, no formato 'latitude longitude'\n");
                
                if(strcmp(nomeArq,"municipios.txt")==0){
                    scanf("%f %f",&(tempC->latitude),&(tempC->longitude));
                    aux = criarNO(tempC, compara_cidade);
                    temp = buscaNO(raiz,aux,'x');

                    if(aux->compara(aux,temp,'x') == -1 && aux->compara(aux,temp,'y') == -1){//o nó existe na estrutura
                        listaprox = kProx(5, temp, distancia_cidade);//nesse caso k = 5, mas poderia ser qualquer valor
                        printf("\nENCONTRADOS:\n===============");
                        for(int i = 0; i < 5; i++){
                            print(listaprox[i],'c');
                        }
                        printf("\n===============");
                    }
                    else{//o nó não existe na estrutura, logo, temp é o pai do nó caso ele estivesse na estrutura, logo, temp é um dos mais próximos também
                        print(temp,'c');
                        listaprox = kProx(4, temp, distancia_cidade);//nesse caso k = 4, mas poderia ser qualquer valor, pois já temos 1, que é o "pai"
                        printf("\nENCONTRADOS:\n===============");
                        for(int i = 0; i < 4; i++){
                            print(listaprox[i],'c');
                        }
                        printf("\n===============");               
                    }
                }
                else{
                    scanf("%f %f",&(tempF->latitude),&(tempF->longitude));
                    aux = criarNO(tempF, compara_fastfood);
                    temp = buscaNO(raiz,aux,'x');
                     if(aux->compara(aux,temp,'x') == -1 && aux->compara(aux,temp,'y') == -1){//o nó existe na estrutura
                        listaprox = kProx(5, temp, distancia_fastfood);//nesse caso k = 5, mas poderia ser qualquer valor
                        printf("\nENCONTRADOS:\n===============");
                        for(int i = 0; i < 5; i++){
                            print(listaprox[i],'f');
                        }
                        printf("\n===============");
                    }
                    else{//o nó não existe na estrutura, logo, temp é o pai do nó caso ele estivesse na estrutura, logo, temp é um dos mais próximos também
                        print(temp,'f');
                        listaprox = kProx(4, temp, distancia_fastfood);//nesse caso k = 4, mas poderia ser qualquer valor, pois já temos 1, que é o "pai"
                        printf("\nENCONTRADOS:\n===============");
                        for(int i = 0; i < 4; i++){
                            print(listaprox[i],'f');
                        }
                        printf("\n===============");               
                    }
                }
                break;
            case 3:
                printf("---Verificar preseca---\nInformar as coordenadas, no formato 'latitude longitude'\n");

                if(strcmp(nomeArq,"municipios.txt")==0){//estamos trabalhanod com nós do tipo "cidade"
                    scanf("%f %f",&(tempC->latitude),&(tempC->longitude));
                    aux = criarNO(tempC, compara_cidade);
                    temp = buscaNO(raiz,aux,'x');

                    if(aux->compara(aux,temp,'x') == -1 && aux->compara(aux,temp,'y') == -1){//o nó existe na estrutura
                        print(temp,'c');
                    }
                    else{
                        printf("\nNao ha nenhum no na estrutura com esse valores");
                    }
                }
                else{//estamos trabalhando com "fastfood"
                     scanf("%f %f",&(tempC->latitude),&(tempC->longitude));
                    aux = criarNO(tempC, compara_cidade);
                    temp = buscaNO(raiz,aux,'x');

                    if(aux->compara(aux,temp,'x') == -1 && aux->compara(aux,temp,'y') == -1){//o nó existe na estrutura
                        print(temp,'c');
                    }
                    else{
                        printf("\nNao ha nenhum no na estrutura com esse valores");
                    }
                }
                break;
            case 4:
                destruir(raiz);
                free(raiz);
                input=-1;  
                printf("\nArvore destruida");              
                break;
            default:
                printf("\nOpcao invalida");
                break;
        }
    }

    return 0;
}