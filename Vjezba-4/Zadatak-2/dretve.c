#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BROJ_DRETVI 100000

int zbroj;

void *povecajZbroj(){
    zbroj++;
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    int brojDretvi;
    pthread_t *opisnik;

    if(argc != 2){
        printf("Krivi broj parametara. Sintaksa: brojDretvi\n");
        exit(EXIT_FAILURE);
    }

    brojDretvi = atoi(argv[1]);
    if(brojDretvi > MAX_BROJ_DRETVI || brojDretvi < 1){
        printf("Broj dretvi mora biti izmedu 1 i %d\n", MAX_BROJ_DRETVI);
        exit(EXIT_FAILURE);
    }

    opisnik = (pthread_t*)malloc(sizeof(pthread_t) * brojDretvi);

    for(int i = 0; i < brojDretvi; i++)
        if (pthread_create(&opisnik[i], NULL, povecajZbroj, NULL)){
            printf("Greska u pthread_create() na indexu %d!\n", i);
            exit(EXIT_FAILURE);
        }

    for(int i = 0; i < brojDretvi; i++)
        if(pthread_join(opisnik[i], NULL))
            printf("Greska u pthread_join()!\n");
    
    printf("%d", zbroj);

    free(opisnik);

    return 0;
}