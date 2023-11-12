# distribute parallel for

## #pragma omp parallel

A diretiva `#pragma omp parallel` é utilizada para criar uma região paralela em um programa, permitindo que várias threads executem um bloco de código simultaneamente. 

A diretiva `#pragma omp parallel` é usada para criar uma equipe (ou time) de threads. Ela delimita uma região paralela do código, indicando que o bloco de código dentro dessa região deve ser executado por várias threads.

**Funcionamento:**
   - Quando um programa atinge uma região paralela delimitada por `#pragma omp parallel`, uma equipe de threads é criada para executar o bloco de código dentro dessa região.
   - Cada thread na equipe executa independentemente o código dentro da região paralela.
   - Após a conclusão da região paralela, as threads se juntam novamente em uma única thread.

**Aplicação:**
   - **Divisão de Tarefas:** A diretiva `#pragma omp parallel` é frequentemente utilizada quando há tarefas independentes que podem ser executadas simultaneamente por várias threads para acelerar a execução do programa.
   - **Loops Paralelos:** É comum usar a diretiva `#pragma omp parallel` em conjunto com diretivas como `#pragma omp for` para paralelizar a execução de loops, distribuindo as iterações entre as threads.
   - **Melhoria de Desempenho:** A aplicação mais comum é a melhoria do desempenho em sistemas com múltiplos núcleos ou processadores, onde a execução simultânea de tarefas pode levar a uma redução no tempo de processamento.

Exemplo em C usando OpenMP:

```c
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, world! This is thread %d.\n", thread_id);
    }

    return 0;
}
```

Neste exemplo, a função `omp_get_thread_num()` retorna o ID da thread, permitindo que cada thread imprima sua identificação. O bloco dentro de `#pragma omp parallel` será executado por todas as threads na equipe paralela.

## #pragma omp for

A diretiva `#pragma omp for` é usada para distribuir automaticamente iterações de loops entre várias threads, permitindo a execução paralela do loop.

**Funcionamento:**
Quando você adiciona `#pragma omp for` antes de um loop, o compilador OpenMP automaticamente divide as iterações do loop entre as threads disponíveis no sistema. Cada thread executa um conjunto diferente de iterações, distribuindo assim a carga de trabalho e acelerando a execução do loop. É importante notar que a execução paralela é eficaz principalmente quando as iterações do loop são independentes entre si, pois isso evita conflitos de dados e torna mais fácil a execução concorrente.

**Aplicação:**
A aplicação típica da diretiva `#pragma omp for` é em loops onde as iterações podem ser executadas independentemente umas das outras. Exemplos incluem loops em cálculos numéricos, processamento de matrizes, ou qualquer situação em que cada iteração não dependa dos resultados das outras.

Aqui está um exemplo simples em C++:

```cpp
#include <stdio.h>
#include <omp.h>

int main() {
    const int size = 100000;
    int array[size];

    // Inicializa o array
    for (int i = 0; i < size; ++i)
        array[i] = i;

    // Uso da diretiva pragma omp for para paralelizar o loop
    #pragma omp parallel for
    for (int i = 0; i < size; ++i)
        array[i] = array[i] * 2;

    // Imprime alguns valores do array
    for (int i = 0; i < 10; ++i) 
        printf("array[%d] = %d", i, array[i]);

    return 0;
}
```

Neste exemplo, a diretiva `#pragma omp for` é usada para paralelizar o loop, e cada thread é atribuída a uma parte do array para multiplicar por 2. Note que o código paralelo deve ser cuidadosamente projetado para evitar problemas de concorrência, como condições de corrida.

## #pragma omp distribute

A diretiva `#pragma omp distribute` é utilizada para indicar a distribuição de um loop aninhado em uma região paralela. Isso significa que o loop aninhado será distribuído entre as equipes de threads, permitindo que cada equipe de threads execute uma parte específica do loop. Isso pode ser útil para distribuir a carga de trabalho entre as equipes de threads e, assim, melhorar o desempenho em arquiteturas paralelas.

**Funcionamento:**
O funcionamento básico da diretiva `#pragma omp distribute` envolve a distribuição dos ciclos do loop aninhado entre as equipes de threads. A distribuição ocorre com base no esquema de distribuição especificado, como `static`, `dynamic`, `guided`, etc. Cada equipe de threads é responsável por executar uma parte do loop, melhorando assim a utilização de recursos paralelos.

