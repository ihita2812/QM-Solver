#ifndef SOLVER_H_
#define SOLVER_H_

#include "helper.h"

extern struct BucketStore* find_implicants(list);

extern struct Bucket* prime_implicants(struct BucketStore);

struct Bucket* ess_prime_implicants(list, list);

#endif
