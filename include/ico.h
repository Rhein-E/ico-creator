#ifndef ICO_H
#define ICO_H

#include "basic.h"

class Bitmap_32 {
private :

public :
    UINT32 width;
    UINT32 height;
    UINT32 *image;

    Bitmap_32();
    Bitmap_32(UINT32 col, UINT32 row);
    Bitmap_32(const Bitmap_32 &bmp);
    ~Bitmap_32();
    UINT32& at(UINT32 x, UINT32 y);
    Bitmap_32& operator=(const Bitmap_32 &bmp);
};

enum ICO_TYPE {
    ICON = 1,
    CURSOR = 2
};

class ICO {
private :

    void writeFileHeader(std::ofstream &fout);
    void writeInfoHeader(std::ofstream &fout);
    void writeBMPData(std::ofstream &fout);

public :
    UINT32 imageCount;
    ICO_TYPE type;
    std::vector<Bitmap_32> subfigs;

    ICO(ICO_TYPE t);
    ~ICO();
    Bitmap_32 getSubfig(int n);
    void add(const Bitmap_32 &bitmap);
    bool save(const char *filename);
    bool load(const char *filename);
};


#endif // ICO_H