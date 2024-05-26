# Proj 2

* Abordar o problema da concorrência
* Desenvolver um programa de computador que consuma as chamadas de um programa do sistema operacional
* conhecer e utilizar de forma ótima as chamadas de um programa do sistema operacional

### Código

Para solucionar o problema proposto pelo professor, o grupo desenvolveu o seguinte código:

// prints

> Obs.: para executar o código é preciso executar o comando `gcc -pthread -o codigo` no terminal

#### Explicação

A estratégia escolhida foi o uso de `pthreads` implementadas com o `mutex` para controlar a ordem na qual cada thread tem acesso aos saldos de cada conta. 

Logo nas primeiras linhas, são definidos dois tipos de dados: `Conta` e `Transação`, o primeiro armazena informações relevantes de cada conta, como o saldo, e o segundo guarda as informações de cada transação, como o valor, 
quem está recebendo e quem está perdendo dinheiro. É dentro da função `main` que esses dados são atribuidos e, para exemplificar a execução, há duas repetições que executam 50 vezes cada que chamam cada uma uma thread para
realizar a transação, totalizando 100 threads realizando transações simultaneamente.

A função que executa as threads é a `tranferencia`. Nessa função, a primeira coisa que é feita é bloquear o acesso de outras threads às variáveis das contaa usando o `mutex` para impedir que mais de uma thread 
acesse e modifique o saldo das contas ao mesmo tempo. É crucial garantir que o acesso às contas seja bloqueado sempre na mesma ordem para evitar deadlocks, uma situação em que duas ou mais threads bloqueiam 
mutuamente os recursos necessárias para continuar a execução.

Depois de bloquear o acess, a transação é realizada e o acesso às contas é desbloqueado.

#### Execução

Para exemplificar, foram criadas duas contas, `conta1` e `conta2`, com os saldos iniciais de 2000 e 1000, respectivamente. Então, são feitas 50 transações de valores variados da `conta1` para a `conta2` e mais 50 
transações de valores variados da `conta2` para a `conta1`.

Como todas as threads para realizar as transações são criadas praticamente o mesmo tempo, é o escalonador que decide qual thread irá executar primeiro. Podendo causar algumas diferenças a cada execução do código.
Isso porque o valor da `conta2` não é o suficiente para cobrir todas as transações, resultando em variações no saldo final após a execução completa do programa.
