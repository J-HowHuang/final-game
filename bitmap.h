#ifndef BITMAP_H
#define BITMAP_H
#include<windows.h>
class BmpLoader
{
private:
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
public:
    unsigned char *TextureData;
    int iWidth,iHeight;
    BmpLoader(const char *);
    ~BmpLoader();
    
};
#endif
