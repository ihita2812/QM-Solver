#ifndef HELPER_H_
#define HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure.h"

// extern struct Implicant** implicant_pointer_array;

int compare(const void* num1, const void* num2);

//Implicant i has size : _size minterms
extern void Implicaant(int _size, struct Implicant* i);

//Implicant i has size : _size minterms and will combine minterms of i1 and i2
extern void Implicaaant(int _size, struct Implicant*, struct Implicant, struct Implicant);

extern int equal_implicants(struct Implicant*, struct Implicant*);

//checks if old is superet of new
int is_superset(struct Implicant new, struct Implicant old);

int N; //number of variables
// extern const char dash;
int str_len;
// int valid_minterms[];
// const int V; //number of valid minterms

//m is the minterm number (0 to 2^(N-1))
//n is N
extern int num_ones(int m, int n);

//will convert final array of chars ('0' '1' and '-') to array of abc chars
extern char* abc_convert(char*, char*);

extern int is_power_of_2(int x);

//converts implicant  to string of '1', '0' or '-'
extern char* string_convert(struct Implicant, int n);

extern void print(struct Implicant);

#endif
