#include<stdio.h>
#include<stdlib.h>
#include<time.h>

signed char polje[100000];

main(){
    time_t t;

    srand((unsigned)time(&t));

    for(int i = 0; i < 100000; i++)
        polje[i] = (rand() % 2) ? 1 : -1;

    for(int i = 0; i < 100000; i++)
        printf("%d\n", polje[i]);
    
    sleep(10);
}