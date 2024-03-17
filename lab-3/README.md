# Lab 3

* Representar a troca de informações de contexto entre a thread e o processo pai.

### Criação do arquivo thread.c

Para realizar a troca de informações entre a thread e o processo filho, o grupo optou em adaptar o código passado em aula pelo professor utilizando sinais.

* Criação do arquivo:

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img1.jpg)

* Escrita do código utilizando o editor `nano`:

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img2.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img3.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img4.jpg)

### Fazendo a comunicação através de sinais

Ao executar o código, temos a seguinte tela:

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img5.jpg)

Na execução, uma variável `value` foi iniciada com 5 e incrementada para 20 quando a thread foi chamada. Podemos ver que essa alteração ocorre com sucesso devido 
ao uso de sinais. Assim, quando a thread é criada, ela chama o sinal `SIGUSR1` chamando automaticamente a função `handle_signal` que irá alterar o valor da variável.

A comunicação entre o sinal e a função ocorre devido ao comando `signal(SIGUSR1, handle_signal);`, que associa os dois, fazendo que quando o sinal seja chamado
a função seja invocada.

### Arquivos enviados para o GitHub

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img6.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab3-img7.jpg)
