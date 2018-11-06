#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

size_t pent_number ( size_t n ) {
    return n * (3*n - 1) / 2;
}

vector < size_t > pents( 1, 0 );


void fill_pents_until ( size_t limit ) {
    size_t i = 0, next;
    do {
        next = pent_number ( ++i );
        pents.push_back ( next );
    } while ( next <= limit );
}

void find_min_diff ( size_t limit, size_t & p1, size_t & p2 ) {
    auto i1 = pents.cbegin(), i2 = i1 + 1;
    size_t diff = limit + 100500, dplus, dmin;
    
    for ( ; i1 != pents.cend(); ++i1 ) {
        for ( i2 = i1 + 1; i2 != pents.cend(); ++i2 ) {
            dmin = *i2 - *i1;
            if ( dmin > limit )
                continue;
            
            dplus = *i2 + *i1;
            if ( dplus  > limit )
                goto next_i1;
            
            if ( find( i2 + 1, pents.cend(), dplus ) != pents.cend() &&
                 find( pents.cbegin(), i2, dmin ) != i2 ) {
                cout << *i2 << " + " << *i1 << " = " << dplus << '\n';
                cout << *i2 << " - " << *i1 << " = " << dmin << '\n';
                if ( dplus < diff ) {
                    diff = dplus;
                    p1 = *i1;
                    p2 = *i2;
                }
            }
        }
next_i1:
        continue;
    }
    
}

int main ()
{
    
    // fill_pents_until ( 1500302515251 ); 
    fill_pents_until ( 10000500 ); 

    size_t p1 = 0, p2 = 0;
    
    find_min_diff ( 10000500, p1, p2 );
    
    cout << "\n\n" << p1 << ' ' << p2 << ": d = " << p2 - p1 << endl;
    
    return 0;
}
