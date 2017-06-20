
#include <stdio.h>
#include <windows.h>


#define BITMAP_ID 0x4D42								// the universal bitmap ID

unsigned char *LoadBitmap(char *FileName, char ErrMsg[512], int &Width, int &Height);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, char ErrMsg[512]);
int WriteBitmapFile(char *filename, int width, int height, unsigned char *imageData, int BPP, char ErrMsg[512]);
