# ISEL · LEIC
## Programação de Sistemas de Computadores

**Pré-processamento de macros.**
*(Exemplo com disposição de estruturas.)*

Executa os comandos seguintes na diretoria onde se encontra o ficheiro **`offset.c`**.

## 1. Pré-processamento

Executa:

```sh
gcc -E -P offset.c -o offset.i
cat offset.i
```

A opção **`-E`** manda o GCC parar depois do pré-processamento. A opção **`-P`** suprime as indicações de ficheiro e número de linha. O resultado é guardado em `offset.i`.

Em alternativa, podes invocar diretamente o pré-processador:

```sh
cpp -P offset.c -o offset.i
cat offset.i
```

O resultado deverá ser equivalente a:

```c
extern int printf(const char * fmt, ...);
struct type {
 int value;
 char * text;
 short num;
};
int main() {
 unsigned int sizeOfType =
  sizeof (struct type);
 unsigned int offsetOfText =
  ((unsigned int)(unsigned long)&(((struct type *)0)->text));
 unsigned int offsetOfNum =
  ((unsigned int)(unsigned long)&(((struct type *)0)->num));
 printf(
  "size: %u; text: %u; num: %u\n",
  sizeOfType,
  offsetOfText,
  offsetOfNum
 );
 return 0;
}
```

*A disposição dos espaços e das linhas pode diferir.*

**Observa:**

- A diretiva `#define offsetof(TYPE, MEMBER)` desapareceu e cada utilização da macro foi substituída pela expressão correspondente.
- Os parâmetros `TYPE` e `MEMBER` foram substituídos, respetivamente, por `struct type` e por `text` ou `num`.
- As expressões `sizeof (struct type)` e `&(((struct type *)0)->text)` **continuam presentes**. O pré-processador expande macros, mas não calcula o tamanho da estrutura nem os deslocamentos dos seus membros: isso compete ao compilador.

## 2. Compilação e execução

Compila o programa original, produzindo um executável chamado `offset`:

```sh
gcc -std=c11 -Wall -Wextra offset.c -o offset
```

Executa-o:

```sh
./offset
```

**Resultado esperado em Linux x86-64:**

```text
size: 24; text: 8; num: 16
```

A estrutura ocupa **24 bytes**, mas a soma dos tamanhos dos três membros é apenas **14 bytes** (`int`: 4, ponteiro: 8, `short`: 2). Os restantes bytes correspondem a *padding*, introduzido para respeitar os requisitos de alinhamento.

Na disposição habitual em x86-64:

| Posição (bytes) | Conteúdo |
|---|---|
| 0–3 | `value` |
| 4–7 | *Padding* |
| 8–15 | `text` |
| 16–17 | `num` |
| 18–23 | *Padding* final |

**Nota:** a macro `offsetof` deste exercício é uma implementação clássica, útil para observar a expansão de macros. Em programas reais, deve utilizar-se a macro `offsetof` disponibilizada por `<stddef.h>`.

## 3. Exercício

Modifique a definição da estrutura para terminar com `} __attribute__((packed));` e analise a diferença de valores. 
