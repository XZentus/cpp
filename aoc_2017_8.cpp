#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

bool check_cond(const int & l, const string & op, const int & r) {
#define __mk(_op) if(op == #_op) return l _op r
    __mk(==);
    else __mk(!=);
    else __mk(>);
    else __mk(<);
    else __mk(>=);
    else __mk(<=);
#undef __mk
    return false;
}
        
void task_1() {
    map<string, int> var;
    string var_name, var_cond, command, cond_op, _if;
    int delta, cond;
    while(cin >> var_name &&
          cin >> command &&
          cin >> delta &&
          cin >> _if &&
          cin >> var_cond &&
          cin >> cond_op &&
          cin >> cond) {
        if(check_cond(var[var_cond], cond_op, cond)) {
            if(command == "inc")
                var[var_name] += delta;
            else
                var[var_name] -= delta;
        }
    }
    for(const auto & elem: var)
        cout << elem.first << " = " << elem.second << endl;
    cout << (*(max_element(var.cbegin(), var.cend(), [](const pair<string, int> & l,
                                                        const pair<string, int> & r) {
        return l.second < r.second;}))).second << endl;
}

int main()
{
    task_1();
    
    return 0;
}
