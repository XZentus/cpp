#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Pos {
    int x;
    int y;
    Pos(const int _x = 0, const int _y = 0): x(_x), y(_y) {};
};

struct PosCmp {
    bool operator()(const Pos & l, const Pos & r) {
        if(l.x == r.x)
            return l.y < r.y;
        return l.x < r.x;
    }
};

// 0
//3 1
// 2
enum dir {N = 0, E, S, W};

void change_dir(const char & c, dir & dr) {
    int ch_dir = (c == 'R') ? 1 : -1, d = int(dr);
    if (ch_dir < 0 && d == 0)
        dr = W;
    else
        dr = dir((d + ch_dir) % 4);
}

set<Pos, PosCmp> db;

int make_turn(int mag, dir d, Pos & p) {
    while(mag > 0) {
        mag -= 1;
        switch(d) {
            case N:
                p.y += 1;
                break;
            case E:
                p.x += 1;
                break;
            case S:
                p.y -= 1;
                break;
            case W:
                p.x -= 1;
        }
        auto elem = db.find(p);
        if(elem != db.end())
            return(abs(p.x) + abs(p.y));
        db.emplace(p);
    }
    return 0;
}

int main()
{
    dir d = N;
    int accum = 0, result = 0;
    Pos p;
    string input;
    getline(cin, input);
    db.emplace(0, 0);
    for (const auto & c: input) {
        if (c == 'L' || c == 'R')
            change_dir(c, d);
        else if (c >= '0' && c <= '9')
            accum = accum * 10 + c - '0';
        else if (c == ',') {
            result = make_turn(accum, d, p);
            if(result)
                break;
            accum = 0;
        }
    }
    if(!result)
        result = make_turn(accum, d, p);
    cout << result << endl;
}
