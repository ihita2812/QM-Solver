//things to do:
//1. power_of_2 calculation                                         count
//2. if implicant x doesnt already exist in nbucket[i].implicants   count
//3. calculate initial size of bucket                               count
//4. N the big N
//5. calculation of number of 1's
//6. improve list_sort

#include <stdlib.h>
#include "solver.h"

struct BucketStore* find_implicants(list minterms) {
    struct BucketStore* implicantBucketStore; //BucketStore to be returned
    
    implicantBucketStore = (struct BucketStore*)malloc(sizeof(struct BucketStore*));
    stack_init(&(implicantBucketStore->store));

    //initial grouping of minterms according to number of 1s

    int size_of_bucket = ceil(log2(*((unsigned int*)list_get(&minterms, minterms.size-1))))+1;
    
    // printf("DEBUG: size of bucket is %d\n", size_of_bucket);
    struct Bucket** pBucket; //an array of pointers to buckets
    pBucket = (struct Bucket**)calloc(size_of_bucket , sizeof(struct Bucket*));
    if (pBucket == NULL) printf("oops for p bucket!\n");

    for (int i=0; i<size_of_bucket; i++) {
        //alloting space to bucket:
        pBucket[i] = (struct Bucket*)malloc(sizeof(list));

        //initialising list of the bucket:
        list_init(&pBucket[i]->implicants);
    }

    list implicant_pointer_array;
    list_init(&implicant_pointer_array);

    for (int i=0; i<100; i++) {
        struct Implicant* x;
        list_add(&implicant_pointer_array, x + sizeof(struct Implicant*) * i);
        list_set(&implicant_pointer_array, i, (struct Implicant*)malloc(sizeof(struct Implicant)));
        // printf("saved pointer %p to implicant pointer array\n", x + sizeof(struct Implicant*) * i);
    }

    for (int i=0; i<minterms.size; i++) {
        unsigned int m = *(unsigned int*)list_get(&minterms, i);
        // printf("\n\ncurrent minterm is %u\n", m);
        // printf("got pointer %p from implicant pointer array\n", (struct Implicant*)list_get(&implicant_pointer_array, i));
        Implicaant(1, (struct Implicant*)list_get(&implicant_pointer_array, i));
        ((struct Implicant*)list_get(&implicant_pointer_array, i))->array[0] = m;
        int ones = num_ones(m, N);
        // printf("adding it to pbucket[%d]\n", ones);
        list_add(&pBucket[ones]->implicants, (struct Implicant*)list_get(&implicant_pointer_array, i));
    }
    
    // for (int temp=0; temp<size_of_bucket; temp++) {
    //     printf("\n\nGROUP WITH %d 1s: \n", temp);
    //     for (int temp2=0; temp2<(pBucket[temp]->implicants).size; temp2++) {
    //         // (struct Implicant*) this= list_get(&pBucket[temp]->implicants, temp2);
    //         for (int temp3=0; temp3<((struct Implicant*)list_get(&pBucket[temp]->implicants, temp2))->size; temp3++) {
    //             printf("%u", ((struct Implicant*)list_get(&pBucket[temp]->implicants, temp2))->array[temp3]);
    //         }
    //         printf("\n");
    //     }
    // }

