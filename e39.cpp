#include <iostream>

using namespace std;

int count_decisions ( int p ) {
    int result = 0;
    
    int a = 1, b = 1;
    
    for ( a = 1; a < p - 2; a += 1 ) {
        for ( b = a ; a + b < p - 1; b += 1 ) {
            
            int ab = a * a + b * b, c = p - a - b;
            
            if ( c < a || c < b )
                goto nextA;
            
            if ( ab == c * c ) {
                result += 1;
                cout << "{ " << a << ", " << b << ", " << c << " }\n";
                goto nextA;
            }
        }
nextA:
        continue;
    }
    
    return result;
}


int main () {
    int max_c = 0, max_i = 0;
    
    for ( int i = 3; i <= 1000; i += 1 ) {
        int tmp = count_decisions(i);
        if ( tmp > max_c ) {
            max_c = tmp;
            max_i = i;
        }
        cout << i << " => " << tmp << '\n';
    }
    
    cout << "\n-------------\n" << max_i << " => " << max_c << '\n';
    count_decisions(max_i);
    
    return 0;
}
