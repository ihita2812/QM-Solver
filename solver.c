//things to do:
//1. power_of_2 calculation
//2. if implicant x doesnt already exist in nbucket[i].implicants
//3. calculate initial size of bucket
//4. N the big N
//5. calculation of number of 1's

#include <stdlib.h>
#include "stl.h"
#include "helper.h"

int power_of_2;

struct BucketStore find_implicants(list minterms) {
    struct BucketStore is;

    int size_of_bucket = 500; //calculate this fr
    struct Bucket* pBucket;
    pBucket = (struct Bucket**)malloc(size_of_bucket * sizeof(struct Bucket*));

    for (int i=0; i<size_of_bucket; i++) {
        list_init(&(pBucket[i]));
    }

    for (int i=0; i<minterms.size; i++) {
        int m = list_get(&minterms, i);
        struct Implicant i;
        Implicaant(1, i);
        i.array[0] = m;
        list_add(&(pBucket[num_ones(m, N)].implicants), &i);
    }
    stack_push(&is, &pBucket);

    while (1) {

        struct Bucket* nBucket;
        nBucket = (struct Bucket**)malloc((size_of_bucket-1) * sizeof(struct Bucket*));

        for (int i=0; i<size_of_bucket-1; i++) {
            list_init(&(pBucket[i]));
        }

        int added = 0;
        for (int i=0; i<size_of_bucket-2; i++) {
            struct Bucket b0 = pBucket[i];
            struct Bucket b1 = pBucket[i+1];
            for (int j=0; j < b0.implicants.size; j++) {
                for (int k=0; k < b1.implicants.size; k++) {
                    struct Implicant* i0 = list_get(&b0, j);
                    struct Implicant* i1 = list_get(&b1, k);
                    int leng = i0->size;
                    int diff = i0->array[0] - i1->array[0];
                    int add = 0;
                    if (diff == power_of_2) {
                        add = 1;
                        for (int l=1; l<leng; l++) {
                            if (i0->array[l] - i1->array[l] != diff) add = 0;
                        }
                    }
                    if (add) {
                        struct Implicant x;
                        Implicant(2*leng, x, *i0, *i1); // write this function!!!
                        // if x doesnt already exist in nBucket[i].implicants, then -->
                        list_add(&(nBucket[i].implicants), &x);
                        added++;
                    }
                }
            }
        }

        if (added > 1) {
            stack_push(&is, &pBucket);
            pBucket = nBucket;
        } else {
            break;
        }

    }

    return is;
}