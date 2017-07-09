#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

int main() {
    string s1;
    string s2 = s1;
    string s3 = "Hello World!";
    string s4(10, 'a');
    string::size_type len = 0;

    cout << s1 << s2 << s3 << s4 << endl;
    string line;
    while(getline(cin, line)) {
        len = line.size();
        cout << "lenth = " << len << "  " << line + ", " + "\n" + line << endl;
    }

    string word;
    while(cin >> word) {
        cout << word << endl;
    }
    return 0;
}
