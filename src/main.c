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
    unsigned int b=3;
    list_add(&terms, &b);
    unsigned int c=4;
    list_add(&terms, &c);
    unsigned int d=8;
    list_add(&terms, &d);
    unsigned int e=9;
    list_add(&terms, &e);
    unsigned int f=12;
    list_add(&terms, &f);
    //------------------------------------------------------------------------
    


    
    //-----------------------------FOR TESTING FIND_IMPLICANTS FUNCTION-----------------------------
    printf("\nall implicants:\n");
    // struct BucketStore* lol = find_implicants(terms);
    // printf("size of main stack is %d\n", (lol->store).size);

    /*
    int i= 1;
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
        

        // int size = sizeof(is)/sizeof(struct Bucket*);
        // printf("\nnumber of buckets is %d\n", size);

        // for (int temp=0; temp<size; temp++) {
        //     printf("bucket number %d\n\n", temp);
        //     struct Bucket* this = is[temp];
        //     printf("\nnumber of implicants is %d\n", this->implicants.size);
        //     for (int temp2=0; temp2<this->implicants.size; temp2++){
        //         printf("implicant number %d\n\n", temp2);
        //         struct Implicant* h = (struct Implicant*)list_get(&this->implicants, temp2);
        //         for (int temp3=0; temp3<h->size; temp3++) {
        //             printf("%u ", h->array[temp3]);
        //         }
        //         printf("\n");
        //     }
        // }

    //     // for (int temp=0; temp<is->size; temp++) {
    //     //     struct Implicant h = *(struct Implicant*)list_get(is, temp);
    //     //     printf("Implicant %d:\n", temp);
    //     //     for (int temp2=0; temp2<h.size; temp2++) {
    //     //         printf("%d ", h.array[temp2]);
    //     //     }
    //     //     printf("\n");
    //     // }

        stack_pop(&(lol->store));
        i++;
    }
    */
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

    return 0;
}
