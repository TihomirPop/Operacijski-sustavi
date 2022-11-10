#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    int bufferSize;
    char* buffer;
    int src, dst;

    if(argc != 4){
        write(2, "Krivi broj parametara. Sintaksa: src dst bufferSize\n", 52);
        exit(EXIT_FAILURE);
    }

    bufferSize = atoi(argv[3]);
    if(bufferSize > MAX_BUFFER_SIZE || bufferSize < 1){
        write(2, "Velicina buffera mora biti izmedu 1 i 1024 bytea\n", 49);
        exit(EXIT_FAILURE);
    }
    buffer = (char*)malloc(bufferSize);

    src = open(argv[1], O_RDONLY);
    if(src == -1){
        write(2, "Nema src datoteke\n", 18);
        exit(EXIT_FAILURE);
    }
    
    dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if(dst == -1){
        write(2, "Nema dozvole za dst datoteku\n", 29);
        exit(EXIT_FAILURE);
    }

    while(1){
        int n;
        n = read(src, buffer, bufferSize);
        if(n == 0)
            break;
        write(dst, buffer, n);
    }

    close(src);
    close(dst);
    free(buffer);

    return(0);
}
