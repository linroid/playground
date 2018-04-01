#include<iostream>
int main() {
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *ia_begin = std::begin(ia);
    int *ia_end = std::end(ia);
    std::cout<<*ia_begin<<" " << *(ia_end-1) << std::endl;
    while(ia_begin != ia_end) {
        std::cout << *ia_begin << std::endl;
        ia_begin++;
    }
    return 0;
}
