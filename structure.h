#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include "stl.h"

struct Implicant {
    int* array; //integer array of size in sorted order
    int size;
};

struct Bucket {
    int x;
    // list<Implicant> implicants;
    list implicants;
};

struct BucketStore {
    int y;
    // stack<Bucket*> store;
    // stack<Implicant*> store; ?
};

#endif