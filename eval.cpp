#include <iostream>
#include <cmath>

using namespace std;

struct expr {
    virtual double operator()(double) {
        cerr << "EXPR::operator() called\n";
        return 100500;
    };
};

struct const_value : public expr {
    double _value;
    const_value (double value = 0): _value(value) {};
    double operator()(double arg = 0) override {
        cout << "const_value " << _value << " called arg = " << arg << '\n';
        return _value;
    };
};

#define make_bin_op(_op_name, _op) struct e_##_op_name : public expr {     \
    expr _left;                                                            \
    expr _right;                                                           \
    e_##_op_name(expr left, expr right): _left(left), _right(right) {};    \
    double operator()(double arg) override {                               \
        return _left(arg) _op _right(arg);                                 \
    };                                                                     \
}

make_bin_op(add,  +);
make_bin_op(sub,  -);
make_bin_op(prod, *);
make_bin_op(div,  /);

#undef make_bin_op

#define make_unary_op(_op)  struct e_##_op : public expr {                 \
    expr _expr;                                                            \
    e_##_op(expr val): _expr(val) {};                                      \
    double operator()(double arg) override {                               \
        cout << #_op " called arg = " << arg << '\n';                      \
        return _op(_expr(arg)) ; };                                        \
}

make_unary_op(sin);
make_unary_op(cos);

#undef make_unary_op

int main()
{
    const_value c1{1};
    e_add e{c1, c1};
    
    cout << e(100) << endl;
    cout << c1(100) << endl;
    
    return 0;
}
