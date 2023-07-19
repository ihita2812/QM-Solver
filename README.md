# QM-Solver

C algorithm for step-by-step, direct execution of the [Quine-McCluskey Method](https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm) for minimising a boolean expression.

## Things to add
1. ~~input handling~~
    - ~~minterm/maxterm?~~
    - ~~dontcares~~
2. ~~dont cares~~
3. ~~convert Implicant to string of '1', '0' or '-'~~
4. ~~proper output handling~~
5. ~~why is [this case](https://atozmath.com/example/KMap.aspx?q=quine&q1=E3) not working?~~
6. check with other examples:
    - dont-cares
    - ~~maxterms~~
7. add comments
8. ~~account for failing of malloc~~
9. makefile
10. gui

## How to execute

### To build
```
cd src
make
```

### To run
```
make run
```

### To clean
```
make clean
```