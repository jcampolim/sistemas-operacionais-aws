#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid;

    int value = 5;
    int fd[2]; // file descriptor para especificar o pipe que está sendo usado

   // cria o pipe
   if(pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    // cria o processo filho
    pid = fork();

    if(pid < 0) {
    	// ocorre algum erro
        fprintf(stderr, "fork failed\n");
        return 1;
    } else if(pid == 0) {
    	// processo filho

        close(fd[0]);  // fecha a entrada de leitura do pipe
        printf("Entrei no filho!\n");
        value += 15;
        printf("CHILD: value = %d\n", value);

        write(fd[1], &value, sizeof(value)); // escreve o valor no pipe
        close(fd[1]);  // fecha a escrita no pipe

        return 0;
    } else {
    	// processo pai

        close(fd[1]);  // fecha a escrita no pipe
        wait(NULL);

        read(fd[0], &value, sizeof(value)); // lê o valor do pipe
        close(fd[0]);  // fecha a leitura no pipe

        printf("PARENT: value = %d\n", value);
        return 0;
    }
}

