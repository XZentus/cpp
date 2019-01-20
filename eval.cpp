#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

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

class Expr {
    enum etype { Add, Sub, Mul, Div, Sin, Cos, Tan, Num, Arg };
    
    etype type;
    
    unique_ptr<Expr> left;
    unique_ptr<Expr> right;
    double n;
    
    Expr(const size_t &);
    
    double operator()(const double &);
    
    void simplify(const size_t &);
};

double Expr::operator()(const double & x) {
    double left = 0, right = 0;
    if(this->type < Num)
        left = this->left->operator()(x);
    if(this->type < Sin)
        right = this->right->operator()(x);
    switch(this->type) {
        case Add:
            return left + right;
        case Sub:
            return left - right;
        case Mul:
            return left * right;
        case Div:
            return left / right;
        case Sin:
            return sin(left);
        case Cos:
            return cos(left);
        case Tan:
            return tan(left);
        case Num:
            return this->n;
    }
    return x;
}
    

int main() {
    return 0;
}
