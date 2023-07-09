#include <stdlib.h>
#include "stl.h"
#include "helper.h"

struct BucketStore find_implicants(list minterms) {
    struct BucketStore is;

    int size_of_bucket = 500; //calculate this fr
    struct Bucket* pBucket;
    pBucket = (struct Bucket**)malloc(size_of_bucket * sizeof(struct Bucket*));

    for (int i=0; i<minterms.total; i++) {
        int m = list_get(&minterms, i);
        struct Implicant i;
        Implicaant(1, i);
        i.array[0] = m;
        list_add(&(pBucket[num_ones(m, N)].implicants), m);
    }

    return is;
}