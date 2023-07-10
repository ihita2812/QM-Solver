#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <math.h>
#include "structure.h"

//Implicant i has size : _size minterms
void Implicaant(int _size, struct Implicant i);

//Implicant i has size : _size minterms and will combine minterms of i1 and i2
void Implicant(int _size, struct Implicant i, struct Implicant i1, struct Implicant i2);

const int N; //number of variables
const char dash = '-';
int str_len;
int valid_minterms[];
const int V; //number of valid minterms

//m is the minterm number (0 to 2^(N-1))
//n is N
int num_ones(int m, int n);

//will convert final array of chars ('0' '1' and '-') to array of abc chars
char* string(char* a);

int is_power_of_2(int x);

#endif