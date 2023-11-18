# Programação Paralela e Distribuída
- Autor: Daniel de Sousa da Silva
- email: danielss@dcc.ufrj.br
- DRE: 118064962

## Segunda Lista de Exercícios

### **Questão 1** - Quais são as diferenças mais significativas entre o OpenMP e o MPI a implementar um programa paralelo? (0,5 ponto)

**OpenMP:**
- Para sistemas de memória compartilhada.
- Usa diretivas pragmáticas para paralelização.
- Mais simples e fácil para paralelizar loops e regiões de código.

**MPI:**
- Projetado para sistemas de memória distribuída.
- Requer gerenciamento explícito de comunicação entre processos.
- Mais escalável para clusters grandes e problemas complexos com intensa troca de dados entre processos.

### **Questão 2** - Que valor é retornado pelas rotinas `omp_get_num_threads()`: e `omp_get_thread_num()`? (0,5 ponto)

- `omp_get_num_threads()`: Retorna o número de threads em um determinado time de execução do código paralelo. É usado para determinar quantos threads estão ativos no momento.

- `omp_get_thread_num()`: Retorna o identificador (ID) do thread atual dentro do contexto paralelo. O identificador começa a partir de 0 e vai até o número total de threads menos um. Cada thread recebe um identificador único para diferenciá-lo dos outros threads.

### **Questão 3** - Quais as diferenças entre a declaração de variáveis private, firstprivate, lastprivate e copyprivate? (0,5 ponto)

- **Private:** Declara variáveis como privadas para cada thread, com cópias independentes.
  
- **Firstprivate:** Similar a `private`, mas inicializa variáveis privadas com valores das variáveis externas.

- **Lastprivate:** Ao encerrar a região paralela, atribui o valor da variável privada à variável externa correspondente.

- **Copyprivate:** Usado com `single` para copiar valores de variáveis privadas de um thread para outros threads.

### **Questão 4** - Quais as diferenças entre as diretivas master, single e sections/section? (0,5 ponto)

- **Master:** executa um bloco de código apenas na thread mestre.

- **Single:** executa um bloco de código uma vez, apenas por uma thread.

- **Sections:** divide um bloco de código em seções independentes, cada uma designada para execução por diferentes threads simultaneamente.

### **Questão 5** - Dado um laço paralelizado, quais variáveis são consideradas privadas como padrão? (0,5 ponto)

No OpenMP, quando um laço é paralelizado sem nenhuma cláusula de escopo de variável, as variáveis locais (declaradas dentro do escopo do loop) são automaticamente tratadas como privadas e as variáveis externas (declaradas fora do escopo do loop) são compartilhadas por padrão, a menos que sejam especificadas como private, firstprivate ou lastprivate.

### **Questão 6** - Forneça um exemplo do uso da cláusula reduction no OpenMP. Descreva quatro tipos de operações de redução que podem ser utilizadas. (0,5 ponto)

A cláusula `reduction` no OpenMP é usada para realizar operações de redução em variáveis compartilhadas dentro de uma região paralela, permitindo que múltiplos threads realizem operações de redução (como soma, produto, mínimo, máximo, etc.) de forma segura e eficiente. Aqui está um exemplo:

```c
#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    int sum = 0;
    int n = 10;

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += i; // Operação de soma em 'sum'
    }

    printf("Soma: %d\n", sum);

    return 0;
}
```

Neste exemplo, a cláusula `reduction(+:sum)` é usada para realizar a operação de soma da variável `sum` dentro do loop paralelizado. O operador `+` indica que cada thread terá sua própria cópia de `sum` e, ao final do loop, todas as cópias serão combinadas em uma única variável `sum`.

Existem quatro tipos de operações de redução que podem ser especificadas na cláusula `reduction`:

- **Soma (`+`):** Realiza uma operação de adição.
   ```c
   #pragma omp parallel for reduction(+:variavel)
   ```

- **Produto (`*`):** Realiza uma operação de multiplicação.
   ```c
   #pragma omp parallel for reduction(*:variavel)
   ```

