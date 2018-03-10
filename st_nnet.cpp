#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
class Vec {

    vector <T> _data;

public:
    Vec(): _data() {};
    Vec(const vector<T> & data): _data(data) {};
    Vec(initializer_list<T> data): _data(data) {};
    
    template <typename _T>
    friend ostream & operator<<(ostream &, const Vec<_T> &);
    
    const vector<T> & get() const {
        return _data;
    };
    
    Vec & operator*=(const T & n) {
        for (auto & x: _data)
            x *= n;
        return *this;
    };
    
    Vec & operator+=(const Vec<T> & v) {
        const auto & v_data = v.get();
        if(_data.size() != v_data.size()) {
            cerr << "ERR: different dimensions\n";
            return *this;
        }
        auto this_iter = _data.begin();
        auto this_end  = _data.end();
        auto v_iter    = v.get().cbegin();
        while(this_iter != this_end) {
            *this_iter += *v_iter;
            ++this_iter;
            ++v_iter;
        }
        return *this;
    }
};

template <typename T>
ostream &operator<<(ostream &os, const Vec<T> & v) {
    os << "+-                -+\n";
    for(const auto & x: v._data)
        os << "|  " << left << showpos << setw(7) << scientific << double(x) << "  |\n";
    os << "+-                -+\n";
    return os;
}

int main() {
    Vec<double> a = {1,2,3,0};
    Vec<double> b = {1.3333, 2.11111111111, 3.2, 4.54738567835};
    a *= 10;
    b *= -3;
    cout << a << '\n' << b << '\n';
    a += b;
    cout << a << endl;
    return 0;
}
    