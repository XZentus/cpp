#include <iostream>

using namespace std;

const int limit = 1000001;

int main () {
/*
    for ( int i = 1; i < 1001; i += 1 )
        cout << i;
    cout << "\n\n\n";
*/    
    for ( int i = 1, step = 1, targ = 10, narg = 10, n = 1; targ < limit; i += step, n += 1 ) {
        if ( i >= targ ) {
            //cout << "   " << step << endl;
            cout << targ << '\n' << n << ' ' << i << "\n\n";
            targ *= 10;
        }
        if ( n >= narg ) {
            narg *= 10;
            step += 1;
        }
    }
    
    return 0;
}
