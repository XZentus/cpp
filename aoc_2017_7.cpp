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
    Node(): total_sum(0) {};
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

void fill_sums(map<string, Node> & db, const string & root) {
    auto & current = db[root];
    if(current.total_sum == 0){
        if(current.leaf.empty())
            return;
        for(auto & leaf_name: current.leaf) {
            fill_sums(db, leaf_name);
            current.total_sum += db[leaf_name].total_sum + db[leaf_name].value;
        }
    }
    return;
}

void print_level(map<string, Node> & db, const string & root) {
    cout << root << ": " << db[root].value << " + " << db[root].total_sum << " = " << db[root].value + db[root].total_sum << endl;
    for(const auto & s: db[root].leaf)
        cout << "    " << s << ": " << db[s].value << " + " << db[s].total_sum << " = " << db[s].value + db[s].total_sum << endl;
}

bool check_leaves(map<string, Node> & db, const string & root) {
	if (db[root].leaf.empty())
		return true;

    auto iter = db[root].leaf.begin();
    int val1 = db[*iter].value + db[*iter].total_sum;
	for(auto end = db[root].leaf.end(); iter != end; ++iter) {
		if(!check_leaves(db, *iter))
			return false;
        if(val1 != db[*iter].value + db[*iter].total_sum) {
            print_level(db, root);
			//return false;
		}
	}
	return true;
}

void task_2() {
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
    
    string root;
    for(auto citer = db.cbegin(); citer != db.cend(); ++citer)
        if(citer->second.root == "")
            root = citer->first;
    
	fill_sums(db, root);
	check_leaves(db, root);
    return;
}

int main() {
    task_2();
    
    return 0;
}
