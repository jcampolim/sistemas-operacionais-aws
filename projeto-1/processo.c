#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int tempo = 0;

int main() {
  int n, direcaoInicial;
  scanf("%d", &n);

  int *pessoas0 = (int *)malloc(n * sizeof(int));
  int *pessoas1 = (int *)malloc(n * sizeof(int));

  // Cria um espaço de memória compartilhado para as variáveis que guardam os valores 
  // do tempo total da escada, do topo de cada fila e da direção atual da escada
  key_t key = 1234, key0 = 4567, key1 = 7890, keyD = 1470;

  int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT | SHM_R | SHM_W);
  int *tempo = (int *)shmat(shmid, (void *)0, 0);

  int shmid0 = shmget(key0, sizeof(int), 0666 | IPC_CREAT | SHM_R | SHM_W);
  int *pos0 = (int *)shmat(shmid0, (void *)0, 0);

  int shmid1 = shmget(key1, sizeof(int), 0666 | IPC_CREAT | SHM_R | SHM_W);
  int *pos1 = (int *)shmat(shmid1, (void *)0, 0);

  int shmidD = shmget(keyD, sizeof(int), 0666 | IPC_CREAT | SHM_R | SHM_W);
  int *direcao = (int *)shmat(shmidD, (void *)0, 0);

  int qtde0 = 0, qtde1 = 0;
  while (qtde0 + qtde1 < n) {
    int aux;
    scanf("%d %d", &aux, direcao);

    if (qtde0 + qtde1 == 0) {
      direcaoInicial = *direcao;
    }

    if (*direcao == 0) {
      pessoas0[qtde0] = aux;
      qtde0++;
    } else {
      pessoas1[qtde1] = aux;
      qtde1++;
    }
  }

  printf("\n");
  if (direcaoInicial == 0) {
    *tempo = pessoas0[0];
  } else {
    *tempo = pessoas1[0];
  }

  *pos0 = 0, *pos1 = 0;
  *direcao = direcaoInicial;

  // Cria dois IDs, um para cada processo que será criado
  pid_t pid0, pid1;

  // Cria o processo filho para a direção 0
  pid0 = fork();
  // Caso ocorra algum erro na criação do processo filho
  if (pid0 < 0) {
    perror("Erro ao criar o processo filho para a direção 0");
    exit(1);
  // Processo filho 0 em execução
  } else if (pid0 == 0) {
    // Executa a repetição até que todas as pessoas da direção 0 entrem na escada
    while (*pos0 < qtde0) {
      if ((pessoas0[*pos0] < pessoas1[*pos1] && *pos0 < qtde0) || qtde1 == 0 ||
          qtde1 == *pos1) {
        printf("Fila 0 - %d\n", pessoas0[*pos0]);
        if (pessoas0[*pos0] >= *tempo) {
          *tempo = pessoas0[*pos0] + 10;
          *pos0 = *pos0 + 1;

          *direcao = 0;
        }

        if (*pos0 + *pos1 == 0) {
          *tempo = *tempo + 10;
          *pos0 = *pos0 + 1;
        }

        if (pessoas0[*pos0] <= *tempo && *pos0 < qtde0) {
          if (*direcao == 1) {
            while (pessoas0[*pos0] <= *tempo && *pos0 < qtde0) {
              *pos0 = *pos0 + 1;
            }
            pessoas0[*pos0 - 1] = *tempo;
            *tempo = *tempo + 10;
          }
          while (pessoas0[*pos0] <= *tempo && *pos0 < qtde0) {
            *tempo = *tempo + (pessoas0[*pos0] - pessoas0[*pos0 - 1]);
            *pos0 = *pos0 + 1;
          }

          *direcao = 0;
        }
      }
    }
    // O processo filho 0 para de executar quando todas as pessoas do sentido 0 já passaram pela escada
    exit(0);
  // Processo pai em execução
  } else {
    // Cria um novo processo filho para a direção 1
    pid1 = fork();

    // Caso ocorra algum erro na criação do processo filho
    if (pid1 < 0) {
      perror("Erro ao criar o processo filho para a direção 1");
      exit(1);
    // Processo filho 1 em execução
    } else if (pid1 == 0) {
      // Executa a repetição até que todas as pessoas da direção 1 entrem na escada
      while (*pos1 < qtde1) {
        if ((pessoas0[*pos0] > pessoas1[*pos1] && *pos1 < qtde1) ||
            qtde0 == 0 || qtde0 == *pos0) {
          printf("Fila 1 - %d\n", pessoas1[*pos1]);
          if (pessoas1[*pos1] > *tempo) {
            *tempo = pessoas1[*pos1] + 10;
            *pos1 = *pos1 + 1;

            *direcao = 1;
          }

          if (*pos0 + *pos1 == 0) {
            *tempo = *tempo + 10;
            *pos1 = *pos1 + 1;
          }

          if (pessoas1[*pos1] <= *tempo && *pos1 < qtde1) {
            if (*direcao == 0) {
              while (pessoas1[*pos1] <= *tempo && *pos1 < qtde1) {
                *pos1 = *pos1 + 1;
              }
              pessoas1[*pos1 - 1] = *tempo;
              *tempo = *tempo + 10;
            }
            while (pessoas1[*pos1] <= *tempo && *pos1 < qtde1) {
              *tempo = *tempo + (pessoas1[*pos1] - pessoas1[*pos1 - 1]);
              *pos1 = *pos1 + 1;
            }

            *direcao = 1;
          }
        }
      }
      // O processo filho 1 para de executar quando todas as pessoas do sentido 1 já passaram pela escada
      exit(0);
    }
  }

  // Processo pai espera os dois processos filhos terminarem de executar
  wait(NULL);
  wait(NULL);

  // Exibe a variável tempo
  printf("\nTempo = %d\n", *tempo);

  // Desassocia os segmentos de memória compartilhada
  shmdt(tempo);
  shmdt(pos0);
  shmdt(pos1);
  shmdt(direcao);

  free(pessoas0);
  free(pessoas1);

  return 0;
}
