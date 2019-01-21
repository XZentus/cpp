#include <iostream>
#include <memory>
#include <random>

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

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);
uniform_real_distribution<> mut_rng(MUTATE_MIN, MUTATE_MAX);
uniform_real_distribution<> new_rng(MUTATE_MIN, MUTATE_MAX);

enum etype { Add, Sub, Mul, Div, // arity 2
             Sin, Cos, Tan,      // arity 1
             Num,
             Arg };
const auto fun_arity_2 = Div;
const auto fun_arity_1 = Tan;

class Expr {
    
    etype type;
    
    unique_ptr<Expr> left;
    unique_ptr<Expr> right;
    double n;

public:    
    Expr(const int &);
    
    double operator()(const double &);
    double eval(const double &);
    
    void simplify(const int &);
    void mutate(const int &);
    
    etype type_of() const;
    double get_n() const;
    
    friend ostream & operator<<(ostream &, const Expr &);
};

double Expr::eval(const double & x) {
    return (*this)(x);
}

double Expr::operator()(const double & x) {
    double l = 0, r = 0;
    if(type < Num)
        l = left->eval(x);
    if(type < Sin)
        r = right->eval(x);
    switch(this->type) {
        case Add:
            return l + r;
        case Sub:
            return l - r;
        case Mul:
            return l * r;
        case Div:
            return l / r;
        case Sin:
            return sin(l);
        case Cos:
            return cos(l);
        case Tan:
            return tan(l);
        case Num:
            return n;
        default:
            return x;
    }
}

etype Expr::type_of() const {
    return type;
}

Expr::Expr(const int & depth) {
    double r1 = dis(rd);
    
    if(depth < 1) {
        if(r1 < ARG_PROBABILITY)
            type = Arg;
        else {
            type = Num;
            n = dis(rd);
        }
        return;
    }
    
    if(r1 < FUNCTION_PROBABILITY) {
        left = make_unique<Expr>(depth - 1);
        type = static_cast<etype>(rd() % (fun_arity_2 + 1));
        if(type <= fun_arity_2)
            right = make_unique<Expr>(depth - 1);
        return;
    }
    else if(r1 < ARG_PROBABILITY)
        type = Arg;
    else {
        type = Num;
        n = dis(rd);
    }
}

void Expr::mutate(const int & depth) {
    double r1 = dis(rd);
    
    if(depth <= 0) {
        if(type == Arg && r1 < MUTATE_FUN) {
            type = Num;
            n = new_rng(rd);
        }
        else if(type == Num && r1 < MUTATE_FUN)
            type = Arg;
        else if(type == Num && r1 < MUTATE_NUM)
            n += mut_rng(rd);
        return;
    }
    // TODO: ...
/*         if depth == 0 {
            return;
        }
        let mut rng = thread_rng();
        let p1: f64 = rng.gen();
        let d1 = depth - 1;

        if (p1 < MUTATE_FUN && self.is_fun()) ||
           (p1 < MUTATE_ARG && self.is_arg()) {
            *self = Expr::generate_with_depth(depth);
        }

        match self {
            Add(e1, e2) | Sub(e1, e2) |
            Mul(e1, e2) | Div(e1, e2)   => { e1.mutate_with_depth(d1); e2.mutate_with_depth(d1) },
            Sin(e1) | Cos(e1) | Tan(e1) => { e1.mutate_with_depth(d1); },
            Const(n)                    => if p1 < MUTATE_NUM {
                    *n += rng.gen_range(MUTATE_MIN, MUTATE_MAX);
                }
            _ => (),
        } */
}

double Expr::get_n() const {
    return n;
}

ostream & operator<<(ostream & os, const Expr & e) {
    etype this_type = e.type_of();
    if(this_type == Arg)
        os << 'x';
    else if(this_type == Num)
        os << e.get_n();
    else if(this_type > fun_arity_1) {
        switch(this_type) {
            case Sin:
                os << "sin(" << *e.left << ')';
                break;
            case Cos:
                os << "sin(" << *e.left << ')';
                break;
            case Tan:
                os << "sin(" << *e.left << ')';
        }
    }
    else { // arity = 2
        etype ltype = (*e.left).type_of(),
              rtype = (*e.right).type_of();
        if(ltype > fun_arity_2 ||
            (((this_type == Add) || (this_type == Sub)) && ((ltype == Add) || (ltype == Sub))) ||
            (((this_type == Mul) || (this_type == Div)) && ((ltype == Mul) || (ltype == Div))))
            os << *e.left;
        else
            os << '(' << *e.left << ')';
        
        switch(this_type) {
            case Add:
                os << " + ";
                break;
            case Sub:
                os << " - ";
                break;
            case Mul:
                os << " * ";
                break;
            case Div:
                os << " / ";
        }
        
        if(rtype > fun_arity_2 ||
            (((this_type == Add) || (this_type == Sub)) && ((rtype == Add) || (rtype == Sub))) ||
            (((this_type == Mul) || (this_type == Div)) && ((rtype == Mul) || (rtype == Div))))
            os << *e.right;
        else
            os << '(' << *e.right << ')';
    }
    return os;
}

int main() {
    Expr a(10), b(10), c(10);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    return 0;
}
