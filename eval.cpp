#include <iostream>

struct expr {
    virtual double operator()(double) = 0;
};

struct const_value : public expr {
    double _value;
    const_value (double value = 0): _value(value) {};
    double operator()(double) { return _value; };
};

struct argument : public expr {
    double operator()(double x = 0) { return x; };
};

#define make_bin_op(_op_name, _op) struct _op_name : public expr {         \
    expr _left;                                                            \
    expr _right;                                                           \
    _op_name(expr left, expr right): _left(left), _right(right) {};        \
    double operator()(double arg) { return _left(arg) _op _right(arg); };  \
}

make_bin_op(add,  +);
make_bin_op(sub,  -);
make_bin_op(prod, *);
make_bin_op(div,  /);

#undef make_bin_op

#define make_unary_op(_op_name, _op)  struct _op_name : public expr {      \
    expr _expr;                                                           \
    _op_name(expr val): _expr(val) {};        \
    double operator()(double arg) { return _expr(arg) ; };  \
}

int main()
{
    std::cout << "Hello, world!\n";
}
