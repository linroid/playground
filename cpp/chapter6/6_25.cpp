#include<iostream>
#include<cstring>
#include<string>
using std::string;
int main(int argc, char **argv) {
    string cmd(argv[0]);
    string ret;
    std::cout<<"cmd="<<cmd<<",argc="<<argc<<",size="<<sizeof(**argv)<<", argv="<<argv<<std::endl;
    for (int i=0; i<argc; i++) {
        ret = ret + argv[i];
    }
    std::cout<<ret<<std::endl;
    return 0;
}
