#include <iostream>

using namespace std;

bool is_pandig ( int n, int & result ) {
    int pnd = 0, tmp = n, t2 = 0, filled = 0, mult = 1, p = 1;
    int numbers[10] = { 0 };
    while ( filled < 9 && pnd <= 987654321 ) {
        tmp = n * mult;
        mult += 1;
        
        p = 1; t2 = 0;
        while ( tmp > 0 ) {
            int d = tmp % 10;
            if ( d == 0 || numbers[d] > 0 )
                return false;
            numbers[d] += 1;
            pnd = pnd * 10;
            t2 += d * p;
            p *= 10;
            filled += 1;
            tmp /= 10;
        }
        pnd += t2;
    }
    if ( pnd >= 123456789 && pnd <= 987654321 ) {
        result = pnd;
        return true;
    }
    return false;
}

int main () {
    int tmp, max_pand = 0;
    
    for ( int i = 10; i < 10000; i += 1 ) {
        if ( is_pandig(i, tmp) ) {
            cout << i << " => " << tmp << '\n';
            if ( tmp > max_pand )
                max_pand = tmp;
        }
    }
    
    cout << '\n' << max_pand << '\n';
    
    return 0;
}
