#include<stdio.h>
#include<stdlib.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    int bufferSize;
    char* buffer;
    FILE *src, *dst;

    if(argc != 4){
        printf("Krivi broj parametara. Sintaksa: src dst bufferSize\n");
        exit(1);
    }

    bufferSize = atoi(argv[3]);
    if(bufferSize > MAX_BUFFER_SIZE || bufferSize < 1){
        printf("Velicina buffera mora biti izmedu 1 i 1024 bytea\n");
        exit(2);
    }
    buffer = (char*)malloc(bufferSize);

    src = fopen(argv[1], "r");
    if(src == NULL){
        printf("Nema src datoteke\n");
        exit(3);
    }
    
    dst = fopen(argv[2], "w");
    if(dst == NULL){
        printf("Nema dozvole za dst datoteku\n");
        exit(4);
    }

    while(1){
        int n;
        n = fread(buffer, 1, bufferSize, src);
        fwrite(buffer, 1, n, dst);
        if(feof(src))
            break;
    }

    fclose(src);
    fclose(dst);
    free(buffer);

    return(0);
}
