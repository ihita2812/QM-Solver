#ifndef HELPER_H_
#define HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

//will give no. of variables from list of minterms
extern int N(list*);

//m is the minterm number (0 to 2^(N-1))
//n is number of variables
extern int num_ones(int m, int n);

extern int is_power_of_2(int x);

//comparator for qsort
int compare(const void* num1, const void* num2);

//initialises implicant i with size = _size
extern void Implicaant(int _size, struct Implicant* i);

//initialises implicant i with size = _size and contents = union of i1 and i2
extern void Implicaaant(int _size, struct Implicant*, struct Implicant, struct Implicant);

//checks if two implicants are equal to avoid duplicates
extern int equal_implicants(struct Implicant*, struct Implicant*);

//checks if old is superet of new
extern int is_superset(struct Implicant new, struct Implicant old);

//will convert final array of chars ('0' '1' and '-') to array of abc chars
extern char* abc_convert(char*, char*, int);

//converts implicant  to string of '1', '0' or '-'
extern char* string_convert(struct Implicant, int n);

//for debugging
extern void print(struct Implicant);

#endif