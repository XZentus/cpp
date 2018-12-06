#include <iostream>
#include <ios>

#include <cstdlib>

#include <set>
#include <vector>

using namespace std;

const int digit_factorials[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

template < typename T >
T digit_factorials_sum( T n ) {
    T result = 0;
    
    while( n >= 10 ) {
        result += digit_factorials[n % 10];
        n /= 10;
    }
    
    return result + digit_factorials[n];
}

template < typename T >
T chain_length ( T n ) {
    vector< T > nums;
    nums.reserve(60);
    
    T counter = 1;
    
    while(true) {
        nums.push_back(n);
        n = digit_factorials_sum(n);
        
        auto citer = nums.begin(),
             cend  = nums.cend();
        
        for( ; citer != cend; ++citer )
            if ( *citer == n )
                return counter;
        
        counter += 1;
    }
};


int main() {
    ios::sync_with_stdio(false);
    
    int result = 0;
    
    for( int i = 1; i < 1000000; i += 1 ) {
        int tmp = chain_length(i);
        if ( tmp == 60 ) {
            cout << i << ' ';
            result += 1;
        }
    }
    cout << '\n' << result << endl;
    
    return 0;
}
