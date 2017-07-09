#include <iostream>
int main() {
    int ival = 1024;
    int &refVal = ival;
    int *p = &ival;
    std::cout << ival << "  " << refVal << "  " << p << std::endl;
    ival = 2048;
    std::cout << ival << "  " << refVal << "  " << *p << std::endl;
    return 0 ;
}
