//#include <iostream>
#include <cstdio>

using namespace std;

#define mkfun(name, T) \
T name(const T & x) { \
    printf(#name "(%d) = %e\n", x, x * 0.0000001); \
    return x; \
}

mkfun(foo, int);
mkfun(bar, int);
mkfun(aby, int);
mkfun(wlg, int);
#undef mkfun

#define N 10

int main()
{
    int (*ptrs_base[])(const int&) = {foo, bar, aby, wlg};
    const int N_F = sizeof(ptrs_base) / sizeof(*ptrs_base);
    int (*ptrs[N])(const int&) = {};
    for(int i = 0; i < N; i += 1)
        ptrs[i] = ptrs_base[i % N_F];
    const int arg = 100500;
    auto x = &ptrs[0];
    for(int i = 0; i < N; ++i, ++x)
        (*x)(arg + i);
    return 0;
}
