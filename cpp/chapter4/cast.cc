#include<iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
    int a = 1, b = 4;
    double slope = static_cast<double>(a) / b;
    cout << a / b << " cast: " << slope << endl;
    double val = 6.4444;
    void * p = &val;
    double *dp = static_cast<double *>(p);
    cout<<*dp<<endl;

    const char *cpc = "hello world";
    char *pc = const_cast<char*>(cpc);
    cout << pc << endl;
    int i = 'c';
    int *ip = &i;
    char * cip = reinterpret_cast<char*>(ip);
    cout << cip << endl;
    return 0;
}
