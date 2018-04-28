#include <fstream>
#include <iostream>
#include <string>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

int split_yuv420(string path, int w, int h) {
    fstream input(path);
    ofstream yo("./outputs/yuv_420_y.y");
    ofstream uo("./outputs/yuv_420_u.y");
    ofstream vo("./outputs/yuv_420_v.y");

    int size = w * h * 3 / 2;
    char *data = (char *)malloc(size);

    input.read(data, size);
    yo.write(data, w * h);
    uo.write(data + w * h, w * h / 4);
    vo.write(data + w * h * 5 / 4, w * h / 4);

    input.close();
    uo.close();
    yo.close();
    vo.close();
    return 0;
}
int split_yuv444(string path, int w, int h) {
    fstream input(path);
    ofstream yo("./outputs/yuv_444_y.y");
    ofstream uo("./outputs/yuv_444_u.y");
    ofstream vo("./outputs/yuv_444_v.y");

    int size = w * h * 3;
    char *data = (char *)malloc(size);

    input.read(data, size);
    yo.write(data, w * h);
    uo.write(data + w * h, w * h);
    vo.write(data + w * h * 2, w * h);

    input.close();
    uo.close();
    yo.close();
    vo.close();
    return 0;
}

int yuv420_gray(string path, int w, int h) {
    fstream input(path);
    ofstream output("./outputs/yuv420_gray.yuv");
    char *data = (char *)malloc(w * h * 3 / 2);
    input.read(data, w * h * 3 / 2);
    memset(data + w * h, (unsigned char)128, w * h / 2);
    output.write(data, w * h * 3 / 2);
    input.close();
    output.close();
    return 0;
}

int yuv420_halfy(string path, int w, int h) {
    fstream input(path);
    ofstream output("./outputs/yuv420_halfy.yuv");
    char *data = (char *)malloc(w * h * 3 / 2);
    input.read(data, w * h * 3 / 2);
    for (int i = 0; i < w * h; i++) {
        *(data + i) = *(data + i) >> 1;
    }
    output.write(data, w * h * 3 / 2);
    input.close();
    output.close();
    return 0;
}
int yuv420_border(string path, int w, int h, int border) {
    fstream input(path);
    ofstream output("./outputs/yuv420_border.yuv");
    char *data = (char *)malloc(w * h * 3 / 2);
    input.read(data, w * h * 3 / 2);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (i < border || i > w - border || j < border || j > h - border) {
                data[i * w + j] = 0x00;
            }
        }
    }
    output.write(data, w * h * 3 / 2);
    input.close();
    output.close();
    return 0;
}
int main() {
    // return split_yuv420("./lena_256x256_yuv420p.yuv", 256, 256);
    // return split_yuv444("./lena_256x256_yuv444p.yuv", 256, 256);
    // return yuv420_gray("./lena_256x256_yuv420p.yuv", 256, 256);
    // return yuv420_halfy("./lena_256x256_yuv420p.yuv", 256, 256);
    return yuv420_border("./lena_256x256_yuv420p.yuv", 256, 256, 10);
}