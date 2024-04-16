# Proj 1

* Resolução do problema E da maratona de programação de 2021
* Solução usando processos
* Solução usando threads

### Perguntas

#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

A estratégia usada para evitar que duas pessoas acessem a escada rolante ao mesmo tempo foi inicialmente ler os valores de todas as pessoas e armazená-lo em duas filas, uma fila para cada direção. Porém, a
linguagem C não possui nenhuma biblioteca com uma fila já implementada, então o grupo optou por fazer uma matriz de duas linhas, uma para cada fila, e simular o comportamento dessa estrutura de dados utilizando 
duas variáveis de controle, uma seria o tamanho da fila, enquanto a outra a posição do elemento que está no topo.

Após ter os dados devidamente armazenados, o próximo passo é percorrer as duas filas respeitando a ordem de chegada de cada pessoa. 

Então, primeiro é feita a comparação de qual topo é menor, indicando qual pessoa chegou primeiro. Depois, é feita uma análise para verificar se as próximas pessoas dessa fila conseguem entrar na
escada antes que a escada mude de direção. Quando todas as pessoas disponíveis já entraram na escada, então a escada inverte a direção e repete todo o processo para o outro sentido. 

Esse algoritmo garante que duas pessoas de sentidos contrários nunca usem a escada ao mesmo por fazer a análise individual de cada pessoa, respeitando não apenas a ordem de chegada, como também a ordem de prioridade.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Como o código faz a análise individual de cada pessoa, nunca terão duas pessoas sendo executadas ao mesmo tempo, então só haverá uma direção ativa.

Na parte de processos e threads, isso foi garantido, já que a criação dos processos filhos e das threads ocorre somente quando é preciso fazer alguma alteração no valor da variável "tempo" e cada alteração
ocorre separadamente.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

Avaliando a lógica do código, as duas soluções foram parecidas, já que as threads e os processos filhos foram criados para representar cada pessoa no momento de alteração da variável global "tempo". Pórem, 
analisando o código, é possível perceber que o código de threads é muito mais eficiente por conta do compartilhamento de memória, ficando um código mais legível e mais organizado. Além disso, o grupo
optou por fazer o uso de pthreads, facilitando na criação e execução de cada thread.

Já o código de processos é mais extenso, mais poluído visualmente e menos intuitivo de se entender. Em um primeiro momento, para conseguir criar vários processos, o grupo optou por criar um vetor para armazenar o ID de cada processo filho que será criado; além de uma matriz com as pipes, também uma para cada processo filho, que seriam utilizadas na comunição entre o processo pai e o processo filho. Entretanto, o grupo decidiu seguir por outro caminho e fazer uma função que cria cada processo.

Ainda assim, é mais eficiente e menos prolixo fazer a utilização de threads do que de processos.

### Explicação

O grupo utilizou o código abaixo como base para fazer modificações com as implementações de processos e threads: 

