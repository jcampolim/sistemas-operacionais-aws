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

Então primeiro é feita a comparação de qual topo é menor, indicando qual pessoa chegou primeiro. Depois, é feita uma análise para verificar se as próximas pessoas dessa fila conseguem entrar na
escada antes que a escada mude de direção. Quando todas as pessoas disponíveis já entraram na escada, então a escada inverte a direção e repete todo o processo para o outro sentido. 

Esse algoritmo garante que duas pessoas nunca usem a escada ao mesmo por fazer a analise individual de cada pessoa, respeitando não apenas a ordem de chegada, como também a ordem de prioridade.

#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

Como o código faz a análise individual de cada pessoa, nunca terão duas pessoas sendo executadas ao mesmo tempo, então só haverá uma direção ativa.

Na parte de processos e threads, isso foi garantido, já que a criação dos processos filhos e das threads ocorre somente quando é preciso fazer alguma alteração no valor da variável "tempo" e cada alteração
ocorre separadamente.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

Avaliando a lógica do código, as duas soluções foram parecidas, já que as threads e os processos filhos foram criados para representar cada pessoa no momento de alteração da variável global "tempo". Pórem, 
analisando o código, é possível perceber que o código de threads é muito mais eficiente por conta do compartilhamento de memória, ficando um código mais legivel e mais organizado. Além disso, o grupo
optou por fazer o uso de pthreads, facilitando na criação e execução de cada thread.

Já o código de processos é mais extenso e com muitos trechos de grandes repetições, deixando o código mais poluído visualmente e menos intuitivo de se entender. Para conseguir criar vários processos, 
foi necessário criar um vetor para armazenar o ID de cada processo filho que será criado; além de uma matriz com as pipes, também uma para cada processo filho, que são utilizadas na comunição entre o processo 
pai e o processo filho. 
