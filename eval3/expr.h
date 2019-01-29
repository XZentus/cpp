#include <iostream>
#include <memory>
#include <vector>

using std::ostream, std::vector, std::unique_ptr;

enum etype { Add, Sub, Mul, Div, // arity 2
             Sin, Cos, Tan,      // arity 1
             Num,
             Arg };
const auto fun_arity_2 = Div;
const auto fun_arity_1 = Tan;

struct SimplifyResult {
    bool is_const;
    double value;
};

class Expr {
    
    etype type;
    
    unique_ptr<Expr> left;
    unique_ptr<Expr> right;
    double n;
    vector <double> result;
    
    void eval();
    
public:

    explicit Expr(const int &);
    Expr(const Expr &);
    Expr(Expr &&);
    
    void operator()();
    
    SimplifyResult simplify();
    bool mutate(const int &);
    double calc_fitness(const vector<double> &);
    
    etype type_of() const;
    double get_n() const;
    
    vector<double> & get_result();
    
    Expr * get_left() const;
    Expr * get_right() const;
    
    Expr & operator=(const Expr & e);
    
    friend ostream & operator<<(ostream &, const Expr &);
};