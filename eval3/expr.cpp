#include <iostream>
#include <memory>
#include <vector>

#include <cmath>

#include "expr.h"

#include "parameters.h"

using namespace std;

//random_device rd;
//mt19937 gen(rd());
//uniform_real_distribution<> dis(0.0, 1.0);

void Expr::eval() {
    return (*this)();
}

vector<double> & Expr::get_result() {
    (*this)();
    return result;
}

void Expr::operator()() {
    result.clear();
    
    if(type == Arg) {
        size_t i = 0;
        double arg = FITNESS_MIN;
        for(; i < FITNESS_POINTS; i += 1, arg += FITNESS_STEP)
            result.push_back(arg);
    }
    else if(type == Num)
        for(size_t i = 0; i < FITNESS_POINTS; i += 1)
            result.push_back(n);
    else if(type <= fun_arity_2) {
        const vector<double> & l = left->get_result();
        const vector<double> & r = right->get_result();
        switch(type) {
            case Add:
                for(auto liter = l.cbegin(), riter = r.cbegin();
                    liter != l.end() && riter != r.cend();
                    ++liter, ++riter)
                    result.push_back(*liter + *riter);
                break;
            case Sub:
                for(auto liter = l.cbegin(), riter = r.cbegin();
                    liter != l.end() && riter != r.cend();
                    ++liter, ++riter)
                    result.push_back(*liter - *riter);
                break;
            case Mul:
                for(auto liter = l.cbegin(), riter = r.cbegin();
                    liter != l.end() && riter != r.cend();
                    ++liter, ++riter)
                    result.push_back(*liter * *riter);
                break;
            case Div:
                for(auto liter = l.cbegin(), riter = r.cbegin();
                    liter != l.end() && riter != r.cend();
                    ++liter, ++riter)
                    result.push_back(*liter / *riter);
            default:;
        }
    }
    else {
        const vector<double> & l = left->get_result();
        switch(type) {
            case Sin:
                for(auto liter = l.cbegin(); liter != l.end(); ++liter)
                    result.push_back(sin(*liter));
                break;
            case Cos:
                for(auto liter = l.cbegin(); liter != l.end(); ++liter)
                    result.push_back(cos(*liter));
                break;
            case Tan:
                for(auto liter = l.cbegin(); liter != l.end(); ++liter)
                    result.push_back(tan(*liter));
            default:;
        }
    }
}

etype Expr::type_of() const {
    return type;
}

Expr::Expr(const int & depth) {
    double r1 = dis();
    result.reserve(FITNESS_POINTS);
    
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
    result.reserve(FITNESS_POINTS);
    if(e.left)
        left.reset(new Expr(*e.left));
    if(e.right)
        right.reset(new Expr(*e.right));
}

Expr::Expr(Expr && e): type(e.type_of()), n(e.get_n()) {
    result = move(e.result);
    left.swap(e.left);
    right.swap(e.right);
}

Expr & Expr::operator=(const Expr & e) {
    result.reserve(FITNESS_POINTS);
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

double Expr::calc_fitness(const vector<double> & points) {
      double result = 0;
      const double pos_inf =   numeric_limits<double>::infinity();
      const double neg_inf = -(numeric_limits<double>::infinity());
      eval();
      for(size_t x = 0; x < FITNESS_POINTS; x += 1) {
          const auto & p = points[x];
          const auto & fx = this->result[x];
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