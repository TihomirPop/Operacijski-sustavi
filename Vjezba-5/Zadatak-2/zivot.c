#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAX_BROJ_JELA 30

typedef enum {nista, cokolada, cevapi, janjetina, strukle, grah, keksi, kelj, jabuka} Jelo; 
typedef struct {
	int pojedeno;
	int odbijeno;
	int prazno;
} JeloStat;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int brojJela;
static Jelo stol = nista;

void* tin();
void* davor();
void* ivica();
void* ivan();
void* kuharica();

void spavanje(const char* ime);
void programiranje(const char* ime);
void servis(const char* ime);
void televizija(const char* ime);
void tenis(const char* ime);
void klavir(const char* ime);
void kuhanje();
void odmaranje();
void jeloNaStol();
void jedenje(const char* ime, JeloStat* jeloStat);
void printJeloStat(const char* ime, JeloStat* jeloStat);

int main(int argc, char *argv[]){
    pthread_t opisnik[5];

    if(argc != 2){
        printf("Krivi broj parametara. Sintaksa: brojJela\n");
        exit(EXIT_FAILURE);
    }

    brojJela = atoi(argv[1]);
    if(brojJela > MAX_BROJ_JELA || brojJela < 0){
        printf("Broj djece mora biti izmedu 1 i %d\n", MAX_BROJ_JELA);
        exit(EXIT_FAILURE);
    }
    
    if (pthread_create(&opisnik[0], NULL, tin, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[1], NULL, davor, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[2], NULL, ivica, NULL))
        printf("Greska u pthread_create()!\n");

    if (pthread_create(&opisnik[3], NULL, ivan, NULL))
        printf("Greska u pthread_create()!\n");
        
    if (pthread_create(&opisnik[4], NULL, kuharica, NULL))
        printf("Greska u pthread_create()!\n");


    for(int i = 0; i < 5; i++)
        if(pthread_join(opisnik[i], NULL))
            printf("Greska u pthread_join()!\n");

    return 0;
}

void* tin(){
    const char* ime = "Tin";
    JeloStat jeloStat;

    srand((unsigned)time(NULL));

    while(brojJela){
        spavanje(ime);
        programiranje(ime);
        jedenje(ime, &jeloStat);
        servis(ime);
    }

    printJeloStat(ime, &jeloStat);

    pthread_exit(NULL);
}

void* davor(){
    const char* ime = "Davor";
    JeloStat jeloStat;

    srand((unsigned)time(NULL));

    while(brojJela){
        spavanje(ime);
        programiranje(ime);
        jedenje(ime, &jeloStat);
        televizija(ime);
    }

    printJeloStat(ime, &jeloStat);

    pthread_exit(NULL);
}

void* ivica(){
    const char* ime = "Ivica";
    JeloStat jeloStat;

    srand((unsigned)time(NULL));

    while(brojJela){
        spavanje(ime);
        tenis(ime);
        jedenje(ime, &jeloStat);
        programiranje(ime);
    }

    printJeloStat(ime, &jeloStat);

    pthread_exit(NULL);
}

void* ivan(){
    const char* ime = "Ivan";
    JeloStat jeloStat;

    srand((unsigned)time(NULL));

    while(brojJela){
        spavanje(ime);
        klavir(ime);
        jedenje(ime, &jeloStat);
        programiranje(ime);
    }

    printJeloStat(ime, &jeloStat);

    pthread_exit(NULL);
}

void* kuharica(){
    srand((unsigned)time(NULL));

    for(int i = brojJela; i; i--){
        kuhanje();
        jeloNaStol();
        odmaranje();
    }
    
    pthread_exit(NULL);
}


void spavanje(const char* ime){
    printf("%s sada spava\n", ime);
    fflush(stdout);

    if(strcmp(ime, "Tin"))
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

void kuhanje(){
    sleep(rand() % 2 + 1);
}

void odmaranje(){
    sleep(rand() % 2 + 1);
}

void jeloNaStol(){
    Jelo jelo = rand() % 8 + 1;
    
    while(stol);
    pthread_mutex_lock(&mutex);
    stol = jelo;
    pthread_mutex_unlock(&mutex);
}

void jedenje(const char* ime, JeloStat* jeloStat){
    printf("%s sada ide jesti\n", ime);
    fflush(stdout);

    pthread_mutex_lock(&mutex);
    if(stol){
        if(!strcmp(ime, "Tin")){
            if(stol == cevapi || stol == janjetina){
                pthread_mutex_unlock(&mutex);
                jeloStat->odbijeno++;
                return;
            }
            stol = nista;
            brojJela--;
            pthread_mutex_unlock(&mutex);
            jeloStat->pojedeno++;
            return;           
        }
        else if(!strcmp(ime, "Davor")){
            if(stol == cokolada || stol == keksi){
                pthread_mutex_unlock(&mutex);
                jeloStat->odbijeno++;
                return;
            }
            stol = nista;
            brojJela--;
            pthread_mutex_unlock(&mutex);
            jeloStat->pojedeno++;
            return;
        }
        else if(!strcmp(ime, "Ivica")){
            if(stol == grah || stol == kelj){
                pthread_mutex_unlock(&mutex);
                jeloStat->odbijeno++;
                return;
            }
            stol = nista;
            brojJela--;
            pthread_mutex_unlock(&mutex);
            jeloStat->pojedeno++;
            return;           
        }
        else if(!strcmp(ime, "Ivan")){
            if(stol == strukle){
                pthread_mutex_unlock(&mutex);
                jeloStat->odbijeno++;
                return;
            }
            stol = nista;
            brojJela--;
            pthread_mutex_unlock(&mutex);
            jeloStat->pojedeno++;
            return;           
        }
    } 
    pthread_mutex_unlock(&mutex);
    jeloStat->prazno++;
    return;
}

void printJeloStat(const char* ime, JeloStat* jeloStat){
    sleep(15);
    printf("\n%s:\npojedeno = %d\nodbijeno = %d\nprazno = %d\n", ime, jeloStat->pojedeno, jeloStat->odbijeno, jeloStat->prazno);
    fflush(stdout);
}