#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variável global com o momento que a última pessoa saiu da escada
int tempo = 0;

// Função que será executada quando a thread for criada e irá atualizar o valor do tempo
void *attTempo(void *t) {
	int *aux = (int *)t;
	tempo += *aux;
}

int main() {
    int n;
    scanf("%d", &n);

    // Matriz com duas linhas, onde cada linha representa um sentido da escada rolante
    int direcao, pessoas[2][n];

	pthread_t tid;

    // Lê os valores de entrada e armazena na matriz
    int i = 0, j = 0;
    while(i + j < n) {
        int auxDir, aux;
        scanf("%d %d", &aux, &auxDir);

        if(i == 0) {
            direcao = auxDir;
        }

        if(auxDir == 0) {
            pessoas[0][i] = aux;
            i++;
        } else {
            pessoas[1][j] = aux;
            j++;
        }
    }

    // Define n0 como a quantidade de pessoas no sentido 0 e n1 como a quantidade 
    // de pessoas no sentido 1
    // A variável t armazena a quantidade de tempo que deve ser adicionada
    int n0 = i, n1 = j, t = pessoas[direcao][0];
    i = 0; j = 0;

    // Comandos para criar e executar uma thread (a variável t é passada como parâmetro)
    pthread_create(&tid, NULL, attTempo, (void*)&t);
    pthread_join(tid, NULL);

    // Loop que percorre todos os valores da matriz
    while(i + j < n) {
        if(direcao == 0) {
	        t = 10;

            // Adiciona 10 se entrar uma pessoa no sentido 0
            pthread_create(&tid, NULL, attTempo, (void *)&t);
	        pthread_join(tid, NULL);

            i++;

            // Adiciona o tempo correspondente das próximas pessoas que entram no sentido 0
            // antes da escada rolante trocar de sentido
            while(pessoas[0][i] < tempo && i < n0) {
                t = (pessoas[0][i] - pessoas[0][i-1]);

                pthread_create(&tid, NULL, attTempo, (void *)&t);
                pthread_join(tid, NULL);

                i++;
            } 

            // Muda a direção da escada
            direcao = 1;
        } else {
            t = 10;

            // Adiciona 10 se entrar uma pessoa no sentido 1
	        pthread_create(&tid, NULL, attTempo, (void *)&t);
	        pthread_join(tid, NULL);

            j++;

            // Adiciona o tempo correspondente das próximas pessoas que entram no sentido 1
            // antes da escada rolante trocar de sentido
            while(pessoas[1][j] < tempo && j < n1) {
                t = (pessoas[1][j] - pessoas[1][j-1]);

                pthread_create(&tid, NULL, attTempo, (void *)&t);
                pthread_join(tid, NULL);

                j++;
            } 

            // Muda a direção da escada
            direcao = 0;
        }
    }

    // Exibe na tela a quantidade de tempo que a escada ficou ligada
    printf("%d\n", tempo);
    exit(0);

    return 0;
}
