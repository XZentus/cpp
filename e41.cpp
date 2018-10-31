#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

size_t limit  =  10000000;
string pandig = "7654321";

vector < bool > is_prime ( limit, true );

size_t next_step ( size_t step ) {
    step += 2;
    while (!is_prime[step])
        step += 2;
    return step;
}

void init_primes () {
    for ( size_t i = 2 * 2; i < limit; i += 2 )
        is_prime[i] = false;

    for ( size_t step = 3; step * step < limit; step = next_step(step) )
        for ( size_t i = step * step; i < limit; i += step )
            is_prime[i] = false;
    cout << "init() finished" << endl;
}

int read_pandig() {
    int p = limit / 10, i = 0, result = 0;
    while ( i < pandig.size() ) {
        result += (pandig[i] - '0') * p;
        p /= 10;
        i += 1;
    }
    return result;
}

int main () {

    init_primes();

    is_prime[0] = is_prime[1] = 0;
    if ( is_prime[read_pandig()] ) {
        cout << pandig << endl;
        return 0;
    }
    
    while ( next_permutation(pandig.begin(), pandig.end(), [](char a, char b){ return a > b; }) ) {
        if ( is_prime[read_pandig()] ) {
            cout << pandig << endl;
            break;
        }
    }
    
    return 0;
}
