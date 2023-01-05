#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* tin();
void* davor();
void* ivica();
void* ivan();

void spavanje(const char* ime);
void programiranje(const char* ime);
void servis(const char* ime);
void televizija(const char* ime);
void tenis(const char* ime);
void klavir(const char* ime);

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

void* tin(){
    const char* ime = "tin";
    srand((unsigned)time(NULL));
}

void* davor(){
    const char* ime = "davor";
    srand((unsigned)time(NULL));
}

void* ivica(){
    const char* ime = "ivica";
    srand((unsigned)time(NULL));
}

void* ivan(){
    const char* ime = "ivan";
    srand((unsigned)time(NULL));
}


void spavanje(const char* ime){
    printf("%s sada spava\n", ime);
    fflush(stdout);

    if(strcmp(ime, "tin"))
        sleep(rand() % 6 + 5);
    else
        sleep(rand() % 4 + 7);
}

void programiranje(const char* ime){
    printf("%s sada programira\n", ime);
    fflush(stdout);

    int faktorijel = 1;
    for(int i = rand() % 10 + 1; i >= 1; i--)
        faktorijel *= i;
}

void servis(const char* ime){
    printf("%s sada vozi auto na servis\n", ime);
    fflush(stdout);

    int kvar = rand() % 100;
    if(kvar < 25)
        sleep(4);
    else if(kvar < 45)
        sleep(2);
    else
        sleep(rand() % 3 + 2);
}

void televizija(const char* ime){
    printf("%s sada gleda tv\n", ime);
    fflush(stdout);

    sleep(rand() % 3 + 2);
}

void tenis(const char* ime){
    printf("%s sada igra tenis\n", ime);
    fflush(stdout);

    sleep(rand() % 3 + 2);
}

void klavir(const char* ime){
    printf("%s sada slusa sviranje klavira\n", ime);
    fflush(stdout);

    sleep(rand() % 3 + 2);
}