#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > num = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

bool is_divisible ( const vector < int > & num = num ) {
    size_t n;
    int i;
    
    int divs[] = { 2, 3, 5, 7, 11, 13, 17 };
    
    for ( n = 1, i = 0; n < 8; n += 1, i += 1 )
        if ( (num[n]*100 + num[n+1]*10 + num[n+2]) % divs[i] != 0 )
            return false;
    return true;
}

size_t get_num ( const vector < int > & num = num ) {
    size_t p = 1000000000, result = 0;
    for ( size_t i = 0; i < 10; i += 1, p /= 10 )
        result += num[i] * p;
    
    return result;
}

int main () {
    size_t result = 0;
    do {
        if ( is_divisible() ) {
            size_t tmp = get_num();
            result += tmp;
            cout << tmp << '\n';
        }
    } while ( next_permutation(num.begin(), num.end()) ) ;
    
    cout << "\n\n" << result;
    return 0;
}
