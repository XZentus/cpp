#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

const size_t N = 256;

void print_arr(unsigned char const * const array) {
    for(size_t i = 0; i < N; i += 1)
        cout << array[i] << ' ';
    cout << endl;
}

void task_1() {
    unsigned char array[N];
    for(size_t i = 0; i < N; i += 1)
        array[i] = i;
    
    size_t current_position = 0,
           skip_size        = 0,
           length;
    char c;
    while(cin >> length) {
        cin >> c;
        
        for(size_t i = 0; i < length / 2; i += 1) {
            unsigned char tmp = array[(current_position + i) % N];
            array[(current_position + i) % N] = array[(current_position + length - 1 - i) % N];
            array[(current_position + length - 1 - i) % N] = tmp;
        }
        print_arr(array);
        current_position += (length + skip_size) % N;
        skip_size += 1;
            
    }
    cout << array[0] * array[1] << endl;
    return;
}

void fill_codes(vector<unsigned char> & codes) {
    char c;
    vector<unsigned char> end = {17, 31, 73, 47, 23};
    while(cin >> c)
        codes.push_back(c);
    for(const auto & x: end)
        codes.push_back(x);
}

void encrypt_round(const vector<unsigned char> & codes, unsigned char array[],
                   size_t & current_position, size_t & skip_size) {
    for(const auto & length: codes) {
        for(size_t i = 0; i < length / 2; i += 1) {
            unsigned char tmp = array[(current_position + i) % N];
            array[(current_position + i) % N] = array[(current_position + length - 1 - i) % N];
            array[(current_position + length - 1 - i) % N] = tmp;
        }
        current_position += (length + skip_size) % N;
        skip_size += 1;
    }
}

void task_2() {
    unsigned char array[N];
    
    vector<unsigned char> codes;
    
    for(size_t i = 0; i < N; i += 1)
        array[i] = (unsigned char)i;
    
    fill_codes(codes);

    size_t current_position = 0,
           skip_size        = 0;
    
    for(size_t i = 0; i < 64; ++i)
        encrypt_round(codes, array, current_position, skip_size);
    
    for(size_t offset = 0; offset < 16; offset += 1) {
        char symbol = 0;
        for(size_t i = 0; i < 16; i += 1)
            symbol ^= array[i + offset * 16];
        printf("%02x", (unsigned char)symbol);
//        cout << hex << (unsigned char)symbol << ' ';
    }
           
    return;
}

int main() {
    
    task_2();
    
    return 0;
}
