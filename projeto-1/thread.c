#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int tempo = 0;

// Funcao que sera executada quando a thread for criada e ira atualizar o valor do tempo
void *attTempo(void *t) {
	int *aux = (int *)t;
	tempo = *aux;
}

int main() {
    // O ID da thread, necessario para identificar as threads
    pthread_t tid; 

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
    int t = pessoas[direcaoInicial][0];

    // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
    // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
    pthread_create(&tid, NULL, attTempo, (void *)&t);
    // Aguarda o termino da thread para continuar a execucao
    pthread_join(tid, NULL);

    direcao = direcaoInicial;

    while(pos[0] < tam[0] || pos[1] < tam[1]) {
        if((pessoas[0][pos[0]] < pessoas[1][pos[1]] && pos[0] < tam[0]) || tam[1] == 0 || tam[1] == pos[1]) {
            if(pessoas[0][pos[0]] >= tempo) {
                t = pessoas[0][pos[0]] + 10;

                // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                pthread_create(&tid, NULL, attTempo, (void *)&t);
                // Aguarda o termino da thread para continuar a execucao
                pthread_join(tid, NULL);

                pos[0]++;
                
                direcao = 0;
            }

            if(pos[0] + pos[1] == 0) {
                t  = tempo + 10;

                // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                pthread_create(&tid, NULL, attTempo, (void *)&t);
                // Aguarda o termino da thread para continuar a execucao
                pthread_join(tid, NULL);

                pos[0]++;
            }

            if(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                if(direcao == 1) {
                    while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                        pos[0]++;
                    }
                    pessoas[0][pos[0] - 1] = tempo;
                    t = tempo + 10;

                    // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                    // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                    pthread_create(&tid, NULL, attTempo, (void *)&t);
                    // Aguarda o termino da thread para continuar a execucao
                    pthread_join(tid, NULL);
                }
                while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                    t = tempo + (pessoas[0][pos[0]] - pessoas[0][pos[0] - 1]);

                    // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                    // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                    pthread_create(&tid, NULL, attTempo, (void *)&t);
                    // Aguarda o termino da thread para continuar a execucao
                    pthread_join(tid, NULL);

                    pos[0]++;
                }

                direcao = 0;
            }
        } else if((pessoas[0][pos[0]] > pessoas[1][pos[1]] && pos[1] < tam[1]) || tam[0] == 0 || tam[0] == pos[0]) {
            if(pessoas[1][pos[1]] > tempo) {
                t = pessoas[1][pos[1]] + 10;

                // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                pthread_create(&tid, NULL, attTempo, (void *)&t);
                // Aguarda o termino da thread para continuar a execucao
                pthread_join(tid, NULL);

                pos[1]++;
                
                direcao = 1;
            }

            if(pos[0] + pos[1] == 0) {
                t = tempo + 10;

                // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                pthread_create(&tid, NULL, attTempo, (void *)&t);
                // Aguarda o termino da thread para continuar a execucao
                pthread_join(tid, NULL);

                pos[1]++;
            }

            if(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                if(direcao == 0) {
                    while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                        pos[1]++;
                    }
                    pessoas[1][pos[1] - 1] = tempo;
                    t = tempo + 10;

                    // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                    // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                    pthread_create(&tid, NULL, attTempo, (void *)&t);
                    // Aguarda o termino da thread para continuar a execucao
                    pthread_join(tid, NULL);
                }
                while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                    t = tempo + (pessoas[1][pos[1]] - pessoas[1][pos[1] - 1]);

                    // Funcao para criar uma thread, o primeiro parametro eh o ID da thread, o segundo sao os atributos (podem ser NULL),
                    // o terceiro eh o endereco da funcao que sera executada pela thread e o ultimo sao os parametros da funcao
                    pthread_create(&tid, NULL, attTempo, (void *)&t);
                    // Aguarda o termino da thread para continuar a execucao
                    pthread_join(tid, NULL);

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
