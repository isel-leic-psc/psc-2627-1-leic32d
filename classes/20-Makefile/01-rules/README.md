# File Dependencies with `make`

This example illustrates how `make` uses file dependencies and modification times to determine which files need to be generated or updated.

## The Makefile

A rule specifies a target, its prerequisites (the files it depends on), and a recipe (the commands used to build the target):

```make
target: prerequisite1 prerequisite2
	command
```

Recipe lines begin with a tab.

The supplied `Makefile` defines three rules:

- `dest1.txt` depends on `source1.txt` and contains its lowercase text.
- `dest2.txt` depends on `source2.txt` and contains its numbered lines.
- `final.txt` depends on `dest1.txt` and `dest2.txt` and contains their concatenated contents.

The dependencies form two chains (arrows point from prerequisites to targets):

```text
source1.txt --> dest1.txt --+
                           +--> final.txt
source2.txt --> dest2.txt --+
```

When asked to build a target, `make` first ensures that its prerequisites are up to date. It runs the target's recipe if the target does not exist or if any of its prerequisites is newer than the target.

## Experiments

Run the following commands in the directory containing the three supplied files. Start with no generated files.

### 1. Build a specific target, then build all the files

```sh
make dest1.txt
```

Only the recipe for `dest1.txt` runs. Examine the generated file:

```sh
cat dest1.txt
```

Now run:

```sh
make
```

Since no target is specified, `make` builds the first target in the Makefile, `final.txt`. Observe that it generates `dest2.txt` and then `final.txt`, but does not regenerate `dest1.txt`, which is already up to date.

Examine the generated files and their modification times:

```sh
cat dest1.txt dest2.txt final.txt
ls -l --full-time *.txt
```

### 2. Build again without changing anything

```sh
make
```

No recipe runs: all targets exist and none of their prerequisites is newer.

### 3. Change a source file's modification time

```sh
touch source1.txt
make
```

`touch` updates the modification time without changing the file's contents. Observe that `make` regenerates `dest1.txt` and then `final.txt`, but not `dest2.txt`.

Repeat with `source2.txt`. Which recipes run this time? Why?

This shows that `make` uses modification times, not file contents, and that updates propagate through dependency chains.

### 4. Remove a generated file

```sh
rm dest1.txt
make
```

Observe that `make` regenerates the missing `dest1.txt` and then updates `final.txt`, even though neither source file has changed.

### 5. Request an intermediate target

```sh
touch source2.txt
make dest2.txt
```

Only `dest2.txt` is regenerated. `make` follows dependencies toward prerequisites, not toward targets that depend on them.

Now run:

```sh
make
```

Only `final.txt` is regenerated, because `dest2.txt` is now newer than `final.txt`.
