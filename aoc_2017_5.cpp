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

int main() {
    cout << task_1() << endl;
    return 0;
}