#include <iostream>
#include <memory>
//#include <random>
#include <vector>
#include <limits>
#include <algorithm>

#include <cmath>
#include <ctime>
#include <cstdlib>

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

//random_device rd;
//mt19937 gen(rd());
//uniform_real_distribution<> dis(0.0, 1.0);
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

enum etype { Add, Sub, Mul, Div, // arity 2
             Sin, Cos, Tan,      // arity 1
             Num,
             Arg };
const auto fun_arity_2 = Div;
const auto fun_arity_1 = Tan;

typedef double(*function)(const double &);

struct SimplifyResult {
    bool is_const;
    double value;
};

class Expr {
    
    etype type;
    
    unique_ptr<Expr> left;
    unique_ptr<Expr> right;
    double n;
    
public:

    explicit Expr(const int &);
    Expr(const Expr &);
    Expr(Expr &&);
    
    double operator()(const double &) const;
    double eval(const double &) const;
    double calc_fitness(const vector<double> &) const;
    
    SimplifyResult simplify();
    bool mutate(const int &);
    
    etype type_of() const;
    double get_n() const;
    Expr * get_left() const;
    Expr * get_right() const;
    
    Expr & operator=(const Expr & e);
    
    friend ostream & operator<<(ostream &, const Expr &);
};

double Expr::eval(const double & x) const {
    return (*this)(x);
}

double Expr::operator()(const double & x) const {
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
    double r1 = dis();
    
    if(depth < 1) {
        if(r1 < ARG_PROBABILITY)
            type = Arg;
        else {
            type = Num;
            n = new_rng();
        }
        return;
    }
    
    if(r1 < FUNCTION_PROBABILITY) {
        left = make_unique<Expr>(depth - 1);
        type = static_cast<etype>(rand() % (fun_arity_2 + 1));
        if(type <= fun_arity_2)
            right = make_unique<Expr>(depth - 1);
        return;
    }
    else if(r1 < ARG_PROBABILITY)
        type = Arg;
    else {
        type = Num;
        n = new_rng();
    }
}

Expr::Expr(const Expr & e): type(e.type), n(e.n) {
    if(e.left)
        left.reset(new Expr(*e.left));
    if(e.right)
        right.reset(new Expr(*e.right));
}

Expr::Expr(Expr && e): type(e.type_of()), n(e.get_n()) {
    left.swap(e.left);
    right.swap(e.right);
}

Expr & Expr::operator=(const Expr & e) {
    type = e.type;
    n = e.n;
    if(e.left)
        left.reset(new Expr(*e.left));
    else
        left.reset(nullptr);
    if(e.right)
        right.reset(new Expr(*e.right));
    else
        right.reset(nullptr);
    return *this;
}

Expr * Expr::get_left() const {
    return left.get();
}

Expr * Expr::get_right() const {
    return left.get();
}

SimplifyResult Expr::simplify() {
    if(type == Arg)
        return {false, 0};
    else if(type == Num)
        return {true, n};
    
    SimplifyResult lsr {false, 0}, rsr {false, 0};
    if(left)
        lsr = left->simplify();
    if(right)
        rsr = right->simplify();
    
    if(lsr.is_const && type > fun_arity_2 ) { // sin, cos, tan (const)
        switch(type) {
            case Sin:
                n = sin(lsr.value);
                break;
            case Cos:
                n = cos(lsr.value);
                break;
            case Tan:
                n = tan(lsr.value);
                break;
            default:;
        }
        left.reset(nullptr);
        type = Num;
        return {true, n};
    }
    if(type <= fun_arity_2 && lsr.is_const && rsr.is_const) {
        switch(type) {
            case Add:
                n = lsr.value + rsr.value;
                break;
            case Sub:
                n = lsr.value - rsr.value;
                break;
            case Mul:
                n = lsr.value * rsr.value;
                break;
            case Div:
                n = lsr.value / rsr.value;
                break;
            default:;
        }
        left.reset(nullptr);
        right.reset(nullptr);
        type = Num;
        return {true, n};
    }
    return {false, 0};
}

