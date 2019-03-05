#include <iostream>

using namespace std;

typedef unsigned long long int_;

const int_ from = 1, to = 100500;

const int_ diff_limit = 10000000;

void solve1(int_ from, int_ to) {
    if(to - from > diff_limit) {
        cout << "solve1: too big interval\n";
        return;
    }
    
    int_ result = 0;
    while(from <= to) {
        if(from % 5 == 0 || from % 3 == 0) {
            result += from;
            if(result < from) {
                cout << "solve1: overflow\n";
                return;
            }
        }
        ++from;
    }
    cout << "solve1() = " << result << endl;
}

int_ next_div(int_ value, int_ div) {
    if(value % div == 0)
        return value;
    
    return value + div - value % div;
}

int_ prev_div(int_ value, int_ div) {
    if(value % div == 0)
        return value;
    
    return value - value % div;
}

int_ sum_range(int_ from,int_ to, int_ div) {
    from = next_div(from, div);
    to = prev_div(to, div);
    
    int_ n_divs = 1 + (to - from) / div;
    
    if(n_divs % 2 == 0)
        return from + (n_divs - 1) * (from + div + to) / 2;
    return n_divs * (from + to) / 2;
}

void solve2(int_ from, int_ to) {
    int_ s3  = sum_range(from, to,  3),
         s5  = sum_range(from, to,  5),
         s15 = sum_range(from, to, 15);
    int_ result = s3 + s5 - s15;
    if(result < to || s3 < to || s5 < to || s15 < to)
        cout << "solve2: overflow\n";
    else
        cout << "solve2() = " << result << endl;
}

int main() {
    solve1(from, to);
    solve2(from, to);
    return 0;
}
