#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include "stl.h"

struct Implicant {
    unsigned int* array; //integer array of size = size in sorted order
    int size;
};

struct Bucket {
    list implicants;
};

struct BucketStore {
    stack store;
};

#endif