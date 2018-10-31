#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

size_t limit = 10000000;

vector < bool > is_prime ( limit, true );

bool is_trunc_left ( size_t n ) {
    while ( n > 10 ) {
        if ( !is_prime[n] )
            return false;
        n = n % (size_t)(pow(10, (int)log10(n)));
    }
    return is_prime[n];
}

bool is_trunc_right ( size_t n ) {
    while ( n > 10 ) {
        if ( !is_prime[n] )
            return false;
        n /= 10;
    }
    return is_prime[n];
}

bool is_truncable ( size_t n ) {
    return is_trunc_left(n) && is_trunc_right(n);
}

void init_primes () {
    for ( size_t step = 2; step * step < limit; step += 1 )
        for ( size_t i = step * step; i < limit; i += step )
            is_prime[i] = false;
}

int main() {
    init_primes();
    is_prime[0] = is_prime[1] = 0;
    
    size_t result = 0;

    for ( size_t i = 9999999; i > 10; i -= 2 ) {
        if ( !is_prime[i] )
            continue;
        if ( is_truncable(i) ) {
            cout << i << '\n';
            result += i;
        }
    }
    cout << '\n' << result << '\n';

    return 0;
}
