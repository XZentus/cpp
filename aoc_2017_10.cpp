#include <iostream>
#include <string>

using namespace std;

const int N = 5;

void print_arr(int * array) {
    for(int i = 0; i < N; i += 1)
        cout << array[i] << ' ';
    cout << endl;
}

void task_1() {
    int array[N];
    for(int i = 0; i < N; i += 1)
        array[i] = i;
    
    int current_position = 0,
        skip_size        = 0,
        length;
    char c;
    while(cin >> length) {
        cin >> c;
        
        for(int i = 0; i < length / 2; i += 1) {
            int tmp = array[i % N];
            array[i % N] = array[(i + length) % N];
            array[(i + length) % N] = tmp;
        }
        print_arr(array);
        current_position += length + skip_size;
        skip_size += 1;
            
    }
    return;
}

int main() {
    
    task_1();
    
    return 0;
}
