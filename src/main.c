/*

PURPOSE OF FILE:
Handling input/output
and
starting the program

*/

#include <stdio.h>
#include <string.h>
#include "solver.h"

unsigned int inputs[4097];
unsigned int* arr;

int main() {

    printf("Enter 1 for minterms and 0 for maxterms: ");
    int mins;
    scanf("%d", &mins);
    if ((mins!=0) && (mins!= 1)) {
        printf("Choose 0 or 1 only!\n");
        exit(1);
    }

    int num_ins;

    printf("Enter no. of ");
    if (mins) printf("minterms");
    else printf("maxterms");
    printf(" (without dont cares) : ");
    scanf("%d", &num_ins);

    for (int i=0; i<num_ins; i++) {
        printf("Enter ");
        if (mins) printf("minterm");
        else printf("maxterm");
        printf("number %d : ", i+1);
        scanf("%u", &inputs[i]);
    }

    int dont_cares;

    printf("Enter no. of dont-cares : ");
    scanf("%d", &dont_cares);

    for (int i=num_ins; i<num_ins+dont_cares; i++) {
        printf("Enter dont-care number %d : ", i+1);
        scanf("%u", &inputs[i]);
    }

    list minterms; list_init(&minterms);
    list minterms_without_dontcares; list_init(&minterms_without_dontcares);
    list maxterms; list_init(&maxterms);

    if (mins) {
        for (int i=0; i<num_ins; i++) {
            list_add(&minterms, &inputs[i]);
            list_add(&minterms_without_dontcares, &inputs[i]);
        }
    }

    else {
        for (int i=0; i<num_ins+dont_cares; i++) {
            list_add(&maxterms, &inputs[i]);
        }
        int size_of_array = pow(2, ceil(log2(*((unsigned int*)list_get(&maxterms, list_max(&maxterms))))));
        arr = (unsigned int*)malloc(sizeof(unsigned int) * size_of_array);
        if (arr == NULL) {printf("Malloc failure\nCODE: 2\n"); exit(2);}
        int* arr_min = (int*)malloc(sizeof(int) * size_of_array);
        if (arr_min == NULL) {printf("Malloc failure\nCODE: 3\n"); exit(3);}
        for (int i=0; i<size_of_array; i++) {
            arr[i] = i;
            arr_min[i] = 1;
        }
        for (int i=0; i<num_ins+dont_cares; i++) {
            arr_min[inputs[i]] = 0;
        }
        for (int i=0; i<size_of_array; i++) {
            if (arr_min[i]) {
                list_add(&minterms, &arr[i]);
                list_add(&minterms_without_dontcares, &arr[i]);
            }
        }
        free(arr_min);
    }

    list_free(&maxterms);

    for (int i=num_ins; i<num_ins+dont_cares; i++) {
        list_add(&minterms, &inputs[i]);
    }

    N = ceil(log2(*((unsigned int*)list_get(&minterms, list_max(&minterms)))));

    // printf("Enter number of variables: ");
    // scanf("%d", &N);
    
    //-----------------------------FOR TESTING STRING() FUNCTION-----------------------------
    // char arr[4];
    // arr[0] = '1';
    // arr[1] = '0';
    // arr[2] = dash;
    // arr[3] = '0';
    // char* ans = string(arr);
    // for (int i=0; i<str_len; i++) {
    //     printf("%c", *(ans+i));
    // }
    // printf("\n");
    //---------------------------------------------------------------------------------------




    //-----------------------------INITIALISATION-----------------------------
    // struct list terms;
    // list_init(&terms);
    // unsigned int a=0;
    // list_add(&terms, &a);
    // unsigned int b=1;
    // list_add(&terms, &b);
    // unsigned int c=2;
    // list_add(&terms, &c);
    // unsigned int d=5;
    // list_add(&terms, &d);
    // unsigned int e=6;
    // list_add(&terms, &e);
    // unsigned int f=7;
    // list_add(&terms, &f);
    // unsigned int g=8;
    // list_add(&terms, &g);
    // unsigned int h=9;
    // list_add(&terms, &h);
    // unsigned int i=10;
    // list_add(&terms, &i);
    // unsigned int j=14;
    // list_add(&terms, &j);
    //------------------------------------------------------------------------
    


    
    //-----------------------------FOR TESTING FIND_IMPLICANTS FUNCTION-----------------------------
    struct BucketStore* lol = find_implicants(minterms);
    printf("no. of implicants: %d\n", (lol->store).size);

    while (lol->store.size) {
        // printf("Level %d\n\n", i);

        struct Bucket* is = (struct Bucket*)stack_top(&(lol->store));
        for (int temp=0; temp<is->implicants.size; temp++) {
            struct Implicant* h = (struct Implicant*)list_get(&is->implicants, temp);
            for (int temp3=0; temp3<h->size; temp3++) {
                printf("%u ", h->array[temp3]);
            }
            printf("\n");
        }

        stack_pop(&(lol->store));
    }
    
    //----------------------------------------------------------------------------------------------





    //-----------------------------FOR TESTING PRIME_IMPLICANTS FUNCTION-----------------------------
    struct Bucket* lol2 = prime_implicants(*find_implicants(minterms));
    printf("\nno. of prime implicants: %d\n", (lol2->implicants).size);
    
    for (int i=0; i<(lol2->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&lol2->implicants, i);
        for (int j=0; j<h->size; j++) {
            printf("%u ", h->array[j]);
        }
        printf("\n");
    }
    //-----------------------------------------------------------------------------------------------




    //-----------------------------FOR TESTING ESS_PRIME_IMPLICANTS FUNCTION-----------------------------
    struct Bucket* lol3 = ess_prime_implicants(minterms_without_dontcares, lol2->implicants);
    printf("\nno. of essential prime implicants: %d\n", (lol3->implicants).size);

    for (int i=0; i<(lol3->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&lol3->implicants, i);
        for (int j=0; j<h->size; j++) {
            printf("%u ", h->array[j]);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------------    

    //-----------------------------GIVING PROPER OUTPUT-----------------------------
    printf("\noutput is:\n");
    char** container;
    container = (char**)malloc(sizeof(char*) * (lol3->implicants).size);
    if (container == NULL) {printf("Malloc failure\nCODE: 4\n"); exit(4);}
    for (int i=0; i<(lol3->implicants).size; i++) {
        char* x;
        x = (char*)malloc(52 * sizeof(char));
        if (x == NULL) {printf("Malloc failure\nCODE: 5\n"); exit(5);}
        container[i] = x + i * 52 * sizeof(char*);
    }
    for (int i=0; i<(lol3->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&lol3->implicants, i);
        container[i] = abc_convert(string_convert(*h, N), container[i]);
        // printf("\nlength is %d : ", str_len);
        for (int j=0; j<str_len; j++) {
            printf("%c", container[i][j]);
        }
        if (i != ((lol3->implicants).size-1)) printf(" + ");
        // else printf("%s + ", container[i]);
    }
    //------------------------------------------------------------------------------
    



    return 0;
}
