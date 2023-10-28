**Relatório de Análise de Desempenho com OpenMP**

## Implementação do Crivo de Eratóstenes

### Introdução
Este relatório apresenta uma análise detalhada da implementação do Crivo de Eratóstenes, um algoritmo para encontrar todos os números primos menores ou iguais a um determinado número inteiro, utilizando diretivas do OpenMP para programação paralela. O estudo foi realizado como parte do segundo trabalho da disciplina de Programação Paralela e Distribuída, sob a orientação do Professor Gabriel P. Silva, do Bacharelado em Ciência da Computação da DCC/IM-UFRJ.

### Implementação do Código
O programa implementa o Crivo de Eratóstenes, utilizando o OpenMP para explorar paralelismo. O código é capaz de calcular o total de números primos entre 2 e um valor N dado. A seção crítica do código utiliza as diretivas `#pragma omp parallel for` e `#pragma omp parallel for reduction(+: count)` para paralelizar as operações de marcação dos múltiplos dos números primos e a contagem total de números primos, respectivamente.

### Resultados Obtidos
Os resultados do experimento foram registrados em termos de tempo de execução para diferentes quantidades de threads. Para avaliar o desempenho do programa, foram realizadas execuções com 1, 8, 16, 32 e 64 threads, enquanto o valor de N foi fixado em 3.000.000.000.

A tabela abaixo apresenta os tempos médios de execução para cada quantidade de threads:

| Quantidade de Threads | Tempo Médio de Execução (s) |
|-----------------------|-----------------------------|
| 1                     | 303.719804                  |
| 8                     | 49.4911954                  |
| 16                    | 42.0886968                  |
| 32                    | 41.89357                    |
| 64                    | 42.3905722                  |

### Análise de Desempenho
Observa-se uma clara redução no tempo de execução à medida que o número de threads aumenta. O speed-up obtido com a utilização de múltiplas threads é significativo, especialmente ao comparar com a execução sequencial. Os valores de speed-up e eficiência podem ser calculados utilizando a fórmula padrão:

Speed-up = Tempo Sequencial / Tempo Paralelo

Eficiência = Speed-up / Número de Threads

| Quantidade de Threads | Speed-up            | Eficiência          |
|-----------------------|---------------------|---------------------|
| 8                     | 6.13684518          | 0.76710564          |
| 16                    | 7.21618456          | 0.45101153          |
| 32                    | 7.24979523          | 0.22655610          |
| 64                    | 7.16479604          | 0.11194993          |


## Implementação de Gauss-Seidel SOR

### Introdução
Este relatório apresenta uma análise detalhada da implementação do método Gauss-Seidel SOR (Successive Over-Relaxation) para a simulação 2-D de transferência de calor em uma placa de metal NxN. O estudo foi realizado como parte do segundo trabalho da disciplina de Programação Paralela e Distribuída, ministrada pelo Professor Gabriel P. Silva, no Bacharelado em Ciência da Computação da DCC/IM-UFRJ.

### Implementação do Código
O código implementa o método Gauss-Seidel SOR para simular a transferência de calor em uma placa de metal. O programa utiliza diretivas do OpenMP para paralelizar as operações, proporcionando ganhos significativos de desempenho. A inicialização da placa, cálculos de iterações e a impressão dos resultados foram devidamente implementados.

### Resultados Obtidos
Os resultados das execuções do programa para diferentes números de threads foram registrados e analisados. O tempo médio de execução para cada quantidade de threads foi medido e apresentado na tabela a seguir:

| Quantidade de Threads | Tempo Médio de Execução (s) |
|-----------------------|-----------------------------|
| 1                     | 123.117883                  |
| 8                     | 15.231531                   |
| 16                    | 7.4021918                   |
| 32                    | 3.7494544                   |
| 64                    | 1.9766852                   |

### Análise de Desempenho
Observa-se uma clara redução no tempo de execução à medida que o número de threads aumenta. O speed-up obtido com a utilização de múltiplas threads é bastante expressivo, evidenciando os benefícios da programação paralela. Além disso, os valores de speed-up e eficiência podem ser calculados para uma análise mais aprofundada do desempenho.

| Quantidade de Threads | Speed-up       | Eficiência       |
|-----------------------|----------------|------------------|
| 8                     | 8.08309309     | 1.01038663       |
| 16                    | 16.63262535    | 1.03953908       |
| 32                    | 32.83621291    | 1.02613165       |
| 64                    | 62.28502292    | 0.97320348       |


## Conclusão

Os experimentos realizados, tanto com a implementação paralela do método Gauss-Seidel SOR para a simulação de transferência de calor em uma placa de metal, quanto com a programação paralela no algoritmo do Crivo de Eratóstenes, evidenciaram claramente os benefícios do paralelismo na redução do tempo de execução e no aumento da eficiência computacional. Em ambos os casos, o aumento no número de threads resultou em uma melhoria significativa no desempenho, destacando a importância da utilização de técnicas de programação paralela em cenários nos quais a demanda por processamento é elevada. No entanto, é crucial levar em consideração os possíveis custos adicionais associados à coordenação entre threads e ao gerenciamento de memória compartilhada, a fim de otimizar ainda mais o desempenho em ambientes computacionais complexos.