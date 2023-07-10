#include "helper.h"

void Implicaant(int _size, struct Implicant i) {
    i.size = _size;
    i.array = (int*)malloc(_size * sizeof(int));
}

void Implicant(int _size, struct Implicant i, struct Implicant i1, struct Implicant i2) {
    //create new implicant with size. i1.array and i2.array are merged, sorted and added to array
    i.size = _size;
    i.array = (int*)malloc(_size * sizeof(int));
}

int equal_implicants(struct Implicant i1, struct Implicant i2) {
    if (i1.size != i2.size) return 0;

    for (int temp=0; temp<i1.size; temp++) {
        if (i1.array[temp] != i2.array[temp]) return 0;
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

char* string(char* a) {
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
        } else if (a[i] == dash) {
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
    double log = log2(x);
    if (floor(log) == ceil(log)) return 1;
    else return 0;
}
