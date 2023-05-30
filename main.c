#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "kdTree.h"

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
        while (fscanf(arq, "%d,%[^,],%f,%f,%d,%d,%d,%d,%s\n",&(cidad->codIBGE),&(cidad->nome), &auxX,&auxY, &(cidad->capital), &(cidad->uf),&(cidad->siafi),&(cidad->ddd),&(cidad->fuso)) !=EOF)
        {   
            cont ++;
            aux = criarNO(cidad);
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
            cidad = (cidade *)malloc(sizeof(cidade));
        }
    }
    else if(strcmp(nomeArq,"fastFood.txt")==0){
        fastFood * fastfood = (fastFood*) malloc(sizeof(fastFood));
 
        while (fscanf(arq, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%d,%[^,],%[^\n]\n",&(fastfood->id),&(fastfood->address),&(fastfood->categories),&(fastfood->city),&(fastfood->country),&auxX,&auxY,&(fastfood->name),&(fastfood->postalCode),&(fastfood->province),&(fastfood->websites))!=EOF)
        {
            printf("\n\n id: %d,",fastfood->id);
            printf("\nendereco: %s,",fastfood->address);
            printf("\ncategoria: %s,",fastfood->categories);
            printf("\ncidade: %s,",fastfood->city);
            printf("\npais: %s,",fastfood->country);
            printf("\nx: %f,",auxX);
            printf("\ny: %f,",auxY);
            printf("\nnome: !%s!,",fastfood->name);
            printf("\npostal: -%d-,",fastfood->postalCode);
            printf("\nprovinicia: %s,",fastfood->province);
            printf("\nsite: %s\n",fastfood->websites);
            cont ++;
            aux = criarNO(fastfood);
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
            fastfood = (fastFood *)malloc(sizeof(fastFood));
            }

    }
    
    fclose(arq);
}

void print(no* recebido, char tipo){
    if(tipo == 'f'){//se os dados forem de um fast food
        printf("\n--------------------\nAdress: %s\nCategories:%s\nCity: %s\nCountry: %s\nLatitude:%f\nLongitude: %f\nName: %s\nPostal Code: %d\nProvince: %s\nWebsite: %s\n--------------------\n",
        ((fastFood*)(recebido->dados))->address,
        ((fastFood*)(recebido->dados))->categories,
        ((fastFood*)(recebido->dados))->city,
        ((fastFood*)(recebido->dados))->country,
        recebido->x,
        recebido->y,
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
        recebido->x,
        recebido->y,
        ((cidade*)(recebido->dados))->siafi,
        ((cidade*)(recebido->dados))->ddd,
        ((cidade*)(recebido->dados))->fuso);
    }
}


int main(){

    no * indiceLista = NULL;
    char nomeArq[MAXCHAR];
    float lat, lon;
    printf("\nInforme o nome do arquivo que estao os dados: ");
    scanf("%s",nomeArq);
    montarLista(&indiceLista,nomeArq);

    no * raiz = NULL;
    montarKD(&raiz, &indiceLista);

    printf("\nArvore construida");

    int input = 0;
    while(input != -1){
        printf("\nEscollha um opcao:\n1-Mostrar mais proxima\n2-Mostrar as 5 mais proximas\n3-Encerrar\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                printf("\nInformar as coordenadas, no formato 'latitude longitude'\n");
                scanf("%f %f",&lat,&lon);
                no * encontrado = encontrarMaisProximo(raiz,lat,lon);
                print(encontrado,'c');
                break;
            case 2:
                printf("Informar as coordenadas, no formato 'latitude longitude'\n");
                scanf("%f %f",&lat,&lon);
                no * aux = cincoProx(buscaNO(raiz,lat,lon,'x'));
                printf("\n%f %f",aux[0].x,aux[0].y);
                printf("\n%f %f",aux[1].x,aux[1].y);
                printf("\n%f %f",aux[2].x,aux[2].y);
                printf("\n%f %f",aux[3].x,aux[3].y);
                printf("\n%f %f",aux[4].x,aux[4].y);
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