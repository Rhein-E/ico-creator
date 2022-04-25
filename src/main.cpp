#include "basic.h"
#include "ico.h"

void halt(const char *msg) {
    std::cout << msg;
    exit(-1);
}

int main(int argc, char **argv) {
    char out[128] = "../out.png";
    char src[16][128];
    int n = 0;
    for (int i = 1; i < argc; ++i)
        if (!strcmp(argv[i], "-o")) {
            if (++i >= argc)
                halt("missing filename after \'-o\'");
            else
                strcpy(out, argv[i]);
        } else {
            strcpy(src[n++], argv[i]);
        }

    ICO ico(ICON);
    for (int i = 0; i < n; ++i) {
        cv::Mat mat = cv::imread(src[i], cv::IMREAD_UNCHANGED);
        Bitmap_32 bitmap(mat.rows, mat.cols);
        for (UINT32 x = 0; x < mat.rows; ++x)
            for (UINT32 y = 0; y < mat.cols; ++y)
                memcpy(&bitmap.at(mat.rows - 1 - x, y), mat.ptr<uchar>(x) + y * 4, 4);
        ico.add(bitmap);
    }
    ico.save(out);


    return 0;
}