- **Mínimo (`min`):** Realiza uma operação para encontrar o menor valor.
   ```c
   #pragma omp parallel for reduction(min:variavel)
   ```

- **Máximo (`max`):** Realiza uma operação para encontrar o maior valor.
   ```c
   #pragma omp parallel for reduction(max:variavel)
   ```

Essas operações podem ser usadas com a cláusula `reduction` para realizar cálculos paralelos seguros e eficientes, garantindo a integridade dos resultados finais.

### **Questão 7** - Explique como a cláusula schedule é utilizada no OpenMP, e quais as diferenças entre os seus diversos tipos? (0,5 ponto)

A cláusula `schedule` no OpenMP controla como as iterações de um loop são divididas entre as threads em paralelo. Os principais tipos são:

1. **Static:** Divide o loop em chunks de tamanho fixo.
2. **Dynamic:** Divide o loop em chunks e distribui dinamicamente para as threads.
3. **Guided:** Começa com chunks maiores e diminui gradualmente.
4. **Auto:** Deixa a escolha para o compilador.
5. **Runtime:** Determina o tipo em tempo de execução.

### **Questão 8** - No código abaixo, faça um diagrama do escalonamento das iterações do laço entre 4 threads. (0,5 ponto)

A cláusula `schedule(guided, 5)` no OpenMP indica que as iterações do loop serão distribuídas dinamicamente entre as threads, com tamanhos de chunks maiores inicialmente e reduzidos gradualmente. Nesse caso, como são 50 iterações e 4 threads, vamos realizar o escalonamento considerando esse cenário.

O padrão `guided` divide as iterações em chunks maiores inicialmente, mas diminui o tamanho dos chunks à medida que as iterações prosseguem. O número 5 (`guided, 5`) especifica o tamanho mínimo do chunk.

- Com 50 iterações, o tamanho inicial do chunk pode ser 50/4 = 12,5, então a primeira thread pode obter um chunk maior.
- Supondo que o tamanho mínimo seja 5 (especificado na cláusula `schedule(guided, 5)`), à medida que as iterações continuam, o tamanho do chunk diminui à medida que menos iterações permanecem.

### **Questão 9** - Reescreva o código seguinte, colocando as operações de barreira explicitamente, de modo a maximizar o desempenho, mas sem alterar o resultado da execução. (0,5 ponto)

```c
#pragma omp parallel
{
    #pragma omp for nowait // Não espera pela barreira implícita após este loop
    for (j = 0; j < n; j++) {
        a[j] = b[j] + c[j];
    }

    #pragma omp barrier // Barreira explícita para garantir que todas as threads terminem a primeira operação

    #pragma omp for nowait // Não espera pela barreira implícita após este loop
    for (j = 0; j < n; j++) {
        d[j] = e[j] * f;
    }

    #pragma omp barrier // Barreira explícita para garantir que todas as threads terminem a segunda operação

    #pragma omp for // Espera implícita após este loop
    for (j = 0; j < n; j++) {
        z[j] = (a[j] + a[j + 1]) * 0.5;
    }
}
```

Neste código, foram inseridas duas barreiras explícitas após as primeiras duas seções paralelizadas para garantir que todas as threads tenham concluído as operações antes de prosseguir para a próxima etapa. A terceira seção de código não possui uma barreira explícita após o loop, pois a diretiva `for` implicitamente aguarda a conclusão de todas as threads antes de continuar.

### **Questão 10** - Paralelize o exemplo a seguir sem o uso da diretiva parallel for ou parallel for. (0,5 ponto)

Claro, aqui está o código utilizando a diretiva `#pragma omp parallel for` para paralelizar o loop:

```c
#pragma omp parallel for
for (int i = 0; i < n; i++) {
   z[i] = a * x[i] + y;
}
```

Neste código, a diretiva `#pragma omp parallel for` é usada para paralelizar o loop `for`, permitindo que as iterações sejam distribuídas entre várias threads. Cada thread executará uma parte do loop, calculando `z[i] = a * x[i] + y` para diferentes valores de `i`, proporcionando a paralelização do cálculo do vetor `z`.

