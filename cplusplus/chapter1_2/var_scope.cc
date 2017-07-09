#include <iostream>
int reused = 1024;
int main() {
    int inner = 0;
    std::cout << reused << "  " << inner << std::endl;
    int reused = 1;
    std::cout << reused << "  " << inner << std::endl;
    std::cout << ::reused << "  " << inner << std::endl;
    return 0;
}
