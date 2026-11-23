# ISEL · LEIC
## Programação de Sistemas de Computadores  

**Pré-processamento**

Executa os comandos seguintes na diretoria onde se encontra o ficheiro com o nome **`prog.c`**.

## 1. Pré-processamento

Executa:

```sh
gcc -E -P prog.c -o prog.i
cat prog.i
```

A opção **`-E`** manda o GCC parar depois do pré-processamento, sem compilar. A opção **`-P`** suprime as indicações de ficheiro e número de linha que o pré-processador normalmente acrescenta à saída. O resultado fica guardado em `prog.i`.

Em alternativa, podes invocar diretamente o pré-processador:

```sh
cpp -P prog.c -o prog.i
cat prog.i
```

O resultado deverá ser equivalente a:

```c
extern int puts(const char * str);
int main
() {
    puts("Hello, world!");
    puts("Hello, world!");
    return 0;
}
```

*A disposição dos espaços e das linhas pode diferir.*

**Observa:**

- As diretivas `#define` desapareceram: foram processadas, não traduzidas para instruções C.
- `number` foi substituído por `int` e `entry` por `main`.
- `noargsf` foi substituído por `() {` e `endf` por `}`.
- `OK` foi substituído por `0`.
- Tanto `MESSAGE` como `TEXT` deram origem à cadeia de caracteres `"Hello, world!"`.

**Nota importante:** `TEXT` está definido como `MESSAGE` *antes* de aparecer a definição de `MESSAGE`. Isso não impede a expansão: quando `TEXT` é utilizado no código, a sua substituição é novamente examinada, e `MESSAGE` já está definido. Por isso, **as duas chamadas a `puts` ficam iguais**.

## 2. Compilação e execução

Compila o programa original, produzindo um executável chamado `prog`:

```sh
gcc -std=c11 -Wall -Wextra prog.c -o prog
```

Executa-o:

```sh
./prog
```

**Resultado esperado:**

```text
Hello, world!
Hello, world!
```

Para consultar o código de saída do programa depois de o executar:

```sh
echo $?
```

O valor esperado é `0`, porque `main` termina com `return OK;` e `OK` é substituído por `0`.
