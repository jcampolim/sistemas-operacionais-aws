#include <stdio.h>
#include <stdlib.h>

// Variável global para armazenar o valor do tempo
int tempo = 0;

int main() {
    int n, direcao, direcaoInicial;
    scanf("%d", &n);

    // Cria duas filas, uma para cada sentido (a linguagem C não possui a fila implementada por padrão,
    //  então usamos dois vetores estáticos para simular seu funcionamento)
    int *pessoas0 = (int *)malloc(n * sizeof(int));
    int *pessoas1 = (int *)malloc(n * sizeof(int));

    // Lê os valores de cada pessoa e armazena em sua fila correspondente
    int qtde0 = 0, qtde1 = 0;
    while(qtde0 + qtde1 < n) {
        int aux;
        scanf("%d %d", &aux, &direcao);

        if(qtde0 + qtde1 == 0) {
            direcaoInicial = direcao;
        }
    
        if(direcao == 0) {
            pessoas0[qtde0] = aux;
            qtde0++;
        } else {
            pessoas1[qtde1] = aux;
            qtde1++;
        }
    }

    int pos0 = 0, pos1 = 0;

    // O tempo de chegada da primeira pessoa é adicionado à variável tempo
    if(direcaoInicial == 0) {
        tempo = pessoas0[0];
    } else {
        tempo = pessoas1[0];
    }

    printf("\n");
    direcao = direcaoInicial;

    // Percorre todas as pessoas da fila, somando o tempo que a escada ficou ligada 
    while(pos0 < qtde0 || pos1 < qtde1) {
        // Se a pessoa da fila 0 chegou primeiro que a pessoa da fila 1
        if((pessoas0[pos0] < pessoas1[pos1] && pos0 < qtde0) || qtde1 == 0 || qtde1 == pos1) {
            printf("Fila 0 - %d\n", pessoas0[pos0]);
            // Se o tempo de chegada da próxima pessoa for maior que o tempo total da escada
            if(pessoas0[pos0] >= tempo) {
                tempo = pessoas0[pos0] + 10;
                pos0++;
                
                direcao = 0;
            }

            // Se a pessoa foi a primeira a entrar na escada
            if(pos0 + pos1 == 0) {
                tempo += 10;
                pos0++;
            }

            // Se o tempo de chegada da pessoa for menor que o tempo da escada
            if(pessoas0[pos0] <= tempo && pos0 < qtde0) {
                // Se a escada está na direção oposta, então várias pessoas que chegaram e tiveram 
                // que esperar podem entrar juntas na escada rolante
                if(direcao == 1) {
                    while(pessoas0[pos0] <= tempo && pos0 < qtde0) {
                        pos0++;
                    }
                    pessoas0[pos0 - 1] = tempo;
                    tempo += 10;
                }
                // Agora que a escada está no mesmo sentido, as pessoas podem ir entrando 
                // conforme elas vão chegando
                while(pessoas0[pos0] <= tempo && pos0 < qtde0) {
                    tempo += (pessoas0[pos0] - pessoas0[pos0 - 1]);
                    pos0++;
                }

                direcao = 0;
            }
        // Se a pessoa da fila 1 chegou primeiro que a pessoa da fila 0
        } else if((pessoas0[pos0] > pessoas1[pos1] && pos1 < qtde1) || qtde0 == 0 || qtde0 == pos0) {
            printf("Fila 1 - %d\n", pessoas1[pos1]);
            // Se o tempo de chegada da próxima pessoa for maior que o tempo total da escada
            if(pessoas1[pos1] > tempo) {
                tempo = pessoas1[pos1] + 10;
                pos1++;
                
                direcao = 1;
            }

            // Se a pessoa foi a primeira a entrar na escada
            if(pos0 + pos1 == 0) {
                tempo += 10;
                pos1++;
            }

            // Se o tempo de chegada da pessoa for menor que o tempo da escada
            if(pessoas1[pos1] <= tempo && pos1 < qtde1) {
                // Se a escada está na direção oposta, então várias pessoas que chegaram e tiveram 
                // que esperar podem entrar juntas na escada rolante
                if(direcao == 0) {
                    while(pessoas1[pos1] <= tempo && pos1 < qtde1) {
                        pos1++;
                    }
                    pessoas1[pos1 - 1] = tempo;
                    tempo += 10;
                }
                // Agora que a escada está no mesmo sentido, as pessoas podem ir entrando 
                // conforme elas vão chegando
                while(pessoas1[pos1] <= tempo && pos1 < qtde1) {
                    tempo += (pessoas1[pos1] - pessoas1[pos1 - 1]);
                    pos1++;
                }

                direcao = 1;
            }
        }
    }

    // Exibe na tela o tempo total que a escada ficou ligada 
    printf("\nTempo = %d\n", tempo);

    // Libera o espaço de memória alocado para cada fila
    free(pessoas0);
    free(pessoas1);

    return 0;
}
