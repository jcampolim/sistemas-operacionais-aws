#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Cria um struct para passar os dados para a função da thread
typedef struct {
  int n;
  int qtde0;
  int qtde1;
  int *pessoas0;
  int *pessoas1;
} Fila;

// Variáveis globais que serão atualizadas pelas duas threads em execução: tempo total
// da escada, topo de cada pilha e direção atual da escada
int tempo = 0;
int direcao, pos0 = 0, pos1 = 0;

// Função de thread que é executada para a fila 0
void *threadFila0(void *f) {
  // O parametro da função é um struct Fila, contendo os dados de cada pessoa
  Fila *fila = (Fila *)f;

  // Executa a repetição até que todas as pessoas da direção 0 entrem na escada
  while (pos0 < fila->qtde0) {
    if ((fila->pessoas0[pos0] < fila->pessoas1[pos1] && pos0 < fila->qtde0) || fila->qtde1 == 0 || fila->qtde1 == pos1) {
      printf("Fila 0 - %d\n", fila->pessoas0[pos0]);
      if (fila->pessoas0[pos0] >= tempo) {
        tempo = fila->pessoas0[pos0] + 10;
        pos0++;

        direcao = 0;
      }

      if (pos0 + pos1 == 0) {
        tempo += 10;
        pos0++;
      }

      if (fila->pessoas0[pos0] <= tempo && pos0 < fila->qtde0) {
        if (direcao == 1) {
          while (fila->pessoas0[pos0] <= tempo && pos0 < fila->qtde0) {
            pos0++;
          }
          fila->pessoas0[pos0 - 1] = tempo;
          tempo += 10;
        }
        while (fila->pessoas0[pos0] <= tempo && pos0 < fila->qtde0) {
          tempo += (fila->pessoas0[pos0] - fila->pessoas0[pos0 - 1]);
          pos0++;
        }

        direcao = 0;
      }
    }
  }
  // A thread para de executar quando todas as pessoas do sentido 0 já passaram pela escada
  pthread_exit(NULL);
}

// Função de thread que é executada para a fila 1
void *threadFila1(void *f) {
  // O parametro da função é um struct Fila, contendo os dados de cada pessoa
  Fila *fila = (Fila *)f;

  // Executa a repetição até que todas as pessoas da direção 1 entrem na escada
  while (pos1 < fila->qtde1) {
    if ((fila->pessoas0[pos0] > fila->pessoas1[pos1] && pos1 < fila->qtde1) || fila->qtde0 == 0 || fila->qtde0 == pos0) {
      printf("Fila 1 - %d\n", fila->pessoas1[pos1]);
      if (fila->pessoas1[pos1] >= tempo) {
        tempo = fila->pessoas1[pos1] + 10;
        pos1++;

        direcao = 1;
      }

      if (pos0 + pos1 == 0) {
        tempo += 10;
        pos1++;
      }

      if (fila->pessoas1[pos1] <= tempo && pos1 < fila->qtde1) {
        if (direcao == 0) {
          while (fila->pessoas1[pos1] <= tempo && pos1 < fila->qtde1) {
            pos1++;
          }
          fila->pessoas1[pos1 - 1] = tempo;
          tempo += 10;
        }
        while (fila->pessoas1[pos1] <= tempo && pos1 < fila->qtde1) {
          tempo += (fila->pessoas1[pos1] - fila->pessoas1[pos1 - 1]);
          pos1++;
        }

        direcao = 1;
      }
    }
  }
  // A thread para de executar quando todas as pessoas do sentido 1 já passaram pela escada
  pthread_exit(NULL);
}

int main() {
  // Cria dois IDs, um para cada thread
  pthread_t tid1, tid2;

  Fila fila;

  int direcaoInicial;
  scanf("%d", &fila.n);

  fila.pessoas0 = (int *)malloc(fila.n * sizeof(int));
  fila.pessoas1 = (int *)malloc(fila.n * sizeof(int));

  fila.qtde0 = 0, fila.qtde1 = 0;
  while (fila.qtde0 + fila.qtde1 < fila.n) {
    int aux;
    scanf("%d %d", &aux, &direcao);

    if (fila.qtde0 + fila.qtde1 == 0) {
      direcaoInicial = direcao;
    }

    if (direcao == 0) {
      fila.pessoas0[fila.qtde0] = aux;
      fila.qtde0++;
    } else {
      fila.pessoas1[fila.qtde1] = aux;
      fila.qtde1++;
    }
  }

  printf("\n");
  direcao = direcaoInicial;

  if (direcaoInicial == 0) {
    tempo = fila.pessoas0[0];
  } else {
    tempo = fila.pessoas1[0];
  }

  // Cria uma thread para cada sentido, a thread do sentido 0 chama a função
  // para o sentido 0 e a thread do sentido 1 chama a função para o sentido 1
  pthread_create(&tid1, NULL, threadFila0, (void *)&fila);
  pthread_create(&tid2, NULL, threadFila1, (void *)&fila);

  // Espera a execução das duas threads 
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("\nTempo = %d\n", tempo);

  free(fila.pessoas0);
  free(fila.pessoas1);

  return 0;
}
