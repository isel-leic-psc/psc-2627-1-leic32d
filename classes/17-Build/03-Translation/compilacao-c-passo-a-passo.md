# De um programa C ao executável: passo a passo

Este exercício acompanha o ficheiro **`prog.c`** fornecido, desde o pré-processamento até à ligação, inspecionando o que cada etapa produz. Pressupõe **Linux**, **GCC**, **binutils** e uma máquina **x86-64**. Executar os comandos na diretoria que contém `prog.c`.

O programa define duas variáveis globais (`also_add_c` e `c`), a função `add` e a função `main`. Esta última chama `add` duas vezes (a segunda condicionalmente) e apresenta o resultado com `printf`. É um exemplo conveniente para observar como se representam referências a funções e variáveis antes e depois da ligação.

> **Nota:** o programa declara `printf` diretamente, em vez de incluir `<stdio.h>`. Isso é válido neste exemplo e evita acrescentar muitas declarações ao ficheiro pré-processado.

## 1. Pré-processamento: `prog.c` → `prog.i`

```sh
cpp -P prog.c -o prog.i
cat prog.i
```

O pré-processador trata diretivas como `#include` e `#define`. Neste exercício, a inclusão de `<stdbool.h>` leva à substituição de `bool` por `_Bool` e de `true` por `1`.

Sem a opção **`-P`**, apareceriam indicações na saída a identificar a origem e o número das linhas do código, para preservar a correspondência com o ficheiro original.

Também se pode pedir ao *driver* GCC que faça o pré-processamento:

```sh
gcc -E -P prog.c -o prog.i
```

Aqui, **`-E`** significa «parar depois do pré-processamento». Para observar as indicações de ficheiro/linha, experimentar `gcc -E prog.c` sem `-P`.

**Observar:** que desapareceu o `#include <stdbool.h>` e como ficaram escritas as declarações de `also_add_c`, `c`, `add` e `main`.

## 2. Compilação: `prog.i` → `prog.s`

```sh
gcc -Og -S prog.i -o prog.s
cat prog.s
```

O compilador C traduz o código pré-processado para **assembly** da arquitetura de destino. A opção **`-S`** manda parar **antes da assemblagem**: o resultado é o ficheiro textual `prog.s`, ainda não um ficheiro objeto.

A opção **`-Og`** ativa um conjunto de otimizações pensado para facilitar a **depuração**: elimina algum trabalho redundante, mas evita várias transformações que tornam mais difícil relacionar as instruções com o código C.

Outras opções que se podem experimentar são `-O0` (sem otimizações), `-O1`, `-O2` e `-O3` (otimizações progressivamente mais intensas), e `-Os` (otimizar privilegiando o tamanho). Com níveis mais elevados, a função `add` poderá ser integrada (*inlined*) e certas operações poderão desaparecer; nesse caso, já não será tão fácil seguir as referências que se pretendem observar.

**Procurar em `prog.s`:** a implementação de `add`, as duas instruções `call add`, os acessos relativos ao contador de instruções a `also_add_c` e a `c`, e a chamada a `printf` (tipicamente `printf@PLT`).

O GCC é um *driver*. A compilação C propriamente dita é realizada por **`cc1`**, que o GCC executa internamente. Para ver como seria invocado:

```sh
gcc -### -Og -S prog.i -o prog.s
```

A opção **`-###`** mostra comandos sem os executar.

## 3. Assemblagem: `prog.s` → `prog.o`

```sh
gcc -c prog.s -o prog.o
file prog.o
```

Nesta etapa, o **assembler** (`as`, invocado pelo GCC) transforma o assembly em instruções máquina e constrói um **ficheiro objeto relocável**, neste caso ELF. A opção **`-c`** impede a ligação.

É importante distinguir as ferramentas: neste percurso, **`cc1` traduz C para assembly**; **`as` transforma assembly num objeto**. Quando se faz `gcc -Og -c prog.c -o prog.o`, o *driver* coordena as etapas necessárias, sem guardar normalmente o `.s` intermédio. É possível observar os comandos com:

```sh
gcc -### -Og -c prog.c -o prog.o
```

### 3.1. Secções e símbolos

```sh
objdump -x prog.o
```

O comando apresenta os cabeçalhos do objeto, as secções, a tabela de símbolos e as relocações. Identificar, entre outras:

- **`.text`** — código máquina de `add` e `main`;
- **`.data`** — dados globais inicializados, como `c` e `also_add_c`;
- **`.rodata...`** — dados constantes, incluindo a cadeia `"res: %d\n"` (o nome exato da secção pode variar);
- **`.rela.text`** — informação necessária para corrigir certas referências contidas na secção `.text` durante a ligação.

Para ver os símbolos de forma mais compacta:

