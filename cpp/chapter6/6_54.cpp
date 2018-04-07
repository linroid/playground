#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multipy(int a, int b) { return a * b; }
int _div(int a, int b) { return b != 0 ? a / b : 0; }
int main() {
        int func(int, int);
        vector<decltype(func) *> list;
        list.push_back(add);
        list.push_back(subtract);
        list.push_back(multipy);
        list.push_back(_div);
        for (auto fun : list) {
                cout << fun(8, 2) << endl;
        }
        return 0;
}