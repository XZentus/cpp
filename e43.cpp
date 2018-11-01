#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

size_t limit = 0;

vector < int > num = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

bool is_divisible ( const vector < int > & num = num ) {
    size_t n;
    int i;
    
    int divs[] = { 2, 3, 5, 7, 11, 13, 17 };
    
    for ( n = 1, i = 0; n < limit - 2; n += 1, i += 1 )
        if ( (num[n]*100 + num[n+1]*10 + num[n+2]) % divs[i] != 0 )
            return false;
    return true;
}

size_t get_num ( const vector < int > & num = num ) {
    size_t p = pow(10, limit - 1), result = 0;
    for ( size_t i = 0; i < limit; i += 1, p /= 10 )
        result += num[i] * p;
    
    return result;
}

int main () {
    size_t result = 0;
    cin >> limit;
    limit += 1;
    do {
        if ( is_divisible() )
            result += get_num();
    } while ( next_permutation(num.begin(), num.begin() + limit) ) ;
    
    cout << result;
    return 0;
}
