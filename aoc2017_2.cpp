#include <iostream>
#include <map>

using namespace std;

/*
directions
  1
  ^
2< >0
  v
  3

coords
2|
1|
0|
Y+---
 X012
*/

struct Pos {
    int x, y;
    Pos (const int & _x = 0, const int & _y = 0): x(_x), y(_y) {};
};

struct PosCmp {
    bool operator()(const Pos & l, const Pos & r) {
        if(l.x == r.x)
            return l.y < r.y;
        return l.x < r.x;
    }
};

struct Env {
    int length, pos_id;
    Pos p;
    Env(): length(2), pos_id(3), p(1,1) {};
    int len_from_id(const int & id) {
        if (id == 1)
            return 0;
        else if (id == 2)
            return 1;
            
        while(pos_id < id) {
        // <
            if(pos_id + length <= id) {
                p.x -= length;
                pos_id += length;
                if(pos_id == id)
                    goto end;
            }
            else {
                p.x -= id - pos_id;
                pos_id += id - pos_id;
            }
        // v
            if(pos_id + length <= id) {
                p.y -= length;
                pos_id += length;
                if(pos_id == id)
                    goto end;
            }
            else {
                p.y -= id - pos_id;
                pos_id += id - pos_id;
            }
            length += 1;
        // >
            if(pos_id + length <= id) {
                p.x += length;
                pos_id += length;
                if(pos_id == id)
                    goto end;
            }
            else {
                p.x += id - pos_id;
                pos_id += id - pos_id;
            }
        // ^
            if(pos_id + length <= id) {
                p.y += length;
                pos_id += length;
                if(pos_id == id)
                    goto end;
            }
            else {
                p.y += id - pos_id;
                pos_id += id - pos_id;
            }
            length += 1;
        }
        end:
        cout << "x = " << p.x << " y = " << p.y << " id = " << pos_id << endl;
        return (abs(p.x) + abs(p.y));
    }
};


struct Env2 {
    int length;
    Pos p;
    map<Pos, int, PosCmp> id_db;
    Env2(): length(2), p(1,1) {
        id_db.emplace(Pos(),    1);
        id_db.emplace(Pos(1),   1);
        id_db.emplace(Pos(1,1), 2);
    };
    int neib_sum(const int & dx, const int & dy) {
        auto iter = id_db.find(Pos(p.x + dx, p.y + dy));
        if(iter != id_db.end())
            return (*iter).second;
        return 0;
    }
    int all_neighbors_sum() {
        return neib_sum( 1,  1)
             + neib_sum( 1,  0)
             + neib_sum( 1, -1)
             + neib_sum( 0, -1)
             + neib_sum( 0,  1)
             + neib_sum(-1, -1)
             + neib_sum(-1,  0)
             + neib_sum(-1,  1);
    }
    int nex_id(const int & id) {
        if (id == 0)
            return 1;
        else if (id == 1)
            return 2;
        int len, last_sum = 0;
        while(last_sum <= id) {
        // <
            len = length;
            while(len--) {
                p.x -= 1;
                last_sum = all_neighbors_sum();
                id_db[p] = last_sum;
                if(last_sum > id)
                    return last_sum;
            }
        // v
            len = length;
            while(len--) {
                p.y -= 1;
                last_sum = all_neighbors_sum();
                id_db[p] = last_sum;
                if(last_sum > id)
                    return last_sum;
            }
            length += 1;
        // >
            len = length;
            while(len--) {
                p.x += 1;
                last_sum = all_neighbors_sum();
                id_db[p] = last_sum;
                if(last_sum > id)
                    return last_sum;
            }
        // ^
            len = length;
            while(len--) {
                p.y += 1;
                last_sum = all_neighbors_sum();
                id_db[p] = last_sum;
                if(last_sum > id)
                    return last_sum;
            }
            length += 1;
        }
        cout << "x = " << p.x << " y = " << p.y << endl;
        return (abs(p.x) + abs(p.y));
    }
};

int main()
{
    Env2 e;
    int target;
    cin >> target;
    cout << e.nex_id(target);
    return 0;
}