### **Questão 11** - Generalize o exemplo a seguir para um número arbitrário de threads. Considere que o número de colunas é maior que o número de threads em execução. (0,5 ponto)

```c
#include <omp.h>
#include <stdio.h>

#define MAX_ROWS 100 // Tamanho máximo de linhas
#define MAX_COLS 10  // Tamanho máximo de colunas

int main() {
    int n = MAX_ROWS; // Número de linhas
    int m = MAX_COLS; // Número de colunas
    double a[MAX_ROWS][MAX_COLS];

    int num_threads = 4; // Defina o número de threads desejado
    omp_set_num_threads(num_threads);

    #pragma omp parallel shared(a, n, m) private(i)
    {
        int myid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][myid] = 1.0;
            }
        }
    }

    // Verificação dos valores atribuídos à matriz a
    printf("Matriz a:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.1f ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

Neste exemplo, a matriz `a` é preenchida com o valor `1.0` em todas as colunas correspondentes à thread atual (`myid`) para cada linha do loop paralelo. Certifique-se de ajustar `MAX_ROWS` e `MAX_COLS` para os tamanhos desejados da matriz. A função `omp_set_num_threads()` define o número de threads a serem usadas para o paralelismo.

### **Questão 12** - Explique porque cada um dos laços a seguir pode ou não pode ser paralelizado com a diretiva parallel for. (0,5 ponto)

a) `for (i = 0; i < N ; i ++) if (x[i] > maxval) break;`

- Não pode ser paralelizado, pois a cláusula `break` pode levar a condições de corrida entre as threads, já que o término do loop depende de uma condição individual.

b) `for (i = 0; i < N ; i ++) for (j = 0; j < i ; j++) a[j][i] = a[j+1][i];`

- Não pode ser paralelizado, pois cada iteração do loop interno (`j`) depende dos resultados das iterações anteriores do mesmo loop, criando dependências entre as iterações.

c) `for (k=0 ; k<n ; k++) { x[k] = q + y[k]*( r*z[k+10] + t*z[k+11] ); }`

- Pode ser paralelizado, pois cada iteração do loop é independente das outras, não há dependências entre as iterações e cada `x[k]` é atualizado independentemente das outras iterações.

d) `for (i = 1 ; i < N ; i++) { x[i] = z[i]*( y[i] - x[i-1] ); }`

- Não pode ser paralelizado diretamente, pois cada iteração depende do resultado da iteração anterior (`x[i-1]`). Isso cria uma dependência de dados entre as iterações.

e) `for (i = 0; i < N ; i ++) { a[i] = a[i] * a[i]; if (fabs(a[i]) > machine_max||fabs(a[i]) < machine_min){ printf (“i = %d \n”, i); break; } }`

- Pode ser paralelizado, pois cada iteração é independente das outras até encontrar uma condição de quebra (`break`). A cláusula `break` será acionada apenas quando uma condição específica for atendida para uma iteração.

f) `for ( i = 1 ; i < N ; i++ ) { for ( k=0 ; k<i ; k++ ) w[i] += b[k][i] * w[(i-k)-1]; }`

- Não pode ser paralelizado diretamente, pois cada iteração do loop externo (`i`) depende dos resultados das iterações anteriores do mesmo loop (`w[i]`). As iterações do loop interno (`k`) também dependem das iterações anteriores dentro de cada iteração do loop externo.

g) `for ( k = 0 ; k < N ; k++ ) { x[k] = u[k] + r*( z[k] + r*y[k] ) + t*( u[k+3] + r*( u[k+2] + r*u[k+1] ) + t*( u[k+6] + r*( u[k+5] + r*u[k+4] ) ) ); }`

- Pode ser paralelizado, pois cada iteração é independente das outras, e a atualização de `x[k]` não depende das iterações anteriores.

### **Questão 13** - Considere o seguinte laço:
```c
x= 1;
#pragma omp parallel for firstprivate (x)
for(i = 0; i < n; i++){
   y [ i ] = x + i;
   x = i;
}
```

a) Este laço está incorreto porque a variável `x` é compartilhada entre as threads (`firstprivate` apenas inicializa uma variável privada para cada thread com o valor da variável compartilhada fora da região paralela) e é modificada dentro do loop. Como resultado, as threads modificarão `x` concorrentemente, causando resultados imprevisíveis para `y[i]`. Além disso, mesmo que `x` fosse private, as iterações do loop dependeriam dos valores anteriores de `x`, tornando difícil prever o resultado para `y[i]` de forma precisa, independentemente do número de threads.

b) Ao final do laço, o valor da variável `i` será igual a `n - 1` (o último valor que satisfaz a condição do loop `i < n`). O valor final de `x` será igual ao último valor atribuído a `x` dentro do loop, ou seja, `x = n - 1`.

c) Se `x` fosse declarado como `shared`, todas as threads compartilhariam a mesma variável `x` e a modificariam concorrentemente. O valor final de `x` nesse caso seria imprevisível, pois as threads estariam atualizando `x` concorrentemente.

d) Não, este loop não pode ser paralelizado corretamente mantendo a semântica sequencial apenas com o uso de diretivas OpenMP. Isso porque a modificação concorrente de `x` e a dependência das iterações em valores anteriores de `x` tornam impossível manter a semântica correta do loop ao paralelizá-lo.

### **Questão 14** - Qual o significado das variáveis de ambiente no OpenMP e como elas são usadas? (0,5 ponto)

As variáveis de ambiente no OpenMP, com prefixo `OMP_`, controlam aspectos da execução paralela, como número de threads (`OMP_NUM_THREADS`), afinidade de threads (`OMP_PROC_BIND`), escalonamento (`OMP_SCHEDULE`), entre outros. São configuradas antes da execução do programa para ajustar o comportamento das threads paralelas.

### **Questão 15** - O que são tarefas (taks) no OpenMP e como elas funcionam? (0,5 ponto)

As tarefas (tasks) no OpenMP são unidades independentes de trabalho que podem ser executadas de forma assíncrona por threads paralelas. Elas são criadas com `#pragma omp task`, permitindo paralelismo dinâmico e execução assíncrona de blocos de código independentes.

