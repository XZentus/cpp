#include <cstdio>

#include <iostream>

using namespace std;

struct Pos {
    int x, y;
    Pos(): x(1), y(1) {};
};

struct Line {
    int xmin, xmax, ymin, ymax;
}

bool pos_in_line(const Pos & p, const Line & l) {
    return    l.x >= p.xmin
           && l.x <= p.xmax 
           && l.y >= p.ymin
           && l.y <= p.ymax;
}

int main() {
    int s, k;
    Line U_, UR, _R, DR, D_, DL, _L, UL;
    Pos q;
    
    scanf("%d%d%d%d", &s, &k, &q.x, &q.y);
    U_.xmin = U_.xmax = D_.xmin = D_xmax = q.x;
    U_.ymin = q.y + 1;
    U_.xmax = s;
    D_.ymin = 1;
    D_.ymax = q - 1;
    
    int diff = abs(q.x - q.y);
    int s2 = s / 2;
    
    UR.xmin = q.x + 1;
    UR.xmax = (q.y > s2) ? (s - diff) : s;
    UR.ymin = q.y + 1;
    UR.ymax = (q.x > s2) ? (s - diff) : s;
    
    UL.xmin = (q.y > s2) ? diff : 1;
    UL.xmax = q.x - 1;
    UL.ymin = q.y + 1;
    UL.ymax = (q.x < s2) ? (s - diff) : s;
    
    DL.xmin = (q.y < s2) ? diff : 1;
    DL.xmax = q.x - 1;
    DL.ymin = (q.x < s2) ? diff : 1;
    DL.ymax = q.y - 1;
    
    DR.xmin = q.x + 1;
    DR.xmax = (q.y < s2) ? (s - diff) : s;
    DR.ymin = (q.x > s2) ? diff : 1;
    DR.ymax = q.y - 1;
//----------------------------------------------------------------
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
/*    
    cout << "U_ " << U_.x << ' ' << U_.y << '\n'
         << "D_ " << D_.x << ' ' << D_.y << '\n'
         << "_R " << _R.x << ' ' << _R.y << '\n'
         << "_L " << _L.x << ' ' << _L.y << '\n'
         << "DR " << DR.x << ' ' << DR.y << '\n'
         << "UR " << UR.x << ' ' << UR.y << '\n'
         << "DL " << DL.x << ' ' << DL.y << '\n'
         << "UL " << UL.x << ' ' << UL.y << '\n' ;
*/        
    
    printf("%d\n", U_.y - D_.y
                 + _R.x - _L.x
                 + UR.y - DL.y
                 + UL.y - DR.y);
    

    return 0;
}
