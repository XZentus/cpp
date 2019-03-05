#include <iostream>

using namespace std;

typedef unsigned long long int_;

int_ solve_gen(int_ limit) {
    int_ a = 1, b = 2, result = 0;
    while(b < limit) {
        if(a % 2 == 0)
            result += a;
        if(b % 2 == 0)
            result += b;
        a += b;
        b += a;
    }
    return result;
}

void solve() {
    cout << solve_gen(4000000) << endl;
}

int main() {
    solve();
    return 0;
}
    