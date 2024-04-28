#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Defineos valores das dimenções das matrizes
#define N 3  // Coluna(s) da matriz A e linha(s) da matriz B
#define M 3  // Linha(s) da matriz A
#define P 1  // Coluna(s) da matriz B

// Variável glolbal para armazenar a matriz C de resultado da multiplicação
int c[M][P];

// Struct que guarda a matriz A, o vetor B e qual linha deverá ser multiplicada
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

  // Define os valores das matriz A e do vetor B
  int a[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int b[N][P] = {{1}, {2}, {3}};

  // Passa os valores da matriz A para a matriz A do struct Matrizes
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      m.a[i][j] = &a[i][j];
    }
  }

  // Passa os valores da matriz B para o vetor B do struct Matrizes
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