```sh
nm prog.o
```

Neste exemplo, `add` e `main` surgem como símbolos definidos em código (`T`), `c` e `also_add_c` como símbolos definidos em dados inicializados (`D`), e `printf` como símbolo **não definido neste objeto** (`U`).

### 3.2. Instruções e referências por resolver

```sh
objdump -d prog.o
```

A opção **`-d`** desmonta as instruções máquina. É normal encontrar chamadas a `add` e acessos a `c` com **deslocamentos provisórios**, frequentemente com bytes a zero: o assembler produziu as instruções, mas deixou ao *linker* a tarefa de determinar os deslocamentos corretos.

Para tornar explícito **que instrução depende de que símbolo**, é particularmente útil:

```sh
objdump -dr prog.o
```

A opção `-r` acrescenta as **entradas de relocação** junto das instruções correspondentes. Por exemplo, o resultado de uma compilação em x86-64 pode ter, entre outros, os seguintes excertos:

```text
12: e8 00 00 00 00        call 17 <main+0x13>
        13: R_X86_64_PLT32 add-0x4

20: 8b 35 00 00 00 00     mov 0x0(%rip),%esi
        22: R_X86_64_PC32  c-0x4

28: e8 00 00 00 00        call 2d <main+0x29>
        29: R_X86_64_PLT32 add-0x4
```

Os zeros **não** são os destinos definitivos da chamada nem do acesso à variável. Representam campos de deslocamento por preencher; as entradas `R_X86_64_...` indicam ao *linker* que valores terá de calcular e escrever nesses campos. Também existem, neste programa, relocações relativas a `also_add_c`, à cadeia de caracteres e a `printf`.

**Distinção essencial:** dizer que há «referências por resolver» **não significa** que todos os símbolos referidos sejam desconhecidos. `add` e `c` **já estão definidos no próprio `prog.o`**. Falta, isso sim, aplicar às instruções as relocações que dependem da disposição final do código e dos dados. `printf`, pelo contrário, é um símbolo externo cuja implementação não se encontra neste objeto.

## 4. Ligação: `prog.o` → `prog`

```sh
gcc prog.o -o prog
./prog
```

Resultado esperado:

```text
res: 87
```

Na ligação, as secções dos diversos objetos são dispostas no executável, os símbolos são associados às suas posições e são aplicadas as **relocações necessárias**. O GCC acrescenta automaticamente os componentes habituais de um programa C (ficheiros de arranque, bibliotecas e configuração de ligação). Por isso é muito mais prático usá-lo do que invocar `ld` diretamente.

Numa instalação Linux típica, o GCC prepara uma execução de **`collect2`**, que utiliza o **`ld`** ou outro *linker* configurado. Não é necessário compreender a longa lista de parâmetros para realizar este exercício. Basta espreitar os comandos:

```sh
gcc -### prog.o -o prog   # mostra os comandos, sem os executar
gcc -v   prog.o -o prog   # executa e mostra informação detalhada
```

## 5. Inspeção do executável: referências já resolvidas

```sh
objdump -x prog
objdump -d prog
```

O executável tem mais secções e mais código do que o objeto original, por incluir os componentes necessários ao arranque e à ligação com as bibliotecas. Procurar novamente **`<main>`**, **`<add>`** e **`<c>`**.

No executável produzido na mesma máquina, as instruções anteriormente mostradas passaram a:

```text
114b: e8 e9 ff ff ff       call 1139 <add>

1159: 8b 35 b9 2e 00 00    mov 0x2eb9(%rip),%esi # 4018 <c>

1161: e8 d3 ff ff ff       call 1139 <add>
```

Agora, as duas chamadas a `add` têm deslocamentos calculados para o destino efetivo, e o acesso a `c` tem o deslocamento adequado a partir do contador de instruções. **Os valores numéricos variam entre compilações e sistemas; interessa a diferença entre os campos provisórios do objeto e os campos já corrigidos do executável.**

A comparação mais instrutiva é, portanto:

```sh
objdump -dr prog.o    # antes da ligação: instruções e relocações pendentes
objdump -d  prog      # depois da ligação: instruções já corrigidas
```

---

## Sequência completa

```sh
cpp -P prog.c -o prog.i
# ou: gcc -E -P prog.c -o prog.i

gcc -Og -S prog.i -o prog.s
gcc -c prog.s -o prog.o

objdump -x prog.o
objdump -dr prog.o

gcc prog.o -o prog

objdump -x prog
objdump -d prog
./prog
```

**Ideia-chave:** o pré-processador prepara o código C, o compilador produz assembly, o assembler produz código máquina relocável e o *linker* constrói o executável, **resolvendo as referências e aplicando as relocações que já podem ser determinadas nesta fase**.
