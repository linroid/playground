#include <thread>
struct data {
    int a;
    // Add fence to avoid shared cache line (False Sharing)
    // char fence[ 64];
    int b;
};

struct data global_data;

void add_a() {
    for (int i = 0; i < 500000000; ++i) {
        ++global_data.a;
    }
}

void add_b() {
    for (int i = 0; i < 500000000; ++i) {
        ++global_data.b;
    }
}

int main() {
    std::thread t1(add_a);
    std::thread t2(add_b);
    t1.join();
    t2.join();
    return 0;
}