bool Expr::mutate(const int & depth) {
    double r1 = dis();
    
    if(depth <= 0) {
        if(type == Arg && r1 < MUTATE_FUN) {
            type = Num;
            n = new_rng();
            return true;
        }
        else if(type == Num && r1 < MUTATE_FUN) {
            type = Arg;
            return true;
        }
        else if(type == Num && r1 < MUTATE_NUM) {
            n += mut_rng();
            return true;
        }
        return false;
    }
    
    if(type == Num         && r1 < MUTATE_NUM) {
        n += mut_rng();
        return true;
    }
    else if((type <= fun_arity_1 && r1 < MUTATE_FUN) ||
            (type == Arg         && r1 < MUTATE_ARG)) {
        left = make_unique<Expr>(depth - 1);
        type = static_cast<etype>(rand() % (fun_arity_2 + 1));
        if(type <= fun_arity_2)
            right = make_unique<Expr>(depth - 1);
        return true;
    }
    return (bool(left)  &&  left.get()->mutate(depth - 1)) ||
           (bool(right) && right.get()->mutate(depth - 1));
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
                os << "cos(" << *e.left << ')';
                break;
            case Tan:
                os << "tan(" << *e.left << ')';
            default:;
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
            default:;
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

double Expr::calc_fitness(const vector<double> & points) const {
      double result = 0;
      const double pos_inf = numeric_limits<double>::infinity();
      const double neg_inf = -(numeric_limits<double>::infinity());
      for(size_t x = 0; x < FITNESS_POINTS; x += 1) {
          const auto & p = points[x];
          double fx = this->eval(FITNESS_MIN + FITNESS_STEP * double(x));
          if(p == pos_inf || p == neg_inf) {
              if(p != fx)
                  result += EXCEPTION_WEIGHT;
          }
          else {
              double addition = abs(fx - p);
              if(addition == numeric_limits<double>::quiet_NaN() ||
                 addition == numeric_limits<double>::signaling_NaN())
                  addition = EXCEPTION_WEIGHT;
              result += addition;
          }

      }
      return result;
}

void make_points(function f, vector<double> & v) {
    v.clear();
    v.reserve(FITNESS_POINTS);
    
    for(int x = 0; x < FITNESS_POINTS; x += 1)
        v.emplace_back(f(FITNESS_MIN + FITNESS_STEP * double(x)));
}

void train(vector<Expr> & population, const vector<double> & points, const size_t & generations) {
    const size_t pop_size = population.size();
    vector<pair<Expr, double>> db;
    db.reserve(population.size());

    for(size_t i = 0; i < pop_size; i += 1) {
        auto & expr = population[i];
        double fit = expr.calc_fitness(points);

        db.emplace_back(move(expr), fit);
    }
    population.clear();

    for(size_t i = 0; i < generations; i += 1) {
        if(i % 100 == 0)
            cout << "Generation " << i << "..." << endl;

        //mutate, add mutated
        const auto current_len = db.size();
        
        for(size_t i = 0; i < current_len; i += 1) {
            Expr new_expr(db[i].first);
            if(!new_expr.mutate(DEPTH))
                continue;
            double fit = new_expr.calc_fitness(points);
            if(fit < db[i].second) {
                if(dis() < CHANCE_DUPLICATE)
                    db.emplace_back(move(new_expr), fit);
                else {
                    db[i].first = new_expr;
                    db[i].second = fit;
                }
            }
        }
        //cout << "\tMutate done" << endl;

        //sort
        sort(db.begin(), db.end(), [](const auto & a, const auto & b){ return a.second < b.second; });
        //cout << "\tSort done" << endl;

        //drop
        db.erase(db.begin() + INDIVIDUALS_SURVIVE, db.end());
        //cout << "\tDrop done" << endl;

        //add new
        for(size_t i = INDIVIDUALS_SURVIVE; i < POPULATION_SIZE; i += 1) {
            auto new_expr = Expr(DEPTH);
            double fit = new_expr.calc_fitness(points);
            db.emplace_back(move(new_expr), fit);
        }
        //cout << "\tNew creatures done" << endl;
    }

    population.clear();
    for(size_t i = 0; i < POPULATION_SIZE; i += 1) {
        auto e = db[i].first;
        //e.simplify();
        population.emplace_back(move(e));
    }
}

double target_fun(const double & x) {
    return cos(2.16327*x) + x*0.3423 - 3.0;
}

int main() {
    srand(time(0));
    vector<Expr> population;
    population.reserve(POPULATION_SIZE);
    
    for(size_t i = 0; i < POPULATION_SIZE; i += 1)
        population.emplace_back(10);
    
    vector<double> points;
    make_points(target_fun, points);

    cout << "Trainig begin..." << endl;
    train(population, points, 1000);
    cout << "Trainig done" << endl;

    for(size_t i = 0; i < 10; i += 1) {
        cout << population[i] << "\nFitness: " << population[i].calc_fitness(points) << endl;
        population[i].simplify();
        cout << population[i] << "\nFitness: " << population[i].calc_fitness(points) << "\n----------------------------------------\n" << endl;
    }
    
    return 0;
}
