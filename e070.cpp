#include <iostream>

#include <vector>

using namespace std;

const size_t LIMIT = 10000000;

vector<size_t> primes;

bool is_permut(size_t a, size_t b) {
    int map[10] = {0};
    while(a) {
        map[a % 10] += 1;
        a /= 10;
    }
    
    while(b) {
        map[b % 10] -= 1;
        b /= 10;
    }
    
    for(size_t i = 0; i < 10; i += 1)
        if(map[i])
            return false;
    return true;
}

bool is_prime(size_t n) {
    for(const auto & p: primes) {
        if(p * p > n)
            break;
        else if(n % p == 0)
            return false;
    }
    return true;
}

size_t solve_2primes() {
    size_t init[] = {2, 3, 5, 7, 11, 13};
    for(size_t i = 0; i < sizeof(init)/sizeof(size_t); i += 1)
        primes.push_back(init[i]);
    
    size_t next = primes.back();
    while(next * next / 1.5 < LIMIT) {
        if(is_prime(next))
            primes.push_back(next);
        next += 2;
    }
    
    double nphin = 100500;
    size_t res = 0, lim = primes.size();
    
    for(size_t i = 0; i < lim; i += 1) {
        size_t a = primes[i];
        double ad = a;
        
        for(size_t j = 0; j < lim; j += 1) {
            size_t b = primes[j];
            double bd = b;
            size_t n = a * b;
            if(n > LIMIT)
                continue;
            
            double phin = n * (1.0 - 1.0/ad) * (1.0 - 1.0/bd);
            if(!is_permut(static_cast<size_t>(phin), n))
                continue;
            
            double nph = static_cast<double>(n) / phin;
            
            if(nph < nphin) {
                nphin = nph;
                res = n;
            }
        }
    }
    
    cout << res << '\n';
    
    return res;
}

int main() {
    solve_2primes();
    
    return 0;
}
