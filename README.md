# QM-Solver

C algorithm for step-by-step, direct execution of the [Quine-McCluskey Method](https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm) for minimising a boolean expression.

## Contents
1. README.md
2. src *(Makefile and all .c source files)*
    - main.c
    - solver.c
    - helper.c
    - stl.c
    - Makefile
3. include *(all .h header files)*
    - solver.h
    - helper.h
    - structure.h
    - stl.h
4. obj *(all .o object files)*
5. bin *(.exe binary file)*

## How to run

### To compile
```
$ cd src
$ make
```
### To execute
```
$ ../bin/myqm [detail]
```
- Program can be called with or without the "detail" argument.
- Pass "detail" to view details of implicants at each stage along with final answer.

### To clean
```
$ make clean
```
Clean the program before every execution.