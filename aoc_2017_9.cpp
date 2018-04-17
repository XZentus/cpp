#include <iostream>
#include <string>

using namespace std;

static int garbage_count = 0;

const char * parse_garbage(const char * str) {
    while(*str && *str != '>') {
        if(*str == '!') {
            str += 2;
            continue;
        }
        ++garbage_count;
        ++str;
    }
    return str;
}

const char * parse_group(const char * str, int & sum, int n) {
    sum += n;
    while(*str && *str != '}') {
        if(*str == '{') {
            ++str;
            str = parse_group(str, sum, n + 1);
        }
        else if(*str == '<') {
            ++str;
            str = parse_garbage(str);
        }
        ++str;
    }
    return str;
}

int main() {
    
    string input;
    cin >> input;
    garbage_count = 0;

	int sum = 0;
	parse_group(input.c_str(), sum, 0);
    
    cout << "Groups sum: " << sum << '\n' << "Garbage deleted: " << garbage_count << endl;
    
    return 0;
}
