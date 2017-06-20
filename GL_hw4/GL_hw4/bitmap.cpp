#include "bitmap.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cv.h>
#include<highgui.h>
#include <math.h>
#include<windows.h>
using namespace std;
using namespace cv;

unsigned char *LoadBitmap(char *FileName, char ErrMsg[512], int &m_Width, int &m_Height)
{
	unsigned char *pTData, *pData;
	BITMAPINFOHEADER Header;

	if (!(pTData = LoadBitmapFile(FileName, &Header, ErrMsg)))
		return NULL;

	if (Header.biCompression != BI_RGB)
	{
		sprintf(ErrMsg, "bmp file is compressed... cannot read");
		return NULL;
	}

	m_Width = Header.biWidth;
	m_Height = Header.biHeight;

	switch (Header.biBitCount)
	{
	case 1:
	case 8:
	case 16:
	{
			   sprintf(ErrMsg, "Image is %d bit (Only 24 or 32 bit images can be loaded)", Header.biBitCount);
			   return NULL;
	}
	case 24: // add alpha byte for each pixel
	{
				 pData = new unsigned char[m_Width * m_Height * 4];
				 for (int i = 0; i < (int)(m_Width * m_Height); i++)
				 {
					 pData[i * 4] = pTData[i * 3];
					 pData[i * 4 + 1] = pTData[i * 3 + 1];
					 pData[i * 4 + 2] = pTData[i * 3 + 2];
					 pData[i * 4 + 3] = (unsigned char)0xff;
				 }
				 delete[] pTData;
				 break;
	}
	case 32:
	{
			   pData = pTData;
			   break;
	}
	default:
	{
			   sprintf(ErrMsg, "Unkown image BPP");
			   return NULL;
	}
	}

	return pData;
}

// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		 No support for 8-bit bitmaps.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, char ErrMsg[512])
{
	//////////////////////////////////////
	//char* 
	filename = "cans_sc.bmp";
	IplImage *img1 = cvLoadImage(filename);
	//cvShowImage("org", filename);
	//////////////////////////////////////
	FILE *filePtr;								// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	int					imageIdx = 0;			// image index counter
	unsigned char		tempRGB;				// swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
	{
		sprintf(ErrMsg, "Cannot open Image file %s", filename);
		return NULL;
	}

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		sprintf(ErrMsg, "Image file %s is not BMP format", filename);
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		sprintf(ErrMsg, "Memory allocation error");
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		sprintf(ErrMsg, "Image reading fails");
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	if (bitmapInfoHeader->biBitCount == 24)
	{
		for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader->biSizeImage; imageIdx += 3)
		{
			tempRGB = bitmapImage[imageIdx];
			bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
			bitmapImage[imageIdx + 2] = tempRGB;
		}
	}
	else if (bitmapInfoHeader->biBitCount == 32)
	{
		for (int i = 0; i < (int)bitmapInfoHeader->biSizeImage; i += 4)
		{
			tempRGB = bitmapImage[i];
			bitmapImage[i] = bitmapImage[i + 2];
			bitmapImage[i + 2] = tempRGB;
		}
	}
	else
	{
		sprintf(ErrMsg, "Not 24 or 32 bit image");
		return NULL;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	/////////////////////////////
	
	cvShowImage("org", filePtr);
	//cvReleaseImage(&filePtr);
	cvWaitKey();
	//getchar();
	/////////////////////////////
	return bitmapImage;
	//system("pause");
	
}

// WriteBitmapFile()
// desc: takes 32-bit image data and saves it into a 24-bit or 32-bit RGBA .BMP file
//       with width X height dimensions
int WriteBitmapFile(char *filename, int width, int height, unsigned char *imageData, int BPP, char ErrMsg[512])
{
	///////////////////////////////
	//filename = "berry.bmp";
	//IplImage *img2 = cvLoadImage(filename);
	//CvSize imgSize2 = cvSize(512, 512);
	//img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	//overlap(img1, img2, img1->height, img1->widthStep);
	
	////////////////
	
	FILE			 *filePtr;			// file pointer
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap file header
	BITMAPINFOHEADER bitmapInfoHeader;	// bitmap info header
	int				 imageIdx;			// used for swapping RGB->BGR
	unsigned char	 *TBuf;             // temporary buffer

	if (BPP != 24 && BPP != 32)
	{
		sprintf(ErrMsg, "WriteBitmpFile ... can write only 24 or 32 bit image");
		return 0;
	}

	// open file for writing binary mode
	filePtr = fopen(filename, "wb");
	if (!filePtr)
	{
		sprintf(ErrMsg, "File open error");
		return 0;
	}

	// define the bitmap file header
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
	bitmapFileHeader.bfType = 0x4D42;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	// define the bitmap information header
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = BPP;						// 24-bit or 32-bit
	bitmapInfoHeader.biCompression = BI_RGB;				// no compression
	bitmapInfoHeader.biSizeImage = width * abs(height) * ((BPP == 32) ? 4 : 3);	// width * height * (RGB bytes)
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	bitmapInfoHeader.biWidth = width;						// bitmap width
	bitmapInfoHeader.biHeight = height;						// bitmap height

	TBuf = new unsigned char[width * abs(height) * ((BPP == 32) ? 4 : 3)];

	// switch the image data from RGB to BGR

	if (BPP == 24)
	{  // discard alpha byte
		for (int i = 0; i < width * abs(height); i++)
		{
			TBuf[i * 3] = imageData[i * 4 + 2];
			TBuf[i * 3 + 1] = imageData[i * 4 + 1];
			TBuf[i * 3 + 2] = imageData[i * 4];
		}
	}
	else
	{  // 32 bit image 
		for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader.biSizeImage; imageIdx += 4)
		{
			TBuf[imageIdx + 3] = imageData[imageIdx + 3];
			TBuf[imageIdx + 2] = imageData[imageIdx];
			TBuf[imageIdx + 1] = imageData[imageIdx + 1];
			TBuf[imageIdx] = imageData[imageIdx + 2];
		}
	}

	// write the bitmap file header
	fwrite(&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr);

	// write the bitmap info header
	fwrite(&bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), filePtr);

	// write the image data
	// fwrite(imageData, 1, bitmapInfoHeader.biSizeImage, filePtr);
	fwrite(TBuf, 1, bitmapInfoHeader.biSizeImage, filePtr);

	// close our file
	fclose(filePtr);

	/////////////////////////////
	//cvShowImage("big", filePtr);

	//cvReleaseImage(&img2);

	cvWaitKey();
	//return 0;
	/////////////////////////
	delete[] TBuf;
	//getchar();
	return 1;
	//system("pause");
}
