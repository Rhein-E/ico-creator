#include "ico.h"

Bitmap_32::Bitmap_32() {
    width = height = 0;
    image = NULL;
}

Bitmap_32::Bitmap_32(UINT32 col, UINT32 row) {
    image = new UINT32[col * row];
    width = col, height = row;
}

Bitmap_32::Bitmap_32(const Bitmap_32 &bmp) {
    width = bmp.width, height = bmp.height;
    image = new UINT32[width * height];
    memcpy(image, bmp.image, width * height * 4);
}

Bitmap_32::~Bitmap_32() {
    if (image)
        delete[] image;
}

Bitmap_32& Bitmap_32::operator=(const Bitmap_32 &bmp) {
    if (image)
        delete[] image;
    width = bmp.width, height = bmp.height;
    image = new UINT32[width * height];
    memcpy(image, bmp.image, width * height * 4);
    return *this;
}

UINT32& Bitmap_32::at(UINT32 x, UINT32 y) {
    return image[x * width + y];
}

void ICO::writeFileHeader(std::ofstream &fout) {
    fout.write("\0\0", 2);
    fout.write((char *)&type, 2);
    fout.write((char *)&imageCount, 2);
}

void ICO::writeInfoHeader(std::ofstream &fout) {
    INT8    width;
    INT8    height;
    UINT8   colorCount;
    UINT8   reserved;
    UINT16  planeCount;
    UINT16  bitCount;
    UINT32  dataSize;
    UINT32  dataOffset = 6 + 16 * subfigs.size();
    for (UINT32 i = 0; i < subfigs.size(); ++i) {
        width = subfigs[i].width;
        height = subfigs[i].height;
        colorCount = 0;
        reserved = 0;
        planeCount = 1;
        bitCount = 32;
        dataSize = 40 + width * height * 17 / 4;

        fout.write((char *)&width, 1);
        fout.write((char *)&height, 1);
        fout.write((char *)&colorCount, 1);
        fout.write((char *)&reserved, 1);
        fout.write((char *)&planeCount, 2);
        fout.write((char *)&bitCount, 2);
        fout.write((char *)&dataSize, 4);
        fout.write((char *)&dataOffset, 4);

        dataOffset += dataSize;
    }
}

void ICO::writeBMPData(std::ofstream &fout) {
    UINT32  headerSize = 40;
    INT32   width;
    INT32   height;
    UINT16  planeCount = 1;
    UINT16  bitWidth = 32;
    UINT32  compression = 0;
    UINT32  imageDataSize;
    INT32   xPixelsPerMeter = 0;
    INT32   yPixelsPerMeter = 0;
    UINT32  colorCount = 0;
    UINT32  importantColorCount = 0;

    
    for (UINT32 i = 0; i < subfigs.size(); ++i) {
        width = subfigs[i].width;
        height = subfigs[i].height * 2;
        imageDataSize = width * height * 2 + width * height / 8;

        fout.write((char *)&headerSize, 4);
        fout.write((char *)&width, 4);
        fout.write((char *)&height, 4);
        fout.write((char *)&planeCount, 2);
        fout.write((char *)&bitWidth, 2);
        fout.write((char *)&compression, 4);
        fout.write((char *)&imageDataSize, 4);
        fout.write((char *)&xPixelsPerMeter, 4);
        fout.write((char *)&yPixelsPerMeter, 4);
        fout.write((char *)&colorCount, 4);
        fout.write((char *)&importantColorCount, 4);

        // xor map
        for (UINT32 x = 0; x * 2 < height; ++x)
            for (UINT32 y = 0; y < width; ++y) {
                UINT32 pixel = subfigs[i].at(x, y);
                fout.write((char *)&pixel, 4);
            }
        
        // and map
        for (UINT32 x = 0; x * 2 < height; ++x)
            for (UINT32 y = 0; y * 4 < width; ++y) {
                UINT32 pixel = subfigs[i].at(x, y);
                pixel = 0xFFFFFFFFu;
                fout.write((char *)&pixel, 1);
            }
    }
}

ICO::ICO(ICO_TYPE t) {
    subfigs.clear();
    imageCount = 0;
    type = t;
}

ICO::~ICO() {
    return;
}

Bitmap_32 ICO::getSubfig(int n) {
    return subfigs[n];
}

void ICO::add(const Bitmap_32 &bitmap) {
    subfigs.push_back(bitmap);
    ++imageCount;
}

bool ICO::save(const char *filename) {
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return false;
    }

    writeFileHeader(fout);
    writeInfoHeader(fout);
    writeBMPData(fout);

    fout.close();

    return true;
}