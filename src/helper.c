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

    // printf("during combining, values of i0->array are:\n");
    // for(int tempa=0; tempa<i1.size; tempa++) {
    //     printf("%d : %u\n", tempa, i1.array[tempa]);
    // }

    // printf("hi?\n");
    //create new implicant with size. i1.array and i2.array are merged, sorted and added to array
    (*i).size = _size;
    // printf("mallocing\n");
    (*i).array = (unsigned int*)malloc(_size * sizeof(unsigned int));
    // if (i->array) printf("DEBUG: implicant(2) was called and mp fully done\n");
    // else printf("oops for implicant(2)!\n");
    // printf("malloce'd\n");
    // for (int temp=0; temp<=i1.size; temp+=2) {
    //     // printf("half the size of combined implicant is %d\n", i1->size);
    //     // printf("size of combined implicant is %d\n", i->size);
        
    //     if (_size == 4) printf("assigning %u to position %d\n", i1.array[temp], temp);
    //     (*i).array[temp] = i1.array[temp];
    //     if (_size == 4) printf("assigned %u to position %d\n", i->array[temp], temp);

    //     if (_size == 4) printf("assigning %u to position %d\n", i2.array[temp], temp+1);
    //     (*i).array[temp+1] = i2.array[temp];
    //     if (_size == 4) printf("assigned %u to position %d\n", i->array[temp+1], temp+1);

    // }

    for (int temp = 0; temp < i1.size; temp++) {
        i->array[temp] = i1.array[temp];
    }
    for (int temp = 0; temp < i2.size; temp++) {
        i->array[temp+i1.size] = i2.array[temp];
    }

    qsort(i->array, _size, sizeof(unsigned int), compare);
}

int equal_implicants(struct Implicant* i1, struct Implicant* i2) {
    if (i1->size != i2->size) {
        // printf("size dont match\n");
        return 0;
    }

    for (int temp=0; temp<i1->size; temp++) {
        // printf("comparing %d : %d\n", i1->array[temp], i2->array[temp]);
        if (i1->array[temp] != i2->array[temp]) {
            // printf("%dth position is diff\n", temp);
            return 0;
        }
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
