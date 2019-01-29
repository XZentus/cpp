#include <cstddef>

const double FITNESS_MIN          =   -7.0;
const double FITNESS_MAX          =    7.0;
const int    FITNESS_POINTS       = 2000;
const double FITNESS_STEP         = (FITNESS_MAX - FITNESS_MIN) / double(FITNESS_POINTS - 1);

const double FUNCTION_PROBABILITY =    0.5;
const double ARG_PROBABILITY      =    0.7;
const double MIN_VAL              =  -20.0;
const double MAX_VAL              =   20.0;

const double MUTATE_ARG           =    0.1;
const double MUTATE_NUM           =    0.6;
const double MUTATE_FUN           =    0.2;
const double MUTATE_MIN           =   -2.0;
const double MUTATE_MAX           =    2.0;

const size_t POPULATION_SIZE      =   80;
const size_t INDIVIDUALS_SURVIVE  =   30;
const double CHANCE_DUPLICATE     =    0.02;

const double EXCEPTION_WEIGHT     = 10000.0;

const size_t DEPTH                = 10;

double dis();
//uniform_real_distribution<> mut_rng(MUTATE_MIN, MUTATE_MAX);
double mut_rng();
//uniform_real_distribution<> new_rng(MIN_VAL, MAX_VAL);
double new_rng();