#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int tempo = 0;
 
// Todas as vezes que eh preciso atualizar o tempo, essa funcao chamada, ela eh responsavel por
// criar um processo filho para atualizar o valor do tempo
void processo(int t) {
    // O ID do processo, necessario para diferenciar o processo filho do processo filho
    pid_t pid;
    // Vetor de duas posicoes que sera usado como file descriptor para especificar o pipe que esta sendo usado
    int fd[2];

    // Cria o pipe 
    if(pipe(fd) < 0) {
        exit(0);
    }

    // Cria o processo filho
    pid = fork();
    // Se ocorre algum erro durante a criacao do processo filho, o ID do processo eh menor que zero
    if(pid < 0) {
        fprintf(stderr, "fork failed");
    // Se o ID do processo for 0, entao eh o processo filho que esta executando
    } else if(pid == 0) {
        // Fecha a entrada de leitura do pipe
        close(fd[0]);
        tempo = t;

        // Escreve o valor atualizado do tempo no pipe
        write(fd[1], &tempo, sizeof(tempo));
        // Fecha a entrada de ecrita no pipe
        close(fd[1]);

        // O processo filho para de excutar
        exit(0);
    // Se o ID for maior do que zero, então eh o processo pai que esta sendo exacutado
    } else {
        // Fecha a entrada de escrita do pipe 
        close(fd[1]);
        // Espera o processo filho terminar de executar
        wait(NULL);
        // Le o valor atualizado do tempo do pipe
        read(fd[0], &tempo, sizeof(tempo));

        // Fecha a entrada de leitura do pipe
        close(fd[0]);
    }
}

int main() {
    int n, direcao, direcaoInicial;
    scanf("%d", &n);

    int **pessoas = (int **)malloc(n * sizeof(int *));
    pessoas[0] = (int *)malloc(n * sizeof(int));
    pessoas[1] = (int *)malloc(n * sizeof(int));

    int tam[] = {0, 0};
    while(tam[0] + tam[1] < n) {
        int aux;
        scanf("%d %d", &aux, &direcao);

        if(tam[0] + tam[1] == 0) {
            direcaoInicial = direcao;
        }
    
        if(direcao == 0) {
            pessoas[0][tam[0]] = aux;
            tam[0]++;
        } else {
            pessoas[1][tam[1]] = aux;
            tam[1]++;
        }
    }

    int pos[] = {0, 0};
    processo(pessoas[direcaoInicial][0]);
    direcao = direcaoInicial;

    while(pos[0] < tam[0] || pos[1] < tam[1]) {
        if((pessoas[0][pos[0]] < pessoas[1][pos[1]] && pos[0] < tam[0]) || tam[1] == 0 || tam[1] == pos[1]) {
            if(pessoas[0][pos[0]] >= tempo) {
                processo(pessoas[0][pos[0]] + 10);
                pos[0]++;
                
                direcao = 0;
            }

            if(pos[0] + pos[1] == 0) {
                processo(tempo + 10);
                pos[0]++;
            }

            if(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                if(direcao == 1) {
                    while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                        pos[0]++;
                    }
                    pessoas[0][pos[0] - 1] = tempo;
                    processo(tempo + 10);
                }
                while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                    processo(tempo + (pessoas[0][pos[0]] - pessoas[0][pos[0] - 1]));
                    pos[0]++;
                }

                direcao = 0;
            }
        } else if((pessoas[0][pos[0]] > pessoas[1][pos[1]] && pos[1] < tam[1]) || tam[0] == 0 || tam[0] == pos[0]) {
            if(pessoas[1][pos[1]] > tempo) {
                processo(pessoas[1][pos[1]] + 10);
                pos[1]++;
                
                direcao = 1;
            }

            if(pos[0] + pos[1] == 0) {
                processo(tempo + 10);
                pos[1]++;
            }

            if(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                if(direcao == 0) {
                    while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                        pos[1]++;
                    }
                    pessoas[1][pos[1] - 1] = tempo;
                    processo(tempo + 10);
                }
                while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                    processo(tempo + (pessoas[1][pos[1]] - pessoas[1][pos[1] - 1]));
                    pos[1]++;
                }

                direcao = 1;
            }
        }
    }

    printf("%d\n", tempo);
    free(pessoas);

    return 0;
}
