struct data {
    int a;
    int b;
};

struct data global_data;

int main() {
    for (int i = 0; i < 500000000; ++i) {
        ++global_data.a;
    }
    for (int i = 0; i < 500000000; ++i) {
        ++global_data.b;
    }
    return 0;
}