    int added_array[100];
    added_array[0] = 0;
    int grouping = 0;
    while (1) {
        //keep grouping according to placement of 1s

        struct Bucket** nBucket;
        nBucket = (struct Bucket**)malloc((size_of_bucket-1) * sizeof(struct Bucket*));

        for (int i=0; i<size_of_bucket-1; i++) {
            //alloting space to bucket:
            nBucket[i] = (struct Bucket*)malloc(sizeof(list));

            //initialising list of the bucket:
            list_init(&nBucket[i]->implicants);
        }

        int added = 0;
        // int counter = 0;
        for (int i=0; i<size_of_bucket-1; i++) {
            // printf("\n\nDEBUG: this is iter %d\n\n",i);
            struct Bucket* b0 = pBucket[i];
            struct Bucket* b1 = pBucket[i+1];
            for (int j=0; j < (b0->implicants).size; j++) {
                for (int k=0; k < (b1->implicants).size; k++) {
                    struct Implicant* i0 = (struct Implicant*)list_get(&b0->implicants, j);
                    struct Implicant* i1 = (struct Implicant*)list_get(&b1->implicants, k);
                    int leng = i0->size;
                    int diff = i0->array[0] - i1->array[0];
                    int add = 0;
                    // printf("\nminterm 0.0 is %d and minterm 1.0 is %d, their difference is %d\n", i0->array[0], i1->array[0], diff);
                    
                    // printf("much before combining, values of i0->array are:\n");
                    // for(int tempa=0; tempa<i0->size; tempa++) {
                    //     printf("%d : %u\n", tempa, i0->array[tempa]);
                    // }
                    int valid = 1;

                    if ((is_power_of_2(i0->array[0]) && diff>0)
                        ||
                        (is_power_of_2(i1->array[0]) && diff<0)) valid = 0;
                    
                    if (is_power_of_2(diff) && valid) {
                        // printf("checking if they shall be grouped\n");
                        add = 1;
                        for (int l=1; l<leng; l++) {
                            // printf("minterm 0.%d is %d and minterm 1.%d is %d, their difference is %d\n", l, i0->array[l], l, i1->array[l], i0->array[l] - i1->array[l]);
                            if ((i0->array[l] - i1->array[l]) != diff) add = 0;
                        }
                    }
                    if (add) {
                        // printf("yes they shall be grouped\n");
                        // printf("checking if it already exists\n");
                        // struct Implicant* x = (struct Implicant*)list_get(&implicant_pointer_array, minterms.size+added*sizeof(struct Implicant*));
                        // printf("accessing minterms.size + %d from implicant pointer array\n", added);
                        // struct Implicant* x = (struct Implicant*)list_get(&implicant_pointer_array, minterms.size + sizeof(struct Implicant*) * added);
                        
                        // printf("before combining, values of i0->array are:\n");
                        // for(int tempa=0; tempa<i0->size; tempa++) {
                        //     printf("%d : %u\n", tempa, i0->array[tempa]);
                        // }

                        Implicaaant(2*leng, (struct Implicant*)list_get(&implicant_pointer_array, minterms.size + added + added_array[grouping]), *i0, *i1); // write this function!!!
                        
                        // printf("after combining, values of i0->array are:\n");
                        // for(int tempa=0; tempa<i0->size; tempa++) {
                        //     printf("%d : %u\n", tempa, i0->array[tempa]);
                        // }

                        // printf("this is the combined implicant:\n");
                        //     for (int r=0; r<2*leng; r++) {
                        //     printf("%u ", ((struct Implicant*)(list_get(&implicant_pointer_array, minterms.size + added + added_array[grouping])))->array[r]);
                        // }
                        // printf("\n");

                        // if x doesnt already exist in nBucket[i].implicants, then -->

                        int really_add = 1;
                        // list implicants_added = nBucket[i]->implicants;
                        for (int temp=0; temp<(nBucket[i]->implicants).size; temp++) {
                            if (equal_implicants((struct Implicant*)list_get(&nBucket[i]->implicants, temp), (struct Implicant*)list_get(&implicant_pointer_array, minterms.size + added + added_array[grouping]))) {
                                really_add = 0;
                                break;
                            }
                        }

                        if (really_add) {
                            // printf("they are unique, adding\n");
                            list_add(&nBucket[i]->implicants, (struct Implicant*)list_get(&implicant_pointer_array, minterms.size + added + added_array[grouping]));
                            added++;
                        }
                    }
                }
            }
        }

        for (int i=0; i<size_of_bucket; i++) {
            stack_push(&(implicantBucketStore->store), pBucket[i]);
        }
        size_of_bucket--;
        // printf("grouping %d : %d were grouped and size of stack is now %d\n", grouping, added, (implicantBucketStore->store).size);
        
        //stop if 1 or less new groupings have been made
        if (added > 1) {
            // printf("\n%d were grouped and added\n", added);
            struct Bucket*** pptr = &pBucket;
            struct Bucket*** nptr = &nBucket;
            *pptr = *nptr;
            // printf("size of pbucket is now %d\n", --size_of_bucket);
            added_array[grouping+1] = added + added_array[grouping];
        } else {
            for (int i=0; i<size_of_bucket-1; i++) {
                stack_push(&(implicantBucketStore->store), nBucket[i]);
            }    
            break;
        }

        grouping++;

    }

