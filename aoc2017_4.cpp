#include <iostream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

const int num_letters = 26;

struct word_letters {
    int db[num_letters] = { 0 };
    word_letters(const string & str) {
        for (const auto & c: str)
            hack_ptr[int(c)] += 1;
    }
private:
    int * hack_ptr = db - int('a');
};

bool operator<(const word_letters & l, const word_letters & r) {
    for(int i = 0; i < num_letters - 1; i += 1)
        if(l.db[i] != r.db[i])
            return l.db[i] < r.db[i];
    return l.db[num_letters - 1] != r.db[num_letters - 1];
}


void part_1()
{
    string input;
    int count = 0, valid = 0;
    while(getline(cin, input) && input.length()) {
        stringstream inp(input);
        set<string> db;
        string word;
        bool v = true;
        while(inp >> word && word.length()) {
            auto iter = db.find(word);
            if(iter != db.end()) {
                v = false;
                break;
            }
            db.insert(word);
        }
        valid += v;
        count += 1;
    }
    cout << "passphrases: " << count << "\nvalid: " << valid << endl;
}

void part_2()
{
    string input;
    int count = 0, valid = 0;
    while(getline(cin, input) && input.length()) {
        stringstream inp(input);
        set<word_letters> db;
        string word;
        bool v = true;
        while(inp >> word && word.length()) {
            word_letters tmp(word);
            auto iter = db.find(tmp);
            if(iter != db.end()) {
                v = false;
                break;
            }
            db.insert(tmp);
        }
        valid += v;
        count += 1;
    }
    cout << "passphrases: " << count << "\nvalid: " << valid << endl;
}

int main() {
    part_2();
    return 0;
}
