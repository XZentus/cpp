#include <cstdio>

#include <iostream>

using namespace std;

struct Pos {
    int x, y;
    Pos(): x(1), y(1) {};
};

struct Line {
    int xmin, xmax, ymin, ymax;
};

bool pos_in_line(const Pos & p, const Line & l) {
    return    p.x >= l.xmin
           && p.x <= l.xmax 
           && p.y >= l.ymin
           && p.y <= l.ymax;
}

int get_diff_x(const Line & l) {
    return l.xmax - l.xmin + 1;
}

int get_diff_y(const Line & l) {
    return l.ymax - l.ymin + 1;
}

int main() {
    int s, k;
    Line U_, UR, _R, DR, D_, DL, _L, UL;
    Pos q;
    
    scanf("%d%d%d%d", &s, &k, &q.x, &q.y);
    U_.xmin = U_.xmax = q.x;
    U_.ymin = q.y + 1;
    U_.ymax = s;
    
    D_.xmin = D_.xmax = q.x;
    D_.ymin = 1;
    D_.ymax = q.y - 1;
    
    _R.ymin = _R.ymax = q.y;
    _R.xmin = q.x + 1;
    _R.xmax = s;
    
    _L.ymin = _L.ymax = q.y;
    _L.xmin = 1;
    _L.xmax = q.x - 1;
    
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
#define fstr(attr) printf( #attr " x [%d : %d] y [%d : %d] || x: %d y: %d\n", attr.xmin, attr.xmax, attr.ymin, attr.ymax, get_diff_x(attr), get_diff_y(attr))
    
    fstr(U_);
    fstr(D_);
    fstr(_R);
    fstr(_L);
    fstr(UL);
    fstr(UR);
    fstr(DR);
    fstr(DL);
#undef fstr
    cout << "-----------------------------------------\n";
    Pos p;
    while(k--) {
        scanf("%d%d", &p.x, &p.y);
        //U
        if      (pos_in_line(p, U_))
            U_.ymax = p.y - 1;
        //D
        else if (pos_in_line(p, D_))
            D_.ymin = p.y + 1;
        //L
        else if (pos_in_line(p, _L))
            _L.xmin = p.x + 1;
        //R
        else if (pos_in_line(p, _R))
            _R.xmax = p.x - 1;
        //UL
        else if (pos_in_line(p, UL)) {
            UL.xmin = p.x + 1;
            UL.ymax = p.y - 1;
        }
        //UR
        else if (pos_in_line(p, UR)) {
            UR.xmax = p.x - 1;
            UR.ymax = p.y - 1;
        }
        //DL
        else if (pos_in_line(p, DL)) {
            DL.xmin = p.x + 1;
            DL.ymin = p.y + 1;
        }
        //DR
        else if (pos_in_line(p, DR)) {
            DR.xmax = p.x - 1;
            DR.ymin = p.y + 1;
        }
    }
#define fstr(attr) printf( #attr " x [%d : %d] y [%d : %d] || x: %d y: %d\n", attr.xmin, attr.xmax, attr.ymin, attr.ymax, get_diff_x(attr), get_diff_y(attr))
    
    fstr(U_);
    fstr(D_);
    fstr(_R);
    fstr(_L);
    fstr(UL);
    fstr(UR);
    fstr(DR);
    fstr(DL);
#undef fstr

    int u = get_diff_y(U_),
        d = get_diff_y(D_),
        l = get_diff_x(_L),
        r = get_diff_x(_R),
        ul = get_diff_y(UL),
        ur = get_diff_y(UR),
        dl = get_diff_y(DL),
        dr = get_diff_y(DR);
#define ps(i) ((i > 0) ? i : 0)
    printf("%d\n", ps(u) + ps(d) + ps(l) + ps(r) + ps(ul) + ps(ur) + ps(dl) + ps(dr));
#undef ps
    return 0;
}
