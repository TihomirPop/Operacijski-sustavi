#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>

char avion[100];

int getSlobodnaMjesta(char* slobodnaMjesta){
    int brojSlobodnihMjesta = 0;

    for(int i = 0; i < 100; i++)
        if(avion[i] == 0){
            slobodnaMjesta[brojSlobodnihMjesta] = i;
            brojSlobodnihMjesta++;
        }

    sleep(rand() % 3 + 1);

    return brojSlobodnihMjesta;
}

void* aplikacija(){
    char slobondaMjesta[100], odabir;
    int brojSlobodnihMjesta;

    srand((unsigned)time(NULL));
    sleep(rand() % 5 + 1);

    brojSlobodnihMjesta = getSlobodnaMjesta(slobondaMjesta);
    do{
        odabir = slobondaMjesta[rand() % brojSlobodnihMjesta];
    }while(rand() % 2);
    sleep(rand() % 2 + 1);
    avion[odabir] = 1;

    pthread_exit(NULL);
}


int main(int argc, char *argv[]){
    char indexKasnijegSpajanja, brojZauzetihMjesta = 0;;
    pthread_t opisnik[100];

    srand((unsigned)time(NULL));
    indexKasnijegSpajanja = rand() % 100;

    for(int i = 0; i < indexKasnijegSpajanja; i++)
        if (pthread_create(&opisnik[i], NULL, aplikacija, NULL))
            printf("Greska u pthread_create()!\n");

    wait(1);

    for(int i = indexKasnijegSpajanja; i < 100; i++)
        if (pthread_create(&opisnik[i], NULL, aplikacija, NULL))
            printf("Greska u pthread_create()!\n");

    for(int i = 0; i < 100; i++)
        if(pthread_join(opisnik[i], NULL))
            printf("Greska u pthread_join()!\n");
    
    for(int i = 0; i < 100; i++)
        if(avion[i])
            brojZauzetihMjesta++;

    printf("zauzeto: %d\nslobodno: %d\n", brojZauzetihMjesta, 100 - brojZauzetihMjesta);
    return 0;
}