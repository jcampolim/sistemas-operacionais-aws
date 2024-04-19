# Proj 1

* Resolução do problema E da maratona de programação de 2021
* Solução usando processos
* Solução usando threads

### Perguntas

#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

Em ambas soluções a estratégia usada para evitar que duas pessoas acessem a escada rolante ao mesmo tempo foi parecida. No código usando processos,
foram criados dois processos filhos, um para cada sentido da escada. Depois disso, cada processo entra em uma repetição até que todas as pessoas do seu sentido 
acessem a escada rolante; dentro dessa repetição, há uma série de condições que garatem que somente pessoas de um único sentido estão acessando a escada.

No código usando threads algo muito semelhante ocorre, uma vez que são criadas duas threads (uma para cada sentido da escada rolante), cada thread 
também executa uma repetição até que todas as pessoas tenham acessado a escada e um conjunto de condições dentro da repetição impede que pessoas de sentidos opostos
acessem a escada ao mesmo tempo.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

O código utilizando processos e o código utilizando threads possuem a mesma ideia ao criar um processo filho ou uma thread para cada sentido e executar
uma repetição em cada processo filho ou thread. A primeira coisa nessa repetição é uma condição, que verifica se a próxima pessoa da fila que está no sentido do 
processo ou da thread em questão é a próxima pessoa que pode entrar na escada. Se sim, são realizadas uma série de condições para encontrar a quantidade 
de tempo que deverá ser adicionada ao funcionamento da escada. Se não, a repetição continua sendo executada até que os valores sejam alterados (mudando a 
pessoa que seria a próxima a entrar na escada) pelo outro processo filho ou outra thread.

Dessa forma, duas direções nunca estão ativas ao mesmo tempo.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

Na implementação do código usando processos, foram criados dois processos filhos para representar cada direção da escada rolante. Esses dois processos são
executados simultaneamente e eles se comunicam por meio da memória compartilhada; dessa forma, eles conseguem se comunicar para ver qual pessoa é a próxima a 
entrar na escada e qual é o valor do tempo atual. Na implementação utilizando threads a estratégia é a mesma: foram criadas duas threads, uma para cada 
sentido da escada e elas são executadas simultaneamente.

A primeira diferença entre as soluções é que as threads já possuem memória compartilhada, então não foi preciso criar uma região compartilhada para a 
comunicação entre threads; já os dois processos filhos precisaram desse recurso para conseguir trocar informações. 

Outra diferença é que, no código de processos, os processos foram executados dentro da `main` e, como eles começam a executar a partir do ponto do `fork`, não
foi preciso enviar os dados de chegada de cada pessoa. O contrário acontece na execução das threads; já que, quando elas são criadas, elas executam alguma 
função específica e todos os dados precisam ser passados como parametro dessa função, o que acaba sendo um pouco mais trabalhoso. 

Além disso, para a comunicação entre threads ser eficiente (sem o uso de sinais, por exemplo), é preciso usar variáveis globais no código, algo que não é preciso
na implementação de processos.

Avaliando essas diferenças, a solução utilizando threads é mais eficiente para resolver o problema, isso porque com as threads a memória já é compartilhada e 
não é preciso forçar o compartilhamento em uma estrutura caracterizada pelo não compartilhamento de memória. O único problema da utilização de threads seria
para passar vários valores como parametro, mas isso pode ser facilmente resolvido com um struct.

### Lógica

A estratégia usada para resolver o problema foi a utilização duas filas, uma para cada sentido da escada. Como a linguagem C não possui uma implementação
pronta para essa estrutura de dados, o grupo optou por utilizar dois vetores estáticos para simular o funcionamento das filas, isso foi feito com ajuda 
de duas variáveis de controle: uma indicando qual é o próximo elemento e outra armazenando o tamanho da fila.

Depois de ler e armazenar cada dado, as duas filas são percorridas em ordem. Então, primeiro é avaliado qual é o sentido da primeira pessoa da fila, isso vai 
determinar qual bloco de código será executado, o bloco da direção 0 ou o bloco da direção 1. Os dois blocos são espelhados e possuem exatamente o mesmo algoritmo:

1 . Verifica se o tempo de chegada da pessoa é maior que o tempo total de funcionamento da escada. Se sim, o tempo da escada é o tempo de chegada somado 10 do
tempo de funcionamento.

2 . Verifica se a pessoa é a primeira a entrar na escada. Se sim, o tempo de funcionamento da escada é o tempo de chegada da primeira pessoa somado a 10.

3 . Verifica se o tempo de chegada da próxima pessoa da fila é menor que o tempo total de funcionamento da escada. Se sim, há uma outra verificação: se o 
sentido da escada era o sentido contrário ao sentido atual. Se sim, todas as pessoas que chegaram antes da escada rolante trocar de sentido podem entrar juntas 
e é somado 10 ao tempo total da escada. Independentemente do resultado da ultima condição, o programa vai procurar por pessoas que chegaram na escada quando
já tinha alguém no mesmo sentido; nesse caso, é somado a diferença entre o tempo da última pessoa que entrou na escada e da nova pessoa que está entrando 
na escada.

Esse algoritmo funciona para todos os casos testes fornecidos pelo professor.

### Processos



#### Threads



