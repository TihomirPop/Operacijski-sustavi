#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* tin();
void* davor();
void* ivica();
void* ivan();

int main(int argc, char *argv[]){
    pthread_t opisnik[4];
    
    if (pthread_create(&opisnik[0], NULL, tin, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[1], NULL, davor, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[2], NULL, ivica, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[3], NULL, ivan, NULL))
        printf("Greska u pthread_create()!\n");

    for(int i = 0; i < 4; i++)
        if(pthread_join(opisnik[i], NULL))
            printf("Greska u pthread_join()!\n");

    return 0;
}