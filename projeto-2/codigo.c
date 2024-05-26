#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define o número máximo de threads que podem ser executadas simultaneamente
#define MAXN 100

// Estrutura para armazenar os dados de cada conta
typedef struct {
  int saldo;
  pthread_mutex_t lock;
} Conta;

// Estrutura para armazenar os dados de cada transação
typedef struct {
  int value;
  Conta *from;
  Conta *to;
} Transacao;

// Cria duas contas genéricas que serão usadas como exemplo
Conta conta1;
Conta conta2;

// Função que executa a transação
void *transferencia(void *args) {
  Transacao *t = (Transacao *)args;

  // Usa o mutex para bloquear o acesso de outras threads ao saldo das duas
  // contas
  pthread_mutex_lock(&conta1.lock);
  pthread_mutex_lock(&conta2.lock);

  // Verifica se a conta from possui salto suficiente para realizar a transação
  if (t->from->saldo >= t->value) {
    // Se sim, a transação é realizada e exibe na tela o saldo atualizado das
    // contas
    t->from->saldo -= t->value;
    t->to->saldo += t->value;

    printf("\nTransferência realizada com sucesso!\n");
    printf("From: %d\n", t->from->saldo);
    printf("To: %d\n", t->to->saldo);
  } else {
    // Se não, exibe na tela uma mensagem de erro
    printf("\nNão há saldo suficiente para realizar a transferência!\n");
  }

  // Desbloqueia o acesso às contas
  pthread_mutex_unlock(&conta1.lock);
  pthread_mutex_unlock(&conta2.lock);

  // Libera o espaço de memória alocada para os dados da transação e sinaliza o
  // final da thread
  free(t);
  pthread_exit(NULL);
}

int main() {
  // Cria um vetor para armazenar o ID de todas as threads que serão criadas
  pthread_t tid[MAXN];

  // Inicializa o saldo das contas
  conta1.saldo = 2000;
  conta2.saldo = 1000;

  Transacao **t = (Transacao **)malloc(MAXN * sizeof(Transacao *));

  // Inicia o mutex das contas
  pthread_mutex_init(&conta1.lock, NULL);
  pthread_mutex_init(&conta2.lock, NULL);

  // Repetição que cria as threads para realizar as transações
  for (int i = 0; i < 50; i++) {
    t[i] = (Transacao *)malloc(sizeof(Transacao));
    t[i]->value = i + 1;
    t[i]->from = &conta1;
    t[i]->to = &conta2;
    pthread_create(&tid[i], NULL, transferencia, (void *)t[i]);
  }

  for (int i = 50; i < 100; i++) {
    t[i] = (Transacao *)malloc(sizeof(Transacao));
    t[i]->value = i + 1;
    t[i]->from = &conta2;
    t[i]->to = &conta1;
    pthread_create(&tid[i], NULL, transferencia, (void *)t[i]);
  }

  // Espera todas as threads terminarem de executar
  for (int i = 0; i < 100; i++) {
    pthread_join(tid[i], NULL);
  }

  // Exibe os saldos finais
  printf("\nSaldos finais: \n");
  printf(" From: %d\n", conta1.saldo);
  printf(" To: %d\n", conta2.saldo);

  // Destroi os mutex de cada conta
  pthread_mutex_destroy(&conta1.lock);
  pthread_mutex_destroy(&conta2.lock);

  free(t);
  
  return 0;
}

