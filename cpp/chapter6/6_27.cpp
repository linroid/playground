#include<iostream>
int sum(std::initializer_list<int> vars) {
    int ret=0;
    for (auto beg=vars.begin(); beg!=vars.end(); ++beg) {
        ret += *beg;
    }
    std::cout<<ret<<std::endl;
}
