#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

vector<size_t> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

bool is_prime(size_t n) {
    for ( const auto & e: primes ) {
        if ( (e * e) > n )
            return true;
        if ( !(n % e) )
            return false;
    }
    return true;
}

void extend_primes( size_t limit ) {
    size_t new_p = primes.back();
start:
    new_p += 2;
    while ( !is_prime(new_p) )
        new_p += 2;
    primes.push_back( new_p );
    if ( new_p < limit )
        goto start;
    return;
}

bool is_circular_prime(size_t n) {
    int perms = log10(n), i = perms, pw = (int)pow(10, perms);
    do {
        if ( !binary_search(primes.cbegin(), primes.cend(), n) )
            return false;
        n = (n % pw) * 10 + (n / pw);
    } while (i--);
    return true;
}

int main()
{
    extend_primes(1000000);
    size_t result = 13;
    
    for ( const auto & e: primes ) {
        if ( e < 100 )
            continue;
        if ( is_circular_prime(e) ) {
            result += 1;
            cout << e << ' ';
        }
    }
    cout << endl << result;
    
    return 0;
}
