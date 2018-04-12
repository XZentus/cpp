#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Keypad {
/*X 1 2 3
Y + -----
1 | 1 2 3
2 | 4 5 6
3 | 7 8 9
*/
    int x;
    int y;
    Keypad (const int & _x = 2, const int & _y = 2): x(_x), y(_y) {};
    int get_key() {
        return x + (y - 1) * 3;
    }
    void make_step(const char & c) {
        switch(c) {
            case 'U':
                y -= 1;
                break;
            case 'D':
                y += 1;
                break;
            case 'L':
                x -= 1;
                break;
            case 'R':
                x += 1;
        }
        correct_pos();
    }
    
    void correct_pos() {
        x = max(x, 1);
        x = min(x, 3);
        y = max(y, 1);
        y = min(y, 3);
    }
    void rewind() {
        x = 2;
        y = 2;
    }
};


/*
    1
  2 3 4
5 6 7 8 9
  A B C
    D
*/

static vector<vector<int>> moves {
    {},
        /*  1 */ { 1, 1, 3, 1 },
        /*  2 */ { 2, 3, 6, 2 },
        /*  3 */ { 1, 4, 7, 2 },
        /*  4 */ { 4, 4, 8, 3 },
        /*  5 */ { 5, 6, 5, 5 },
        /*  6 */ { 2, 7,10, 5 },
        /*  7 */ { 3, 8,11, 6 },
        /*  8 */ { 4, 9,12, 7 },
        /*  9 */ { 9, 9, 9, 8 },
        /*  A */ { 6,11,10,10 },
        /*  B */ { 7,12,13,10 },
        /*  C */ { 8,12,12,11 },
        /*  D */ {11,13,13,13 },
};

/*
directions:
 0
3 1
 2
*/
int dir2int(const char & c) {
    int ret = 0;
    switch(c){
        case 'R':
            ret = 1;
            break;
        case 'D':
            ret = 2;
            break;
        case 'L':
            ret = 3;
    }
    return ret;
}

struct Keypad2 {
    int key;
    Keypad2(const int & k = 5): key(k) {};
    void make_step(const char & c) {
        key = moves[key][dir2int(c)];
    }
    char get_key() {
        if(key < 10)
            return key + '0';
        return key - 10 + 'A';
    }
};

int main()
{
    string result, input;
    Keypad2 k;
    while(getline(cin, input) && input.length()) {
        for(const char & c : input)
            if(c == 'U' || c == 'D' || c == 'R' || c == 'L')
                k.make_step(c);
        result += k.get_key();
    }
    cout << result << endl;
}
