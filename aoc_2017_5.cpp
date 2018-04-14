#include <iostream>
#include <vector>

using namespace std;

int task_1() {
    int pos = 0, counter = 0;
    vector<int> stack;
    int tmp;
    while(cin >> tmp)
        stack.push_back(tmp);
    while(pos >= 0 && pos < stack.size()) {
        counter += 1;
        stack[pos] += 1;
        pos += stack[pos] - 1;
    }
    return counter;
}

int task_2() {
    int pos = 0, counter = 0, prev_pos, p_val;
    vector<int> stack;
    int tmp;
    while(cin >> tmp)
        stack.push_back(tmp);
    while(pos >= 0 && pos < stack.size()) {
        counter += 1;
        prev_pos = pos;
        p_val = stack[pos];
        pos += p_val;
        stack[prev_pos] += (p_val >= 3) ? -1 : 1;
    }
    return counter;
}

int main() {
    cout << task_2() << endl;
    return 0;
}
