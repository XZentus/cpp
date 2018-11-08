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


bool is_n_prime_factors ( size_t n, const size_t & fs ) {
    size_t result = 0, last_factor = 0;
    
    for ( size_t i = 0; n > 1; ++i ) {

         if ( i >= primes.size() )
             extend_primes ( n );
         
         while ( !(n % primes[i]) ) {
             if ( primes[i] != last_factor ) {
                result += 1;
                if ( result > fs )
                    return false;
                last_factor = primes[i];
             }
             n /= primes[i];
         }
    }

    return result == fs;
}

int main () {
    
    //extend_primes( 100 );
    size_t i, n;
    
    const size_t target_factors = 3;

    for ( i = 10, n = 0; i < 100500; ++i ) {
        if ( is_n_prime_factors( i, target_factors ) )
            n += 1;
        else
            n = 0;
        if ( n == target_factors )
            break;
    }
    
    cout << i - n + 1;
    
    return 0;
}
