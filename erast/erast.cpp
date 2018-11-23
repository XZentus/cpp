#include <ios>
#include <iomanip>
#include <iostream>

#include <cstdlib>
#include <cstring>

using namespace std;

const size_t LIMIT        = 8007,
             BITS_IN_BYTE = 8,
             DB_SIZE      = LIMIT/BITS_IN_BYTE + 1;

unsigned char erast[DB_SIZE] = { 0 };

void drop_bit(size_t i) {
    erast[i / BITS_IN_BYTE] &= ~(0x01 << (i % BITS_IN_BYTE));
}

bool is_prime(const size_t & i) {
    return erast[i / BITS_IN_BYTE] & (0x01 << (i % BITS_IN_BYTE));
}

size_t next_prime(size_t i) {
    i += 1;
    while( !is_prime(i))
        i += 1;

    return i;
}

void init() {
    memset(erast, 0xff, DB_SIZE);
    
    for(size_t i = 4; i < LIMIT; i += 2)
        drop_bit(i);
    
    for(size_t i = 3; i * i < LIMIT; i = next_prime(i))
        for(size_t n = i * i; n < LIMIT; n += i)
            drop_bit(n);
}

void print_erast_bits() {
    for(size_t i = 0; i < LIMIT; i += 1)
        cout << is_prime(i);
    cout << endl;
}

void print_erast_hex_simple(const size_t & row_len = 16, size_t row_offset = 4) {
    string newstr = "\n";
    while ( row_offset-- )
        newstr += ' ';

    cout << '{' << newstr;

    cout << hex << uppercase << setfill('0');
    for(size_t i = 0; i < DB_SIZE - 1; i += 1) {
        cout << "0x" << setw(2) << (erast[i] & 0xff) << ", ";
        if ( (i % row_len) == (row_len - 1) )
            cout << newstr;
    }
    cout << "0x" << (erast[DB_SIZE - 1] & 0xff);
    
    cout << dec << nouppercase << setfill(' ');
    cout << "\n}";
}

void print_erast_dec_simple(const size_t & row_len = 16, size_t row_offset = 4) {
    string newstr = "\n";
    while ( row_offset-- )
        newstr += ' ';

    cout << '{' << newstr;
    for(size_t i = 0; i < DB_SIZE - 1; i += 1) {
        cout << setw(3) << (erast[i] & 0xff) << ", ";
        if ( (i % row_len) == (row_len - 1) )
            cout << newstr;
    }
    cout << setw(3) << (erast[DB_SIZE - 1] & 0xff);
    
    cout << "\n}";
}

void print_primes() {
    for(size_t i = 2; i < LIMIT; i = next_prime(i))
        if(is_prime(i))
            cout << i << ' ';
}

int main()
{
    cout << "DB_SIZE = " << DB_SIZE << '\n'
         << "LIMIT   = " << LIMIT << '\n';
    init();
    
    print_erast_hex_simple(16);
    
    cout << "\n\n";
    
    print_erast_dec_simple(16);
    
    cout << "\n\n";
    /*
    for(size_t i = 2; i < LIMIT; i = next_prime(i))
        if(is_prime(i))
            cout << i << ' ';
    */
    return 0;
}
