#include <iostream>
#include <set>

using namespace std;

const int N_BANKS = 16;

struct HDD {
    unsigned char bank[N_BANKS + 1];
    
    size_t get_max_bank_id() const {
        size_t id = 0, s = 0;
        for (int i = 0; i < N_BANKS; i += 1)
            if (s < bank[i]) {
                s = bank[i];
                id = i;
            }
        return id;
    }
    
    void defrag_iter() {
        size_t id = get_max_bank_id();
        unsigned char blocks = bank[id];
        bank[id] = 0;
        id = (id + 1) % N_BANKS;
        for(; blocks; id = (id + 1) % N_BANKS){
            blocks -= 1;
            bank[id] += 1;
        }
    }
    int id;
};

bool operator<(const HDD & l, const HDD & r) {
    for (int i = 0; i < N_BANKS - 1; i += 1)
        if(l.bank[i] != r.bank[i])
            return l.bank[i] < r.bank[i];
    return l.bank[N_BANKS - 1] < r.bank[N_BANKS - 1];
}

int task_1() {
    HDD hdd;
    for(int i = 0; i < N_BANKS; i += 1) {
        int tmp; cin >> tmp;
        hdd.bank[i] = static_cast<unsigned char>(tmp);
    }
    
    set<HDD> db;
    int iterations = 0;
    while(db.find(hdd) == db.end()) {
        db.insert(hdd);
        hdd.defrag_iter();
        iterations += 1;
    }
    return iterations;
}

int task_2() {
    HDD hdd;
    for(int i = 0; i < N_BANKS; i += 1) {
        int tmp; cin >> tmp;
        hdd.bank[i] = static_cast<unsigned char>(tmp);
    }
    
    set<HDD> db;
    int iterations = 0;
    while(db.find(hdd) == db.end()) {
        hdd.id = iterations;
        db.insert(hdd);
        hdd.defrag_iter();
        iterations += 1;
    }
    return iterations - (*db.find(hdd)).id;
}

int main() {

    cout << task_2() << endl;
    
    return 0;
}