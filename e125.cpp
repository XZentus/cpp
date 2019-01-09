#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const size_t LIMIT = 100000000;

size_t number_of_values = 0;

template<typename T>
vector<T> values;

template<typename T>
bool is_pal(T n){
    T reversed = 0;
    T k = n;
 
    while (k > 0) {
        reversed = 10 * reversed + k % 10;
        k /= 10;
    }
    return n == reversed;
}

template<typename T>
void solve() {
    number_of_values = 0;
    
    T result = 0, i = 1, j, current_sum = 1;
    
    do {
        current_sum = i * i;
        if(current_sum >= LIMIT)
            break;
        j = i + 1;
        do {
            current_sum += j * j;
            if(current_sum >= LIMIT)
                break;
            if(is_pal(current_sum) && find(begin(values<T>), end(values<T>), current_sum) == end(values<T>)) {
                cout << i << " .. " << j << " -> " << current_sum << '\n';
                number_of_values += 1;
                result += current_sum;
                values<T>.push_back(current_sum);
            }
            j += 1;
        } while(true);
        i += 1;
    } while(true);
    
    cout << "Number of values: " << number_of_values << "\nSum = " << result << '\n';
    values<T>.clear();
}

int main() {
       
    solve<unsigned>();

    return 0;
}
