#include "helper.h"

//comparator for qsort
int compare(const void* num1, const void* num2) {  
    unsigned int a = *(unsigned int*) num1;  
    unsigned int b = *(unsigned int*) num2;  
    if(a > b) {
        return 1;
    } else if(a < b) {
        return -1;
    }
    return 0;  
}

void Implicaant(int _size, struct Implicant* i) {
    i->size = _size;
    i->array = (unsigned int*)malloc(_size * sizeof(unsigned int));
    // if (i->array) printf("DEBUG: implicant(1) was called and mp fully done\n");
    // else printf("oops for implicant(1)!\n");
    // *i->array = 0;
    
}

void Implicaaant(int _size, struct Implicant* i, struct Implicant i1, struct Implicant i2) {

    (*i).size = _size;
    (*i).array = (unsigned int*)malloc(_size * sizeof(unsigned int));
    
    for (int temp = 0; temp < i1.size; temp++) {
        i->array[temp] = i1.array[temp];
    }
    for (int temp = 0; temp < i2.size; temp++) {
        i->array[temp+i1.size] = i2.array[temp];
    }

    qsort(i->array, _size, sizeof(unsigned int), compare);
}

int equal_implicants(struct Implicant* i1, struct Implicant* i2) {
    if (i1->size != i2->size) return 0;

    for (int temp=0; temp<i1->size; temp++) {
        if (i1->array[temp] != i2->array[temp]) return 0;
    }

    return 1;
}

//checks if old is superet of new
int is_superset(struct Implicant new, struct Implicant old) {
    if (new.size >= old.size) return 0;

    for (int i=0; i<new.size; i++) {
        int found = 0;
        for (int j=0; j<old.size; j++) {
            if (old.array[j] == new.array[i]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }

    return 1;
}

//m is the minterm number (0 to 2^(N-1))
//n is N
int num_ones(int m, int n) {

    if (m == 0) return 0;

    int this = pow(2, n-1);
    if (m >= this) {
        return num_ones(m-this, n)+1;
    } else {
        return num_ones(m, n-1);
    }
}

//takes string of '0' '1' or '-' and converts it to abc format
char* abc_convert(char* a) {
    static char s[52];
    int s_ind = 0;

    for (int i=0; i<N; i++) {
        if (a[i] == '0') {
            s[s_ind] = 97+i;
            s[s_ind+1] = 39;
            s_ind+= 2;
        } else if (a[i] == '1') {
            s[s_ind] = 97+i;
            s_ind++;
        } else if (a[i] == '-') {
            //add nothing to s
        } else {
            printf("ERROR: value is other than 0, 1 or -\n");
            printf("Value is: %c.\n", a[i]);
            char x = 'X';
            char* ew = &x;
            return ew;
        }
    }

    str_len = s_ind;

    return s;
}

int is_power_of_2(int x) {
    if (x<0) x=-x;
    double log = log2(x);
    if (floor(log) == ceil(log)) return 1;
    else return 0;
}

//converts implicant x to string of '1', '0' or '-'
//n is the numner of variables
char* string_convert(struct Implicant x, int n) {

    char* rep;
    rep = (char*)malloc(n * sizeof(char));

    if (x.size == 1) {
        //return binary of the minterm
        unsigned int m = x.array[0];
        int q; int r;
        int filled = 0; int idx = n-1;
        while (q) {
            r = m%2;
            q = m/2;
            rep[idx++] = r+48;
            filled++;
            m = q;
        }
        for (int i=0; i<(n-filled); i++) {
            rep[i] = '0';
        }

        return rep;
    }

    else {
        //call this function with half of the minterms as a seperate implicant
        struct Implicant x1; Implicaant(x.size/2, &x1);
        struct Implicant x2; Implicaant(x.size/2, &x2);

        for (int i=0; i<x.size/2; i++) {
            x1.array[i] = x.array[i];
            x2.array[i] = x.array[i+x.size/2];
        }

        char* rep1 = string_convert(x1, n);
        char* rep2 = string_convert(x2, n);

        //then combine their result
        for (int i=0; i<n; i++) {
            if (rep1[i] == rep2[i]) {
                rep[i] = rep1[i];
            } else {
                rep[i] = '-';
            }
        }

        return rep;
    }

}

