#include<iostream>
#include<string>
using std::string;

int main() {
    string s("hello world");
    for (auto it = s.begin(); it != s.end(); it++) {
        *it = toupper(*it);
    }
    std::cout << s << std::endl;
    //if (s.begin() != s.end()) {
    //    std::cout << *(s.begin()) << std::endl;
    //}
    return 0;
}
