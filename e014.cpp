#include <vector>

#include <algorithm>

#include <iostream>

using namespace std;

size_t DB_SIZE = 1000;

vector<int> db;

template<typename T>
T collatz_next(const T & n) {
    if(n % T(2) == 0)
        return n / 2;
    return 3 * n + 1;
}

template<typename T>
T collatz_len(const T & n) {
    if(n < DB_SIZE)
        return db[n];
    return 1 + collatz_len(collatz_next(n));
}

template <typename T>
T collatz_len_fill(const T & n) {
    if(n < DB_SIZE) {
        if(db[n])
            return db[n];
        T result = 1 + collatz_len_fill(collatz_next(n));
        db[n] = result;
        return result;
    }
    return 1 + collatz_len_fill(collatz_next(n));
}

template <typename T>
void print_collatz(T n) {
    while(n != T(1)) {
        cout << n << " -> ";
        n = collatz_next(n);
    }
    cout << "1\n";
}

void init_db() {
    db.resize(DB_SIZE);
    
    fill(db.begin(), db.end(), 0);
    
    db[1] = 1;
    db[2] = 2;
    db[4] = 3;
    db[8] = 4;
    
    for(size_t i = 3; i < DB_SIZE; i += 1)
        collatz_len_fill(i);
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    
    size_t limit = 1000000;
    
    if(argc > 1)
        limit = atoi(argv[1]);
    if(argc > 2)
        DB_SIZE = atoi(argv[2]);
    
    init_db();
    
    size_t maxi = 0, maxlen = 0;

    for(size_t i = 3; i < limit; i += 1) {
        size_t c_len = collatz_len(i);
        if(c_len > maxlen) {
            maxi = i;
            maxlen = c_len;
        }
    }
    
    cout << maxi << " -> " << maxlen << '\n';
    print_collatz(maxi);
    
    // cout << collatz_len(837799);
    // print_collatz<size_t>(837799);
    
    return 0;
}
