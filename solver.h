#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <math.h>

const int N; //number of variables
const char dash = '-';
int str_len;
int valid_minterms[];

//m is the minterm number (0 to 2^(N-1))
//n is N
int num_ones(int m, int n);

//will convert final array of chars ('0' '1' and '-') to array of abc chars
char* string(char* a);

#endif