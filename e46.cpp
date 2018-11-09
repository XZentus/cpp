#include <iostream>
#include <vector>

using namespace std;

vector < size_t > primes = { 2, 3, 5, 7, 11, 13, 17, 19 };

void extend_primes ( size_t n ) {
    size_t next = primes.back();
    
start:
    
    next += 2;
    
    for ( const auto & p: primes ) {
        if ( !(next % p) )
            goto start;
        if ( (next / p) < p )
            break;
    }
    
    primes.push_back( next );
    
    if ( next < n )
        goto start;
    
    return;
}

const size_t limit = 10000;

vector < bool > sieve( limit, false );

int main () {
    extend_primes( limit );
    
    for ( const auto & p: primes ) {
        for ( size_t a = 1; p + 2 * a * a < limit ; a += 1 ) {            
            size_t next = p + 2 * a * a;
            if ( next >= limit )
                break;
            sieve[next] = true;
        }
    }
    
    auto e = primes.cbegin();
    
    for ( size_t i = 9; i < limit; i += 2 ) {
        for ( ; (e != primes.cend()) && (*e < i); ++e );
        if ( (*e != i) && (!sieve[i]) ) {
            cout << i;
            break;
        }
    }
    
    return 0;
}
