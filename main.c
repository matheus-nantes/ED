#include<stdlib.h>
#include<stdio.h>
#include<string.h>
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
    int result = 0;
    if(param=='x'){//se for latitude
        result = a1->latitude - a2->latitude;
    }
    else{
        result = a1->longitude - a2->longitude;
    }
    if(result < 0){//se for menor, retorna 1
        return 1;
    }
    else if(result == 0){//se for igual retorna -1
        return -1;
    }
    else{//se for maior retorna 0
        return 0;
    }
}

double distancia_cidade(const void *a, const void *b, char param){
    cidade * a1;
    cidade * a2;
    a1 = (cidade *) a;
    a2 = (cidade *) b;
    int result = 0;
    if(param=='x'){//se for latitude
        result = a1->latitude - a2->latitude;
    }
    else{
        result = a1->longitude - a2->longitude;
    }
    return result;
}


typedef struct fastFood{
    char id[10];
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
    int result = 0;
    if(param=='x'){//se for latitude
        result = a1->latitude - a2->latitude;
    }
    else{
        result = a1->longitude - a2->longitude;
    }
    if(result < 0){//se for menor, retorna 1
        return 1;
    }
    else if(result == 0){//se for igual retorna -1
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
            print(temp,'c');
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
 
        while (fscanf(arq, "%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%[^,],%[^,],%[^\n]\n",fastfood->id,fastfood->address,fastfood->city,fastfood->country,&(fastfood->latitude),&(fastfood->longitude),fastfood->name,fastfood->postalCode,fastfood->province,fastfood->websites)!=EOF)
        {
            printf("\n\n id: %s,",fastfood->id);
            printf("\nendereco: %s,",fastfood->address);
            printf("\ncidade: %s,",fastfood->city);
            printf("\npais: %s,",fastfood->country);
            printf("\nlatitude: %f,",fastfood->latitude);
            printf("\nlongitude: %f,",fastfood->longitude);
            printf("\nnome: !%s!,",fastfood->name);
            printf("\npostal: -%s-,",fastfood->postalCode);
            printf("\nprovinicia: %s,",fastfood->province);
            printf("\nsite: %s\n",fastfood->websites);
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
    
    fclose(arq);
}


int main(){

    no * indiceLista = NULL;
    char nomeArq[MAXCHAR];
    float lat, lon;
    printf("\nInforme o nome do arquivo que estao os dados: ");
    scanf("%s",nomeArq);
    no * aux = NULL;
    no * raiz = NULL;
    cidade * tempC = NULL;
    fastFood * tempF = NULL;
   
   if(strcmp(nomeArq,"municipios.txt")==0){
        tempC = (cidade*) malloc(sizeof(cidade));
   }
   else{
        tempF = (fastFood*) malloc(sizeof(fastFood));
    }

    montarLista(&indiceLista,nomeArq);
    

    montarKD(&raiz, &indiceLista);

    printf("\nArvore construida");

    int input = 0;
    while(input != -1){
        printf("\nEscollha um opcao:\n1-Mostrar mais proxima\n2-Mostrar as 5 mais proximas\n3-Encerrar\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                printf("\nInformar as coordenadas, no formato 'latitude longitude'\n");
                if(tempC != NULL){
                    scanf("%f %f",&(tempC->latitude),&(tempC->longitude));
                    aux = criarNO(tempC, compara_cidade);
                }
                else{
                    scanf("%f %f",&(tempF->latitude),&(tempF->longitude));
                    aux = criarNO(tempF, compara_fastfood);
                }
                no * encontrado = encontrarMaisProximo(raiz,aux,distancia_cidade);
                print(encontrado,'c');
                break;
            case 2:
                printf("Informar as coordenadas, no formato 'latitude longitude'\n");
                
                if(tempC != NULL){
                    scanf("%f %f",&(tempC->latitude),&(tempC->longitude));
                    aux = criarNO(tempC, compara_cidade);
                    aux = criarNO(tempC, compara_cidade);
                }
                else{
                    scanf("%f %f",&(tempF->latitude),&(tempF->longitude));
                    aux = criarNO(tempF, compara_fastfood);
                    aux = criarNO(tempF, compara_fastfood);
                }
                no* listaprox = cincoProx(buscaNO(raiz,aux,'x'), distancia_fastfood);
                break;
            case 3:
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