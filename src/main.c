/*

PURPOSE OF FILE:
Handling input/output
and
starting the program

*/

#include <stdio.h>
#include "solver.h"

int main() {
    printf("Enter number of variables: ");
    scanf("%d", &N);
    
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
    struct list terms;
    list_init(&terms);
    
    unsigned int a=0;
    list_add(&terms, &a);
    unsigned int b=1;
    list_add(&terms, &b);
    unsigned int c=2;
    list_add(&terms, &c);
    unsigned int d=5;
    list_add(&terms, &d);
    unsigned int e=6;
    list_add(&terms, &e);
    unsigned int f=7;
    list_add(&terms, &f);
    unsigned int g=8;
    list_add(&terms, &g);
    unsigned int h=9;
    list_add(&terms, &h);
    unsigned int i=10;
    list_add(&terms, &i);
    unsigned int j=14;
    list_add(&terms, &j);
    //------------------------------------------------------------------------
    


    
    //-----------------------------FOR TESTING FIND_IMPLICANTS FUNCTION-----------------------------
    // struct BucketStore* lol = find_implicants(terms);
    // printf("no. of implicants: %d\n", (lol->store).size);

    // while (lol->store.size) {
    //     // printf("Level %d\n\n", i);

    //     struct Bucket* is = (struct Bucket*)stack_top(&(lol->store));
    //     for (int temp=0; temp<is->implicants.size; temp++) {
    //         struct Implicant* h = (struct Implicant*)list_get(&is->implicants, temp);
    //         for (int temp3=0; temp3<h->size; temp3++) {
    //             printf("%u ", h->array[temp3]);
    //         }
    //         printf("\n");
    //     }

    //     stack_pop(&(lol->store));
    // }
    
    //----------------------------------------------------------------------------------------------





    //-----------------------------FOR TESTING PRIME_IMPLICANTS FUNCTION-----------------------------
    struct Bucket* lol2 = prime_implicants(*find_implicants(terms));
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
    struct Bucket* lol3 = ess_prime_implicants(terms, lol2->implicants);
    printf("\nno. of essential prime implicants: %d\n", (lol3->implicants).size);

    for (int i=0; i<(lol3->implicants).size; i++) {
        struct Implicant* h = (struct Implicant*)list_get(&lol3->implicants, i);
        for (int j=0; j<h->size; j++) {
            printf("%u ", h->array[j]);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------------    


    return 0;
}
