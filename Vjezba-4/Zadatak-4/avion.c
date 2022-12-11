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

    printf("\n                             .!!777.\n                             ^&7^~JP!\n                              7B.  :Y5^\n                               YG    ~PJ.\n                                PY    .?P!\n                                .B7     :55^\n                                 !#:      !PJ.\n                                  5P       .?P!.\n                                  .#!        :55^.\n      .~7??!.                      !#:         ~5J:\n      ~&7^~YG!                      5P           7P?.\n       5P   ~G5:                    .B7           .JP!\n       .#7   .JB!                    ~#^            ^55^\n        7&:    ~B5.                   YG.             ~5Y:\n         PP     .JB7                   B?               !P?.\n         .#?      ^PP^ ................5#.               .75?......\n          !&^       ?GYYYYYYJJJJJJJJJJJ?7.                 .75JJJJJJJJJJJJ?J??JJJJJ??7~.\n           YB.          ");
    for(int i = 0; i < 25; i++)
        printf("%s", avion[i] ? "\033[0;31mZ " : "\033[0;32mS ");
    printf("\033[0m");
    printf("           ~7J?.\n           .GY          ");
    for(int i = 25; i < 50; i++)
        printf("%s", avion[i] ? "\033[0;31mZ " : "\033[0;32mS ");
    printf("\033[0m");
    printf("              ~G^\n            PG          ");
    for(int i = 50; i < 75; i++)
        printf("%s", avion[i] ? "\033[0;31mZ " : "\033[0;32mS ");
    printf("\033[0m");
    printf("             .7G^\n           ^&~          ");
    for(int i = 75; i < 100; i++)
        printf("%s", avion[i] ? "\033[0;31mZ " : "\033[0;32mS ");
    printf("\033[0m");
    printf("         ~7Y5?:\n          .BY       !PYYJ????????????????~                  7J????????JJJJJJJJYJJJJJ?!:\n          J#.     :5P^.:^^~~~~~~~~~~~~^~#?                ^55^::::\n         ^&~     !B?                   ?P               .JP!\n         G5    :YG^                   ~#:              ~GJ.\n        ?#:   7BJ.                   .B!             :YP^\n       ^&! .~YP^                     55             !G?\n       BB!?YJ^                      7B.           :Y5^\n       !?7~.                       :#~           7G?\n                                   PY          :5P^\n                                  JB.         7G?\n                                 ~&~        :PP^\n                                 GJ        7B?\n                                JB.      ~P5:\n                               ^#~     :YG~\n                              .P7    .JG?.\n                             .5Y ..^JGJ.\n                             .YY????!:\n                               ..\n\n\n");   

    return 0;
}