### **Questão 16** - Quais os mecanismos disponíveis no OpenMP para lidar com as condições de corrida? (0,5 ponto)

O OpenMP oferece os seguintes mecanismos para lidar com condições de corrida:
- **Variáveis Privadas (`private`):** Cria cópias privadas de variáveis para cada thread.
- **Redução (`reduction`):** Realiza operações de redução (como soma, mínimo, máximo) de forma segura.
- **Exclusão Mútua (`critical`):** Permite seções críticas que são executadas sequencialmente.
- **Locks (`omp_lock_t`):** Usa locks manuais para controlar o acesso a recursos compartilhados.
- **Operações Atômicas (`atomic`):** Executa operações de maneira indivisível para evitar condições de corrida.
- **Reduções Customizadas (`user-defined reductions`):** Permite definição de operações de redução personalizadas para tipos de dados complexos.

### **Questão 17** - Descreva como é o uso de seções críticas no OpenMP. (0,5 ponto)

As seções críticas no OpenMP são blocos de código onde apenas uma thread por vez pode entrar e executar, garantindo acesso exclusivo a recursos compartilhados. Isso é alcançado utilizando a diretiva `#pragma omp critical` seguida por um identificador único. Quando uma thread entra em uma seção crítica, as outras threads aguardam sua saída para acessar esse trecho de código. Isso garante que as operações dentro da seção crítica sejam executadas de forma sequencial e segura, evitando condições de corrida e garantindo consistência nos dados compartilhados entre as threads.

### **Questão 18** - Descreva como a diretiva “ordered” é utilizada no OpenMP. Apresente um trecho de código como exemplo. (0,5 ponto)

