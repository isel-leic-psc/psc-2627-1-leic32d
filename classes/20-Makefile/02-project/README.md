# Building a C Program with Make

## Project structure and dependencies

The program consists of three C source files and one header file:

- `points-program.c` — contains the `main` function.
- `points-aux.c` — implements the `use_points` function.
- `point.c` — implements the operations on `Point` objects.
- `point.h` — defines the `Point` type and declares its operations.

Each source file is compiled separately into an object file (`.o`). The three object files are then linked to produce the `points` executable.

All three source files include `point.h`. Consequently, each object file depends not only on its corresponding `.c` file but also on `point.h`. A change to the header, such as a change to the definition of `Point`, may affect the machine code generated for any of the three source files. Without these dependencies, `make` could reuse outdated object files.

**Experiment:** Run the following commands, observing which compilation and linking commands are executed each time:

```sh
make
./points
make
touch point.c
make
touch point.h
make
```

Why are all three source files recompiled after touching `point.h`, but only one after touching `point.c`? Why is the executable relinked in both cases?

## The `clean` target

The `clean` rule removes the generated object files and the executable. Unlike the other rules, its purpose is to perform an action rather than generate a file. The `-f` option of `rm` prevents errors when the files do not exist.

**Experiment:** Run:

```sh
make clean
ls
make
```

Observe which files remain after cleaning and why the next build recompiles all three source files.

## Phony targets

The declaration `.PHONY: clean` tells `make` that `clean` does not represent a file. When explicitly requested, its recipe runs regardless of whether a file named `clean` exists.

**Experiment:** Create an empty file named `clean`, then request the target:

```sh
touch clean
make clean
make
```

Now temporarily remove the `.PHONY: clean` declaration from the Makefile and run:

```sh
make clean
ls
```

Why does `make` now consider `clean` up to date without removing the generated files?

Restore the `.PHONY: clean` declaration and remove the file named `clean` with `rm clean`.