    return implicantBucketStore;
}

struct Bucket* prime_implicants(struct BucketStore all_implicants) {
    struct Bucket* primes;
    primes = (struct Bucket*)malloc(sizeof(struct Bucket*));
    list_init(&primes->implicants);
    
    stack implicants;
    stack_init(&implicants);
    implicants = all_implicants.store;

    while (implicants.size) {
        struct Bucket* current = stack_top(&implicants);
        
        for (int i=0; i<(current->implicants).size; i++) {
            struct Implicant* new = (struct Implicant*)list_get(&(current->implicants), i);
            int add = 1;
            
            for (int j=0; j<primes->implicants.size; j++) {
                struct Implicant* old = (struct Implicant*)list_get(&primes->implicants, j);
                if (is_superset(*new, *old)) {
                    add = 0;
                    break;
                }
            }

            if (add) {
                list_add(&primes->implicants, new);
            }
        }
        
        stack_pop(&implicants);
    }

    return primes;
}

struct Bucket* ess_prime_implicants(list minterms, list prime_implicants) {
    struct Bucket* ess_primes;
    ess_primes = (struct Bucket*)malloc(sizeof(struct Bucket*));
    list_init(&ess_primes->implicants);

    unsigned int max_minterm = *(unsigned int*)list_get(&minterms, list_max(&minterms));
    
    //done_array initialised to 0
    //to keep track if the minterm is done or not
    //"done" means atleast one implicant in ess_primes coveres it
    int* done_array;
    done_array = (int*)malloc(sizeof(int) * (int)(max_minterm+1));
    for (int temp=0; temp<=max_minterm; temp++) {
        done_array[temp] = 0;
    }

    //step 1
    //taking the initial essential prime implicants
    for (int i=0; i<minterms.size; i++) {
        unsigned int m = *(unsigned int*)list_get(&minterms, i);
        int covered = 0;

        struct Implicant* current_impl;
        int current_idx;
        for (int j=0; j<prime_implicants.size; j++) {
            struct Implicant* impl = (struct Implicant*)list_get(&prime_implicants, j);
    
            for (int k=0; k<impl->size; k++) {
                if (impl->array[k] == m) {
                    current_impl = impl;
                    current_idx = j;
                    covered++;
                    break;
                }
            }
        }

        if (covered == 1) {
            list_add(&ess_primes->implicants, current_impl);
            list_delete(&prime_implicants, current_idx);
        }
    }

    
    int covered_minterms = 0;
    while (covered_minterms != minterms.size) {

        //step 1a
        //all minterms in essential prime implicants are marked as done
        for (int i=0; i<((ess_primes->implicants).size); i++) {
            struct Implicant* impl = (struct Implicant*)list_get(&ess_primes->implicants, i);

            for (int j=0; j<impl->size; j++) {
                if (done_array[(int)(impl->array[j])] != 1) {
                    done_array[(int)(impl->array[j])] = 1;
                    covered_minterms++;
                }
            }
        }

        if (covered_minterms != minterms.size) {

            //step 2
            //prime implicants not covering any of the left minterms are removed
            for (int i=0; i<prime_implicants.size; i++) {
                struct Implicant* impl = (struct Implicant*)list_get(&prime_implicants, i);

                int covered = 0;
                for (int j=0; j<impl->size; j++) {
                    if (done_array[(int)(impl->array[j])] == 0) covered++;
                }

                if (covered == 0) {
                    list_delete(&prime_implicants, i);
                    i--;
                }
            }

            //step 3
            //prime implicant covering max no. of left minterms is added
            struct Implicant* max_covering_impl;
            int max_covered = 0;
            for (int i=0; i<prime_implicants.size; i++) {
                struct Implicant* impl = (struct Implicant*)list_get(&prime_implicants, i);

                int covered = 0;
                for (int j=0; j<impl->size; j++) {
                    if (done_array[(int)(impl->array[j])] == 0) covered++;
                }

                if (covered > max_covered) {
                    max_covered = covered;
                    max_covering_impl = impl;
                }
            }
            if (max_covered != 0) {
                list_add(&ess_primes->implicants, max_covering_impl);
            }

        }

    }

    return ess_primes;
    
}