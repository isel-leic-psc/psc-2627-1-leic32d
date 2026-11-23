# ISEL · LEIC
## Programação de Sistemas de Computadores

**Memória dinâmica, tipos com operações associadas e compilação separada.**

Este exercício utiliza quatro ficheiros, que devem estar na mesma diretoria:

- **`point.h`** — definição do tipo `Point` e declarações das operações disponíveis;
- **`point.c`** — implementação das operações sobre pontos;
- **`points.c`** — função `main`, que cria, utiliza e destrói dois pontos;
- **`points_aux.c`** — implementação de `use_points`, que apresenta e modifica os pontos.

## 1. Pré-processamento

Executa:

```sh
gcc -E -P point.c -o point.i
tail -n 30 point.i
```

A opção **`-E`** manda o GCC parar depois do pré-processamento; **`-P`** suprime as indicações de ficheiro e número de linha. O resultado fica guardado em `point.i`.

O ficheiro pré-processado será bastante extenso, porque `point.h` inclui `<stdlib.h>`. Por isso, o comando `tail` mostra apenas as últimas linhas, onde se encontram as declarações de `point.h` e as definições das funções de `point.c`.

**Observa:**

- A diretiva `#include "point.h"` desapareceu; no seu lugar surgem o conteúdo desse cabeçalho e o dos cabeçalhos que este inclui.
- A definição de `struct point`, a declaração do nome `Point` e os protótipos de `create_point`, `destroy_point` e `translate_point` aparecem antes das respetivas implementações.
- As expressões `malloc(sizeof(Point))` e `free(p)` continuam presentes: o pré-processador não executa estas operações nem calcula o valor de `sizeof`.

Experimenta também pré-processar os outros dois ficheiros C:

```sh
gcc -E -P points.c -o points.i
gcc -E -P points_aux.c -o points_aux.i
```

**Nota:** cada ficheiro `.c` é pré-processado independentemente. O cabeçalho `point.h` é incluído em cada um dos ficheiros que dele necessita; não é compilado separadamente.

## 2. Compilação e execução

Compila os três ficheiros C que contêm implementações, produzindo um único executável:

```sh
gcc -std=c11 -Wall -Wextra -g points.c points_aux.c point.c -o points
```

A opção **`-g`** acrescenta informação de depuração, útil no exercício com o Valgrind.

Executa:

```sh
./points
```

**Resultado esperado:**

```text
Point1(3, 4)
Point2(4, 5)
Point2(79, -27)
```

A função `use_points` apresenta os dois pontos e chama `translate_point(p2, 75, -32)`. Como o ponto `p2` é modificado através de um ponteiro, as suas coordenadas passam de `(4, 5)` para `(79, -27)`.

## 3. Objetos e memória dinâmica

Em `point.h`, a estrutura `struct point` reúne dois campos (`x` e `y`), e `typedef` permite utilizar o nome `Point`.

Em `point.c`, a função `create_point` executa:

```c
Point * pnt = (Point *)malloc(sizeof(Point));
pnt->x = xx;
pnt->y = yy;
return pnt;
```

**Observa:**

- `malloc` reserva uma região de memória suficientemente grande para um objeto `Point` e devolve o endereço dessa região.
- A expressão `sizeof(Point)` determina o número de bytes necessários; os campos são depois inicializados através do operador `->`.
- Em `main`, `p1` e `p2` são variáveis locais que **guardam ponteiros**; os objetos para os quais apontam foram alocados dinamicamente.

A organização faz lembrar uma classe em **Java ou Kotlin**, com operações associadas ao tipo:

| C | Papel semelhante em linguagem object-oriented |
|---|---|
| `create_point(...)` | Construtor: cria e inicializa um objeto |
| `destroy_point(...)` | Operação explícita de destruição/libertação |
| `translate_point(p, dx, dy)` | Método de instância que modifica o objeto |

Há, contudo, diferenças importantes. Em C, estas operações são **funções independentes**: em `translate_point`, o objeto é identificado explicitamente pelo primeiro argumento (`pobj`), em vez de existir um recetor implícito como `this`. Além disso, `struct point` está definida no cabeçalho, pelo que os seus campos são acessíveis diretamente: **não existe aqui encapsulamento dos dados**.

A função `destroy_point` chama `free(p)`, libertando a memória anteriormente reservada por `malloc`. Ao contrário do que sucede normalmente em Java ou Kotlin, **a libertação desta memória não é automática**: o programa tem de a realizar explicitamente. É por isso que `main` termina com duas chamadas a `destroy_point`, uma para cada ponto criado.

**Nota:** esta implementação assume que `malloc` consegue reservar memória. Num programa robusto, seria necessário verificar se devolveu `NULL` antes de aceder aos campos do ponto.

## 4. Compilação separada

O ficheiro `point.h` disponibiliza as **declarações** necessárias para utilizar `Point`; `point.c` contém as respetivas **implementações**. Assim, `points.c` e `points_aux.c` podem ser compilados sem que o compilador tenha de analisar a implementação de `create_point`, `destroy_point` ou `translate_point`.

Compila agora cada ficheiro C para um objeto, sem efetuar a ligação (`-c`):

```sh
gcc -std=c11 -Wall -Wextra -g -c point.c -o point.o
gcc -std=c11 -Wall -Wextra -g -c points_aux.c -o points_aux.o
gcc -std=c11 -Wall -Wextra -g -c points.c -o points.o
```

Liga os três objetos para produzir o executável:

```sh
gcc points.o points_aux.o point.o -o points
./points
```

O resultado deverá ser igual ao anterior. Na ligação, são estabelecidas as referências entre funções definidas em objetos diferentes: por exemplo, a chamada a `use_points` em `points.o` encontra a sua implementação em `points_aux.o`, e as chamadas às operações sobre pontos encontram as respetivas implementações em `point.o`.

**Observa:** `points.c` contém uma declaração de `use_points`, enquanto a sua implementação está em `points_aux.c`. A declaração é suficiente para o compilador verificar a chamada; a implementação só precisa de estar disponível na ligação.

## 5. Exercício — detetar uma fuga de memória

Primeiro, com o programa original, executa:

```sh
valgrind --leak-check=full ./points
```

O Valgrind deverá indicar que **não ficaram blocos de memória alocados por libertar**.

Agora, **retira uma das duas chamadas a `destroy_point`** na função `main` de `points.c`. Volta a compilar e a executar:

```sh
gcc -std=c11 -Wall -Wextra -g points.c points_aux.c point.c -o points
valgrind --leak-check=full ./points
```

**Observa:** o programa continua a apresentar os mesmos valores, mas o Valgrind deverá identificar uma *fuga de memória* (*memory leak*), tipicamente **8 bytes em 1 bloco** num sistema Linux x86-64. A memória reservada por uma das chamadas a `create_point` nunca foi libertada.

Repõe a chamada a `destroy_point`, volta a compilar e confirma que a fuga desapareceu.
