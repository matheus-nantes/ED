#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define SEED    0x12345678

typedef struct{
    char codigo_ibge[100];
    char nome[100];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso[100];
}municipio;

char * get_key_municipio(void * reg){
    return(*((municipio *)reg)).codigo_ibge;
}


void * aloca_municipio(char codigo_ibge[100],char nome[100], float latitude, float longitude,int capital,int codigo_uf,int siafi_id,int ddd,char fuso[100]){
    municipio * munix = malloc(sizeof(municipio));
    strcpy(munix->codigo_ibge,codigo_ibge);
    strcpy(munix->nome,nome);
    munix->latitude = latitude;
    munix->longitude = longitude;
    munix->capital = capital;
    munix->codigo_uf = codigo_uf;
    munix->siafi_id = siafi_id;
    munix->ddd = ddd;
    strcpy(munix->fuso,fuso);
    return munix;
}


typedef struct {
     uintptr_t * table;
     int size;
     int max;
     int segundoHash;/////////////////////////////////////////////
     uintptr_t deleted;
     char * (*get_key)(void *);
}thash;


uint32_t hashf(const char* str, uint32_t h){
    /* One-byte-at-a-time Murmur hash 
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}


int hash_insere(thash * h, void * bucket){
    uint32_t hash = hashf(h->get_key(bucket),SEED);
    int pos = hash % (h->max);//hash1
    int incremento = hash % (h->segundoHash);//calcula o incrmeento do segundo hash
    if (h->max == (h->size+1)){
        free(bucket);
        return EXIT_FAILURE;
    }else{
        while(h->table[pos] != 0){
            if (h->table[pos] == h->deleted)
                break;
            pos = (pos + incremento) % h->max;///////soma o segundo hash na posicao
        }
        h->table[pos] = (uintptr_t) bucket;
        h->size +=1;
    }
    return EXIT_SUCCESS;
}

//função auxiliar pra verificar se um número e primo ou não
int ePrimo(int n){
    if(n <= 1){
        return 0;
    }
    for(int i = 2; i < n/2; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

//função auxiliar para achar o número mais próximo do total 
int primoMaisProx(int n){
    for(int i = n-1; i > 1; i--){
        if(ePrimo(i)){
            return i;
        }
    }
    return 2;
}



int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) ){
    h->table = calloc(sizeof(uintptr_t),nbuckets +1);
    if (h->table == NULL){
        return EXIT_FAILURE;
    }
    h->max = nbuckets +1;
    h->size = 0;
    h->segundoHash = primoMaisProx(h->max);///////////// define o valor do segundo hash
    h->deleted = (uintptr_t) & (h->size);
    h->get_key = get_key;
    return EXIT_SUCCESS;
}


void * hash_busca(thash h, const char * key){
    uint32_t hash = hashf(key,SEED);//define o "hash"
    int pos = hash %(h.max);/////calcula o primeiro hash
    int incremento = hash % (h.segundoHash);//calcula o incremento do segundo hash
    int cont = 0;
    int posInicial = pos;///////////////

    if (strcmp (h.get_key((void*)h.table[pos]),key) ==0){
            return (void *)h.table[pos];
        }
    else
        pos = (pos+incremento)%(h.max);//////calcula o segundo hash

    while (h.table[pos] != 0 && pos != posInicial) {///////////
        if (strcmp (h.get_key((void*)h.table[pos]),key) ==0){
            return (void *)h.table[pos];
        }
        else
            pos = (pos+incremento)%(h.max);//////calcula o segundo hash
    }
    return NULL;
}

int hash_remove(thash * h, const char * key){
    uint32_t hash = hashf(key,SEED);//define a key
    int pos = hash % (h->max);////// calcula o primeiro hash
    int incremento = hash % (h->segundoHash);////calcula o incremento do segundo hash
    while(h->table[pos]!=0){
        if (strcmp (h->get_key((void*)h->table[pos]),key) ==0){
            free((void *) h->table[pos]);
            h->table[pos] = h->deleted;
            h->size -=1;
            return EXIT_SUCCESS;
        }else{
            pos = (pos+incremento)%h->max;//calcula o segundo hash
        }

    }
    return EXIT_FAILURE;
}

void hash_apaga(thash *h){
    int pos;
    for(pos =0;pos< h->max;pos++){
        if (h->table[pos] != 0){
            if (h->table[pos]!=h->deleted){
                free((void *)h->table[pos]);
            }
        }
    }
    free(h->table);
}


void teste_municipios(){
    thash h;
    int nBuckets = 5570;
    int cont = 0;
    hash_constroi(&h,nBuckets,get_key_municipio);

    FILE * arq;
    arq = fopen("municipios.txt", "r");
    municipio * munix = (municipio*) malloc(sizeof(municipio));
    while (fscanf(arq, "%[^,],%[^,],%f,%f,%d,%d,%d,%d,%[^\n]\n",munix->codigo_ibge,munix->nome, &(munix->latitude),&(munix->longitude), &(munix->capital), &(munix->codigo_uf),&(munix->siafi_id),&(munix->ddd),munix->fuso) !=EOF)
    {   
        assert(hash_insere(&h,aloca_municipio(munix->codigo_ibge,munix->nome, munix->latitude,munix->longitude, munix->capital, munix->codigo_uf,munix->siafi_id,munix->ddd,munix->fuso))==EXIT_SUCCESS);
        cont ++;
    }
    printf("\nForam inseridos %d buckets na estrutura",cont);

    municipio * achado = (municipio *)hash_busca(h, "3531605");//monte castelo
    printf("\nAchado: %s", achado->nome);

    hash_remove(&h, "3531605");

    achado = NULL;
    achado = (municipio *)hash_busca(h, "3531605");
    if(achado != NULL)
        printf("\nAchado: %s", achado->nome);
    else
        printf("\nNao achou");

    achado = (municipio *)hash_busca(h, "3147006");//paracatu
    printf("\nAchado: %s", achado->nome);        

}



int main(int argc, char* argv[]){
    teste_municipios();
    return 0;
}