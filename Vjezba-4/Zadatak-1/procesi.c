#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_BROJ_DJECE 100000

int zbroj;

int main(int argc, char *argv[]){
    int brojDjece;

    setbuf(stdout, NULL);

    if(argc != 2){
        printf("Krivi broj parametara. Sintaksa: brojDjece\n");
        exit(EXIT_FAILURE);
    }

    brojDjece = atoi(argv[1]);
    if(brojDjece > MAX_BROJ_DJECE || brojDjece < 1){
        printf("Broj djece mora biti izmedu 1 i %d\n", MAX_BROJ_DJECE);
        exit(EXIT_FAILURE);
    }

    pid_t PID;

    for(int i = 0; i < brojDjece; i++){
        switch (PID = fork())
        {
        case -1:
            exit(EXIT_FAILURE);

        case 0:
            zbroj++;
            exit(EXIT_SUCCESS);

        default:
            wait(NULL);
        }
    }

    printf("globalna varijabla zbroj: %d\n", zbroj);

    return(0);
}