#ifndef BMPLOADER_H
#define BMPLOADER_H
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
#include <stdio.h>
#include <iostream>
using namespace std;
BmpLoader::BmpLoader(const char *filename  )
{
    FILE *file = 0;
    file = fopen(filename, "rb");
    if(!file)
    {
        cout << "File not found" << endl;
    }
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    if(bfh.bfType != 0x4D42)
        cout << " Not a valid bitmap" <<endl;
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
    if(bih.biSizeImage == 0)
        bih.biSizeImage = bih.biHeight * bih.biWidth * 3;
    TextureData = new unsigned char [bih.biSizeImage];
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(TextureData, 1, bih.biSizeImage, file);
    unsigned char temp;
    for(int i = 0 ; i < bih.biSizeImage;i += 3)
    {
        temp = TextureData[i];
        TextureData[i] = TextureData[i + 2];
        TextureData[i + 2] = temp;
    }
    iWidth = bih.biWidth;
    iHeight = bih.biHeight;
    fclose(file);
}
BmpLoader::~BmpLoader()
{
    delete [] TextureData;
}
