#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Defineos valores das dimenções das matrizes
#define N 2  // Colunas da matriz A e linhas da matriz B
#define M 2  // Linhas da matriz A
#define P 3  // Colunas da matriz B

// Variável glolbal para armazenar a matriz C de resultado da multiplicação
int c[M][P];

// Struct que guarda a matriz A, a matriz B e qual linha deverá ser multiplicada
typedef struct {
  int *a[M][N];
  int *b[N][P];
  int linha;
} Matrizes;

// Função da thread que realiza a multiplicação de uma linha especifica 
void *multiplicaLinha(void *t) {
  Matrizes *m = (Matrizes *)t;

  for(int i = 0; i < P; i++) {
    for(int j = 0; j < N; j++) {
      c[m->linha][i] = c[m->linha][i] + ((*m->a[m->linha][j]) * (*m->b[j][i]));
    }
  }
}

int main() {
  Matrizes m;

  // Define os valores das matrizes A e B
  int a[M][N] = {{3, 2}, {5, -1}};
  int b[N][P] = {{6, 4, -2}, {0, 7, 1}};

  // Passa os valores da matriz A para a matriz A do struct Matrizes
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      m.a[i][j] = &a[i][j];
    }
  }

  // Passa os valores da matriz B para a matriz B do struct Matrizes
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < P; j++) {
      m.b[i][j] = &b[i][j];
    }
  }

  // Define os valores iniciais da matriz C como zero
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < P; j++) {
      c[i][j] = 0;
    }
  }

  // Cria um array para armazenar o ID de cada thread 
  pthread_t tid[M];

  // Cria as threads para realizar a multiplicação de cada linha da matriz A
  for(int i = 0; i < M; i++) {
    m.linha = i;
    pthread_create(&tid[i], NULL, multiplicaLinha, &m);
    pthread_join(tid[i], NULL);
  }

  // Imprime a matriz C com o resultado da multiplicação
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < P; j++) {
      printf("%d ", c[i][j]);
    }
    printf("\n");
  }

  return 0;
}
