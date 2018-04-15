#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>

using namespace std;

struct Node {
    string root;
    int value;
    int total_sum;
    set<string> leaf;
};

int parse(const string & v) {
    int ret = 0;
    for(int i = 1, lim = v.size() - 1; i < lim; i += 1)
        ret = ret * 10 + v[i] - '0';
    return ret;
}

void task_1() {
    map<string, Node> db;
    
    string line, word, node_name, val_str;
    while(getline(cin, line) && line.size()) {
        istringstream inp(line);
        inp >> node_name;
        inp >> val_str;
        if(inp >> word) { // "->"
            while(inp >> word && word.size()) {
                if(word[word.size() - 1] == ',')
                    word.pop_back();
                db[word].root = word;
                db[node_name].leaf.insert(word);
            }
        }
        db[node_name].value = parse(val_str);
    }
    
    for(auto citer = db.cbegin(); citer != db.cend(); ++citer)
        if(citer->second.root == "") {
            cout << citer->first << endl;
            return;
        }
    
    return;
}

int main() {
    task_1();
    
    return 0;
}