```
#include <stdio.h>
#include <stdlib.h>

// Variavel global para aramzenar o tempo que a escada ficou ligada
int tempo = 0;

int main() {
    int n, direcao, direcaoInicial;
    scanf("%d", &n);

    // Cria uma matriz com duas linhas, uma para cada sentido da escada
    // cada linha ira simular uma fila de pessoas
    int **pessoas = (int **)malloc(n * sizeof(int *));
    pessoas[0] = (int *)malloc(n * sizeof(int));
    pessoas[1] = (int *)malloc(n * sizeof(int));

    // Le o tempo e a direção de cada pessoa e armazena a direcao inicial da escada
    int tam[] = {0, 0};
    while(tam[0] + tam[1] < n) {
        int aux;
        scanf("%d %d", &aux, &direcao);

        if(tam[0] + tam[1] == 0) {
            direcaoInicial = direcao;
        }
    
        if(direcao == 0) {
            pessoas[0][tam[0]] = aux;
            tam[0]++;
        } else {
            pessoas[1][tam[1]] = aux;
            tam[1]++;
        }
    }

    // Cria um vetor de inteiros para marcar o topo da fila
    int pos[] = {0, 0};

    // O tempo recebe o valor inicial da primeira pessoa
    tempo = pessoas[direcaoInicial][0];
    direcao = direcaoInicial;

    // Loop que percorre todas as posicoes da matriz
    while(pos[0] < tam[0] || pos[1] < tam[1]) {
        // Se a primeira pessoa da direcao 0 for menor que a primeira pessoa da direcao 1 e a fila 0 nao estiver vazia
        // ou se a fila 1 estiver vazia
        if((pessoas[0][pos[0]] < pessoas[1][pos[1]] && pos[0] < tam[0]) || tam[1] == 0 || tam[1] == pos[1]) {
            // Se o topo da fila for maior que o tempo (o tempo eh o tempo de chegada da pessoa somado ao
            // tempo do percurso da escada)
            if(pessoas[0][pos[0]] >= tempo) {
                tempo = pessoas[0][pos[0]] + 10;
                pos[0]++;
                
                // Atualiza a direcao da escada
                direcao = 0;
            }

            // Se a pessoa do topo for a primeira a entrar na escada (adiciona 10 ao tempo)
            if(pos[0] + pos[1] == 0) {
                tempo += 10;
                pos[0]++;
            }

            // Se o tempo de chegada da pessoa do topo for menor que o tempo e a fila nao estiver vazia
            if(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                // Se a direcao anterior foi 1
                if(direcao == 1) {
                    // Loop para encontrar todas as pessoas que podem entrar juntas na escada 
                    while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                        pos[0]++;
                    }

                    // Atualiza o tempo da pessoa anterior para o instante que ela entrou na escada rolante
                    pessoas[0][pos[0] - 1] = tempo;
                    tempo += 10;
                }
                // Loop para encontrar todas as pessoas que podem entrar na escada aproveitando o intervalo de tempo anterior
                // (no tempo adiciona a diferenca dos tempos de chegada entre a ultima pessoa e a atual)
                while(pessoas[0][pos[0]] <= tempo && pos[0] < tam[0]) {
                    tempo += (pessoas[0][pos[0]] - pessoas[0][pos[0] - 1]);
                    pos[0]++;
                }

                // Atualiza a direcao da escada rolante
                direcao = 0;
            }
        // Se a primeira pessoa da direcao 1 for menor que a primeira pessoa da direcao 0 e a fila 1 nao estiver vazia
        // ou se a fila 0 estiver vazia
        } else if((pessoas[0][pos[0]] > pessoas[1][pos[1]] && pos[1] < tam[1]) || tam[0] == 0 || tam[0] == pos[0]) {
            // Se o topo da fila for maior que o tempo (o tempo eh o tempo de chegada da pessoa somado ao
            // tempo do percurso da escada)
            if(pessoas[1][pos[1]] > tempo) {
                tempo = pessoas[1][pos[1]] + 10;
                pos[1]++;
                
                // Atualiza a direcao da escada rolante
                direcao = 1;
            }

            // Se a pessoa do topo for a primeira a entrar na escada (adiciona 10 ao tempo)
            if(pos[0] + pos[1] == 0) {
                tempo += 10;
                pos[1]++;
            }

            // Se o tempo de chegada da pessoa do topo for menor que o tempo e a fila nao estiver vazia
            if(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                // Se a direcao anterior foi 0
                if(direcao == 0) {
                    // Loop para encontrar todas as pessoas que podem entrar juntas na escada 
                    while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                        pos[1]++;
                    }

                    // Atualiza o tempo da pessoa anterior para o instante que ela entrou na escada rolante
                    pessoas[1][pos[1] - 1] = tempo;
                    tempo += 10;
                }
                // Loop para encontrar todas as pessoas que podem entrar na escada aproveitando o intervalo de tempo anterior
                // (no tempo adiciona a diferenca dos tempos de chegada entre a ultima pessoa e a atual)
                while(pessoas[1][pos[1]] <= tempo && pos[1] < tam[1]) {
                    tempo += (pessoas[1][pos[1]] - pessoas[1][pos[1] - 1]);
                    pos[1]++;
                }

                // Atualiza a direcao da escada rolante
                direcao = 1;
            }
        }
    }

    // Exibe na tela o tempo total de funcionamento da escada rolante
    printf("%d\n", tempo);
    free(pessoas);

    return 0;
}
```


A premissa básica da estratégia para a resolução do problema foi utilizar uma matriz com duas linhas (uma para cada sentido da escada rolante) para simular o funcionamento de uma fila. 
Cada fila foi preenchida com os valores dos tempos de chegada de cada pessoa. Depois disso, a matriz é percorrida uma vez imitando a entrada de cada pessoa na escada; nessa parte, o código possui uma série
de verificações para adicionar a quantidade de segundos certa ao tempo total.

> Obs.: Para mais detalhes da lógica usada, é possível verificar os comentários do código acima.

#### Processos

Para utilizar processos, o grupo optou por fazer cada processo filho como uma pessoa, sendo utilizado para fazer a atualização do tempo. O resultado final da implementação foi: 

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img1.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img2.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img3.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img4.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img5.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img6.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img7.jpg)

> Obs.: Os comentários desse código explicam apenas o funcionamento dos processos dentro da implementação, para mais detalhes da lógica de resolução do problema, verificar os comentários do código base.

Ao executar esse código, o grupo obteve todos os resultados como esperado, inclusive os casos de teste extras.

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img8.jpg)

#### Threads

Para utilizar threads, o grupo optou por fazer cada thread como uma pessoa, então cada thread foi criada com o intuito de atualizar o valor do tempo. O código final é: 

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img9.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img10.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img11.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img12.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img13.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img14.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img15.jpg)
![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img16.jpg)

> Obs.: Os comentários desse código explicam apenas o funcionamento das threads dentro da implementação, para mais detalhes da lógica de resolução do problema, verificar os comentários do código base.

Ao executar esse código, o grupo obteve todos os resultados como esperado, inclusive os casos de teste extras.

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img17.jpg)

#### Git 

##### Criação dos arquivos

![](https://github.com/jcampolim/sistemas-operacionais-aws/blob/main/img/proj1-img18.jpg)
