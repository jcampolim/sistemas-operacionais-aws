# Lab 2

* Exemplo na linguagem C onde os processos pai e filho troquem algum tipo de mensagem

### Criação do arquivo fork.c

Para testar a utilização do `fork`, o grupo usou o seguinte código apresentado em aula: 

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img1.jpg)

O código cria um processo pai e um processo filho, além de uma variável chamada `value` que é inicializada com 5. O primeiro processo a ser executado é processo filho que aumenta o valor de `value` em 
15 unidades e exibe na tela esse valor. Logo após a execução do filho, o processo pai termina a sua execução exibindo o valor de `value`, que permanece 5, mostrando assim que os dois processos não se comunicam.

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img2.jpg)

### Fazendo a comunicação através de pipes

Alteramos o código para que os processos se conversem utilizando pipes. Uma pipe é uma via de comunição entre dois processos relacionados, onde os processos podem escrever (`write()`) e ler (`read()`) mensagens.

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img3.jpg)

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img4.jpg)

Assim, quando executamos, a variável `value` exibida na execução do processo pai é 20, mostrando que houve a comunicação entre os dois processos.

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img5.jpg)

### Arquivos enviados para o GitHub

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab2-img6.jpg)