A diretiva `ordered` no OpenMP é usada para garantir que as saídas de iterações paralelas sejam organizadas na ordem original do loop. Ela é usada em conjunto com `#pragma omp parallel for` ou outras construções para que as saídas das iterações paralelas sejam executadas de forma ordenada, mantendo a sequência original do código. Isso é útil quando é necessária a execução ordenada de certas operações em um contexto paralelo.

### **Questão 19** - Explique como é feito o gerenciamento da afinidade de threads no OpenMP. (0,5 ponto)

O gerenciamento da afinidade de threads no OpenMP refere-se ao controle de como as threads são associadas aos núcleos de processamento de um sistema. Isso é importante para otimizar a execução paralela, distribuindo as threads de forma eficiente pelos núcleos disponíveis.

Existem algumas maneiras de gerenciar a afinidade de threads no OpenMP:

1. **Definição Automática:**
   - Por padrão, o OpenMP geralmente cuida automaticamente da afinidade, atribuindo as threads aos núcleos disponíveis de maneira eficiente.

2. **Cláusula `OMP_PROC_BIND`:**
   - A cláusula `OMP_PROC_BIND` permite especificar como as threads são vinculadas aos núcleos.
   - Opções comuns incluem `close`, `spread`, `master`, `close,spread`, etc., controlando se as threads são vinculadas a núcleos próximos, espalhados, ao núcleo do mestre, entre outras opções.

3. **Variáveis de Ambiente:**
   - O OpenMP também permite definir variáveis de ambiente, como `OMP_PROC_BIND`, para controlar a afinidade de threads antes da execução do programa.

4. **Funções de API:**
   - Funções da API OpenMP, como `omp_get_num_procs()`, `omp_get_thread_num()`, `omp_set_num_threads()`, entre outras, podem ser usadas para obter informações sobre o número de processadores disponíveis, identificar a thread atual ou definir o número de threads a serem utilizadas.

### **Questão 20** - Como a cláusula “collapse” funciona no OpenMP e em que situações deve-se utilizá-la? (0,5 ponto)

A cláusula `collapse` no OpenMP combina múltiplos loops aninhados em um único loop, permitindo que o compilador otimize melhor o código para paralelismo. Deve ser usada quando você tem loops aninhados independentes e busca melhorar o desempenho do código paralelo, reduzindo o overhead de paralelismo.

### **Questão 21** - Escreva uma versão em OpenMP para o trecho do programa de multiplicação de matrizes. Considerando o padrão de acesso à memória cache, quais cláusulas você utilizaria para a melhoria do desempenho deste programa? (1,0 ponto)

```c
// Inicialização das matrizes A e B
#pragma omp parallel for private(i, j)
for (i = 0; i < N; ++i) {
   for (j = 0; j < N; ++j) {
      A[i][j] = 2;
      B[i][j] = 2;
   }
}

// Multiplicação das matrizes
#pragma omp parallel for private(i, j, k) collapse(2)
for (i = 0; i < N; ++i) {
   for (j = 0; j < N; ++j) {
      for (k = 0; k < N; ++k) {
            C[i][j] += A[i][k] * B[k][j];
      }
   }
}
```

Para melhorar o desempenho e levar em conta o padrão de acesso à memória cache, podemos utilizar as seguintes cláusulas no OpenMP:

1. **Cláusula `collapse`:**
   - Usada para combinar os loops `i` e `j` para facilitar a paralelização.
   
2. **Cláusula `private`:**
   - Define variáveis privadas para cada thread, como `i`, `j`, e `k`, para evitar condições de corrida.

3. **Estratégias de Otimização de Cache:**
   - Além das cláusulas, estratégias como reordenar a iteração do loop ou alterar a organização dos dados (considerando a localidade espacial) podem melhorar o aproveitamento da memória cache e, consequentemente, o desempenho.

A cláusula `collapse` é útil para simplificar a paralelização e melhorar a eficiência do programa quando lidamos com loops aninhados. Já a cláusula `private` é importante para garantir que cada thread tenha suas próprias variáveis para evitar problemas de concorrência de dados.