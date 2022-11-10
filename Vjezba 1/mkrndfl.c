#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_FILE_SIZE 4000000000

int main(int argc, char *argv[]){
    unsigned char random;
    unsigned int size;
    FILE* dst;
    time_t t;

    srand((unsigned)time(&t));

    if(argc != 3){
        printf("Krivi broj parametara. Sintaksa: dst velicina\n");
        exit(1);
    }

    size = atoi(argv[2]);
    if(size > MAX_FILE_SIZE || size < 1){
        printf("parametar size mora biti izmedu 1 i 4000000000");
        exit(2);
    }

    dst = fopen(argv[1], "w");
    if(dst == NULL){
        printf("Nema dozvole za dst datoteku\n");
        exit(3);
    }

    for(unsigned int i = 0; i < size; i++){
        random = rand() % 256;
        fprintf(dst, "%c", random);
    }

    fclose(dst);

    return 0;
}