#include<iostream>

int swap(int *a, int *b) {
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

int main() {
    int x = 1, y = 2;
    swap(&x, &y);
    std::cout<<x<<" "<<y<< std::endl;
    return 0;
}
