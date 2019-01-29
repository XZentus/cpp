#include "parameters.h"

#include <cstdlib>

double dis() {
    return double(rand()) / double(RAND_MAX);
}
//uniform_real_distribution<> mut_rng(MUTATE_MIN, MUTATE_MAX);
double mut_rng() {
    return dis() * (MUTATE_MAX - MUTATE_MIN) - MUTATE_MIN;
}
//uniform_real_distribution<> new_rng(MIN_VAL, MAX_VAL);
double new_rng() {
    return dis() * (MAX_VAL - MIN_VAL) - MIN_VAL;
}