### Aplicação:
A diretiva `#pragma omp distribute` é útil quando você tem loops aninhados e deseja distribuir a carga de trabalho entre as equipes de threads para melhorar o paralelismo. Isso é especialmente relevante em arquiteturas paralelas, como multiprocessadores ou GPUs, onde a capacidade de distribuir tarefas entre os vários núcleos ou unidades de processamento pode resultar em um desempenho significativamente melhor.

## #pragma omp distribute parallel for

A construção `distribute parallel for` é uma diretiva fornecida pela OpenMP para facilitar a programação paralela de loops em matrizes multidimensionais. Essa construção é frequentemente utilizada em combinação com arrays 2D ou superiores. A ideia é distribuir o trabalho do loop entre várias threads, aproveitando a paralelização tanto no nível do loop quanto na distribuição de dados.

Aqui estão alguns exemplos simplificados de como você pode usar `distribute parallel for`:
```c
#include <stdio.h>
#include <omp.h>

int main() {
  int n = 100;
  int arr[n];

  // Inicializar o array
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }

  // Dividir o loop em 4 chunks
  #pragma omp distribute parallel for
  for (int i = 0; i < n; i++) {
    // Executar cada iteração do loop em uma thread diferente
    printf("arr[%d] = %d\n", i, arr[i]);
  }

  return 0;
}
```
Este código irá imprimir os valores do array arr em ordem crescente. O #pragma omp distribute parallel for é usado para dividir o loop em 4 chunks. Cada chunk é então executado em uma thread diferente.

```c
#include <stdio.h>

int main() {
  int n = 100000;
  int arr[n];

  // Inicializar o array
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }

  // Calcular a soma dos elementos do array
  int sum = 0;

  // Dividir o loop em 100 chunks
  #pragma omp distribute parallel for reduction(+:sum)
  for (int i = 0; i < n; i++) {
    // Executar cada iteração do loop em uma thread diferente
    sum += arr[i];
  }

  // Imprimir a soma
  printf("A soma é %d\n", sum);

  return 0;
}

```

Este código irá calcular a soma dos elementos do array arr. O #pragma omp distribute parallel for é usado para dividir o loop em 100 chunks. Cada chunk é então executado em uma thread diferente. A cláusula reduction(+:sum) é usada para acumular a soma dos elementos do array em uma variável global sum.

Essa construção é útil quando você tem grandes conjuntos de dados multidimensionais e deseja distribuir a carga de trabalho entre as threads de maneira eficiente.

### Aqui estão algumas aplicações comuns:


Um exemplo de uso real do #pragma omp distribute parallel for pode ser encontrado no código abaixo, que implementa um algoritmo de filtragem de imagens:

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  // Inicializar a imagem
  int width = 100;
  int height = 100;
  int image[width][height];
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      image[i][j] = rand() % 256;
    }
  }

  // Definir o limiar
  int threshold = 128;

  // Filtrar a imagem
  #pragma omp distribute parallel for
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      // Se o pixel for maior que o limiar, setá-lo para branco
      if (image[i][j] > threshold) {
        image[i][j] = 255;
      }
      // Senão, setá-lo para preto
      else {
        image[i][j] = 0;
      }
    }
  }

  // Imprimir a imagem filtrada
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      printf("%d ", image[i][j]);
    }
    printf("\n");
  }

  return 0;
}
```

Este código irá ler uma imagem do disco e, em seguida, filtrá-la usando um limiar. O #pragma omp distribute parallel for é usado para dividir o loop de filtragem em chunks. Cada chunk é então executado em uma thread diferente.

Neste exemplo, o loop de filtragem é executado 10000 vezes. Sem o `#pragma omp distribute parallel for`, cada iteração do loop seria executada por uma thread diferente. No entanto, com o `#pragma omp distribute parallel for`, o loop é dividido em 100 chunks. Cada chunk é então executado por um grupo de 10 threads. Isso pode melhorar significativamente o desempenho do código, pois as threads podem executar as iterações do loop em paralelo.

Aqui estão alguns outros exemplos de uso real do `#pragma omp distribute parallel for` for:

Processamento de imagens: O `#pragma omp distribute parallel for` pode ser usado para acelerar algoritmos de processamento de imagens, como filtragem, segmentação e reconhecimento de objetos.
Processamento de dados: O `#pragma omp distribute parallel for` pode ser usado para acelerar algoritmos de processamento de dados, como análise de dados, aprendizado de máquina e mineração de dados.
Simulação: O `#pragma omp distribute parallel for` pode ser usado para acelerar algoritmos de simulação, como simulação de fluidos, simulação de partículas e simulação de sistemas biológicos.