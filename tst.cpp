#include <cstdio>

#include <iostream>

using namespace std;

struct Pos {
    int x, y;
    Pos(): x(0), y(0) {};
};

int main() {
    int s, k;
    Pos U_, UR, _R, DR, D_, DL, _L, UL, q;
    
    scanf("%d%d%d%d", &s, &k, &q.x, &q.y);
    U_.y = UR.y = UL.y = s;
    D_.y = DR.y = DL.y = 1;
    _L.x = UL.x = DL.x = 1;
    _R.x = DR.x = DR.x = s;
    
    Pos p;
    while(k--) {
        scanf("%d%d", &p.x, &p.y);
        //U
        if      (p.x == q.x && p.y >= q.y && p.y <= U_.y)
            U_.y = p.y - 1;
        //D
        else if (p.x == q.x && p.y <= q.y && p.y >= D_.y)
            D_.y = p.y + 1;
        //L
        else if (p.y == q.y && p.x <= q.x && p.x >= _L.y)
            _L.x = p.x + 1;
        //R
        else if (p.y == q.y && p.x >= q.x && p.x <= _R.y)
            _R.x = p.x - 1;
        //UL
        else if (p.y >= q.y && p.x <= q.x && p.y - q.y == q.x - p.x && p.y <= UL.y) {
            UL.x = p.x + 1;
            UL.y = p.y - 1;
        }
        //UR
        else if (p.y >= q.y && p.x >= q.x && p.y - q.y == p.x - q.x && p.y <= UR.y) {
            UR.x = p.x - 1;
            UR.y = p.y - 1;
        }
        //DL
        else if (p.y <= q.y && p.x <= q.x && q.y - p.y == q.x - p.x && p.y >= DL.y) {
            DL.x = p.x + 1;
            DL.y = p.y + 1;
        }
        //DR
        else if (p.y <= q.y && p.x >= q.x && q.y - p.y == p.x - q.x && p.y >= DR.y) {
            DR.x = p.x - 1;
            DR.y = p.y + 1;
        }
    }
    
    cout << "U_ " << U_.x << ' ' << U_.y << '\n'
         << "D_ " << D_.x << ' ' << D_.y << '\n'
         << "_R " << _R.x << ' ' << _R.y << '\n'
         << "_L " << _L.x << ' ' << _L.y << '\n'
         << "DR " << DR.x << ' ' << DR.y << '\n'
         << "UR " << UR.x << ' ' << UR.y << '\n'
         << "DL " << DL.x << ' ' << DL.y << '\n'
         << "UL " << UL.x << ' ' << UL.y << '\n' ;
        
    
    printf("%d\n", U_.y - D_.y
                 + _R.x - _L.x
                 + UR.y - DL.y
                 + UL.y - DR.y);
    

    return 0;
}
