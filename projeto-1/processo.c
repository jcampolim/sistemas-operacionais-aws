#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int n;
    scanf("%d", &n);

    //Variáveis para armazenar a direção e os tempos de cada pessoa
    int direcao, pessoas[2][n], tempo = 0;

    //Armazenam os IDs dos processos e os descritores de arquivos dos pipes
    pid_t pid[n+1];
    int fd[n+1][2];

    //Cria os pipes para comunicação entre os processos
    for(int i = 0; i <= n; i++) {
      if(pipe(fd[i]) < 0) {
        exit(0);
      }
    }

    //Lê os tempos e as direções de cada pessoa
    //Se for a primeira pessoa, define a direção
    //Armazena o tempo e a direção da pessoa no array pessoas
    int i = 0, j = 0;
    while(i + j < n) {
        int auxDir, aux;
        scanf("%d %d", &aux, &auxDir);

        if(i == 0) {
            direcao = auxDir;
        }

        if(auxDir == 0) {
            pessoas[0][i] = aux; //Pessoas indo para a esquerda (0)
            i++;
        } else {
            pessoas[1][j] = aux; //Pessoas indo para a direita (1)
            j++;
        }
    }

    //Armazena o número de pessoas em cada direção
    int n0 = i, n1 = j;
    i = 0; j = 0;

    //Demonstra o movimento da primeira pessoa
    pid[0] = fork();
    if(pid[0] < 0) {
        fprintf(stderr, "fork failed");
    } else if(pid[0] == 0) {
        close(fd[0][0]);
        tempo += pessoas[direcao][0];
        write(fd[0][1], &tempo, sizeof(tempo));
        close(fd[0][1]);

        return 0;
    } else {
        close(fd[0][1]);
        wait(NULL);
        read(fd[0][0], &tempo, sizeof(tempo));
        close(fd[0][0]);
    }

    while(i + j < n) {
        if(direcao == 0) {
            pid[i+j+1] = fork();
            if(pid[i+j+1] < 0) {
                fprintf(stderr, "fork failed");
            } else if(pid[i+j+1] == 0) {
                //Código executado pelo processo filho
                //Adiciona o tempo da primeira pessoa ao tempo total
                // Escreve o tempo no pipe
                close(fd[i+j+1][0]);
                tempo += 10;
                write(fd[i+j+1][1], &tempo, sizeof(tempo));
                close(fd[i+j+1][1]);

                return 0;
            } else {
                //Código executado pelo processo pai
                //Espera o processo filho terminar
                //Lê o tempo do pipe
                close(fd[i+j+1][1]);
                wait(NULL);
                read(fd[i+j+1][0], &tempo, sizeof(tempo));
                close(fd[i+j+1][0]);
            }

            i++;
            //Simula o movimento das outras pessoas
            //Se a direção atual é para a esquerda, cria um processo filho para simular a próxima pessoa
            while(pessoas[0][i] < tempo && i < n0) {
                pid[i+j+1] = fork();
                if(pid[i+j+1] < 0) {
                    fprintf(stderr, "fork failed");
                } else if(pid[i+j+1] == 0) {
                    close(fd[i+j+1][0]);
                    tempo += (pessoas[0][i] - pessoas[0][i-1]);
                    write(fd[i+j+1][1], &tempo, sizeof(tempo));
                    close(fd[i+j+1][1]);

                    return 0;
                } else {
                    close(fd[i+j+1][1]);
                    wait(NULL);
                    read(fd[i+j+1][0], &tempo, sizeof(tempo));
                    close(fd[i+j+1][0]);
                }       
                i++;
            }
            //Muda a direção da escada
            direcao = 1;
        } else {
            pid[i+j+1] = fork();
            if(pid[i+j+1] < 0) {
                fprintf(stderr, "fork failed");
            } else if(pid[i+j+1] == 0) {
                close(fd[i+j+1][0]);
                // Adiciona um tempo fixo ao tempo total
                tempo += 10;
                // Escreve o tempo no pipe
                write(fd[i+j+1][1], &tempo, sizeof(tempo));
                close(fd[i+j+1][1]);

                return 0;
            } else {
                close(fd[i+j+1][1]);
                wait(NULL);
                read(fd[i+j+1][0], &tempo, sizeof(tempo));
                close(fd[i+j+1][0]);
            }

            j++;

            while(pessoas[1][j] < tempo && j < n1) {
                pid[i+j+1] = fork();
                if(pid[i+j+1] < 0) {
                    fprintf(stderr, "fork failed");
                } else if(pid[i+j+1] == 0) {
                    close(fd[i+j+1][0]);
                    tempo += (pessoas[1][j] - pessoas[1][j-1]);
                    write(fd[i+j+1][1], &tempo, sizeof(tempo));
                    close(fd[i+j+1][1]);

                    return 0;
                } else {
                    close(fd[i+j+1][1]);
                    wait(NULL);
                    read(fd[i+j+1][0], &tempo, sizeof(tempo));
                    close(fd[i+j+1][0]);
                }

                j++;
            }
            //Muda a direção da escada
            direcao = 0;
        }
    }
    // Exibe na tela a quantidade de tempo que a escada ficou ligada
    printf("%d\n", tempo);

    return 0;
}
