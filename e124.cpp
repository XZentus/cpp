#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class Rad_solver {
    vector<T> primes;
public:
    
    void extend_primes_sqrt(const T & lim) {
        if(primes.back() * primes.back() >= lim)
            return;
        for(T i = primes.back() + 2; i * i <= lim; i += 2)
            if(is_prime(i))
                primes.push_back(i);
    }
    
    Rad_solver(const T & n = 10) {
        primes.push_back(2);
        primes.push_back(3);
        primes.push_back(5);
        primes.push_back(7);
        extend_primes_sqrt(n + 1000);
    };
    
    bool is_prime(const T & n) {
        if(primes.back() * primes.back() < n)
            extend_primes_sqrt(n + 1000);
        
        for(const auto & p: primes) {
            if(p * p > n)
                return true;
            else if (n % p == 0)
                break;
        }
        return false;
    }
    
    T rad(T n) {
        if(primes.back() * primes.back() < n)
            extend_primes_sqrt(n + 1000);
        T result = 1;
        
        for(const auto & p: primes) {
            if(n == 1 || p * p > n)
                break;
            if(n % p == 0) {
                result *= p;
                while(n % p == 0)
                    n /= p;
            }
        }

        return result * n;
    }
};

int main() {
    const unsigned limit = 100000;
    
    Rad_solver r(limit);
    
    vector<pair<unsigned, unsigned>> db;
    db.reserve(limit);
    for(unsigned i = 1; i <= limit; i += 1)
        db.emplace_back(i, r.rad(i));
    
    sort(db.begin(), db.end(), [](const auto & a, const auto & b) {
        if(a.second == b.second)
            return a.first < b.first;
        return a.second < b.second; });
    
    cout << db[10000 - 1].first << endl;
    
    return 0;
}
