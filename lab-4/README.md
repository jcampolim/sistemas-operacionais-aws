# Lab 4

* Solução usando `pthreads` para resolver o problema da multiplicação matriz-vetor

### Criação dos arquivos

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img1.jpg)

### Código

O seguinte código foi desenvolvido pelo grupo:

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img2.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img3.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img4.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img5.jpg)

A estratégia usada pelo grupo foi criar uma thread para multiplicar cada linha da matriz A. Os valores da matriz A e do vetor B estão definidos dentro do código; então,
para alterá-los, é preciso modificar seus valores dentro do algoritmo. Também é possível modificar esses valores para transformar o vetor B em uma matriz e resolver uma multiplicação de matrizes.

> Obs.: para a compilação do código é necessário usar o comando `gcc -pthread thread.c -o thread` e depois executar o arquivo `thread`.

### Execução

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/lab4-img6.jpg)
