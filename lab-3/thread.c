#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#define FIBER_STACK 1024*64 // 64kB stack

int value = 5;

// função chamada automaticamente quando o sinal SIGUSR1 é recebido
void handle_signal(int signal) {
    if(signal == SIGUSR1) {
        value += 15;
    }
}

// the child thread will execute this function
int threadFunction(void* argument) {
    printf("child thread exiting\n");
    // envia o sinal (passando o pid e o sinal escolhido)
    kill(getppid(), SIGUSR1);

    return 0;
}

int main() {
    void* stack;
    pid_t pid;

    // configura o sinal como o SIGUSR1 e a sua função como handle_signal
    signal(SIGUSR1, handle_signal);

    // allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("- initial value of the variable: %d\n", value);
    printf("\ncreating child thread\n");

    // call the clone system call to create the child thread
    pid = clone(&threadFunction, (char*) stack + FIBER_STACK,
    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    if (pid == -1) {
        perror("clone");
        exit(2);
    }

    // esperando até o valor da variável ser atualizado
    while(value == 5) {
        printf("...\n");
        sleep(50000);
    }

    // sinal recebido
    printf("\nreceived signal!\n");
    printf("\n- update variable value: %d\n", value);

    // wait for the child thread to exit
    pid = waitpid( pid, 0, 0 );
    if (pid == -1) {
        perror("waitpid");
        exit(3);
    }

    // Free the stack
    free(stack);
    printf("child thread returned and stack freed.\n");

    return 0;
} 
