#include <stdio.h>
#include <string.h>
#include "solver.h"

unsigned int inputs[4097]; //stores minterm/maxterms given by user
unsigned int* arr;

int num_vars; //number of variables in boolean expr

int DETAIL = 0; //flag for if detail has to be shown or not

int main(int argc, char** argv) {

    if (argc == 2) {
        if (!strcmp(argv[1], "detail")) DETAIL = 1;
        else {
            printf("Incorrect argument(s) to program call.");
            exit(1);
        }
    }

    else if (argc > 2) {
        printf("Incorrect argument(s) to program call.");
        exit(1);
    }

    //-------------------------------------------------------------------------------
    
    printf("Enter 1 for minterms and 0 for maxterms: ");
    int mins;
    scanf("%d", &mins);
    if ((mins!=0) && (mins!= 1)) {
        printf("Choose 0 or 1 only!\n");
        exit(1);
    }

    //-------------------------------------------------------------------------------
    
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
        printf(" %d : ", i+1);
        scanf("%u", &inputs[i]);
    }

    //-------------------------------------------------------------------------------
    
    int dont_cares;

    printf("Enter no. of dont-cares : ");
    scanf("%d", &dont_cares);

    for (int i=num_ins; i<num_ins+dont_cares; i++) {
        printf("Enter dont-care %d : ", i+1);
        scanf("%u", &inputs[i]);
    }

    //-------------------------------------------------------------------------------
    
    list minterms; list_init(&minterms);
    list minterms_without_dontcares; list_init(&minterms_without_dontcares);
    list maxterms; list_init(&maxterms);

    //-------------------------------------------------------------------------------
    
    if (mins) {
        for (int i=0; i<num_ins; i++) {
            list_add(&minterms, &inputs[i]);
            list_add(&minterms_without_dontcares, &inputs[i]);
        }
    }

    //-------------------------------------------------------------------------------
    
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

    //-------------------------------------------------------------------------------
    
    num_vars = N(&minterms);

    if (DETAIL) {

    //-----------------------------FOR TESTING FIND_IMPLICANTS FUNCTION-----------------------------
    struct BucketStore* lol = find_implicants(minterms, num_vars);
    printf("\nNo. of implicants: %d\n", (lol->store).size);

    while (lol->store.size) {
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
    struct Bucket* lol2 = prime_implicants(*find_implicants(minterms, num_vars));
    printf("\nNo. of prime implicants: %d\n", (lol2->implicants).size);
    
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
    printf("\nNo. of essential prime implicants: %d\n", (lol3->implicants).size);

    for (int i=0; i<(lol3->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&lol3->implicants, i);
        for (int j=0; j<h->size; j++) {
            printf("%u ", h->array[j]);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------------    

    }


    //-----------------------------GIVING PROPER OUTPUT-----------------------------
    printf("\n\nMinimised boolean expression:\n");

    char** container;
    struct Bucket* ans = ess_prime_implicants(minterms_without_dontcares, (prime_implicants(*find_implicants(minterms, num_vars)))->implicants);
    container = (char**)malloc(sizeof(char*) * (ans->implicants).size);
    if (container == NULL) {printf("Malloc failure\nCODE: 4\n"); exit(4);}
    for (int i=0; i<(ans->implicants).size; i++) {
        char* x;
        x = (char*)malloc(52 * sizeof(char));
        if (x == NULL) {printf("Malloc failure\nCODE: 5\n"); exit(5);}
        container[i] = x + i * 52 * sizeof(char*);
    }
    for (int i=0; i<(ans->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&ans->implicants, i);
        container[i] = abc_convert(string_convert(*h, num_vars), container[i], num_vars);
        printf("%s", container[i]);
        if (i != ((ans->implicants).size-1)) printf(" + ");
    }
    //------------------------------------------------------------------------------

    return 0;
}
