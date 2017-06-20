//////////////////////////////////////////////////////////////
#include "Read_bmp.h"
#include "bitmap.h"
#include "Draw_sharp.h"
#include "Bmp_print.h" 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cv.h>
#include<highgui.h>
#include <math.h>
#include <time.h> 
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
using namespace std;
using namespace cv;
uchar blue[512][512];
uchar green[512][512];
uchar red[512][512];
uchar gray[512][512];
uchar temp[512][512];
uchar blue2[512][512];
uchar green2[512][512];
uchar red2[512][512];
uchar blue3[512][512];
uchar green3[512][512];
uchar red3[512][512];

#define tem 64

Fl_Window* Interface;
Fl_Button* mode_Draw;
Fl_Button* mode_Quit;
Fl_Button* mode_Clear;
Fl_Button* mode_Line;
Fl_Button* mode_Triangle;
Fl_Button* mode_Point;
Fl_Button* mode_New1;
Fl_Button* mode_New2;
Fl_Button* mode_New3;
Draw_sharp* drawpicture;
Bmp_print* readimage1;
Bmp_print* readimage2;

void second(IplImage *srcImg, IplImage *desImg, int x, int y);

void overlap(IplImage* srcImg, IplImage *desImg, int x, int y){
	int square = tem;   //方格邊長

	unsigned seed;
	seed = (unsigned)time(NULL); // 取得時間序列
	srand(seed); // 以時間序列當亂數種子
	int a = srcImg->height;
	int b = srcImg->width;
	while (a> srcImg->height - square)
		a = rand() / srcImg->height;
	while (b>srcImg->width - square)
		b = rand() / srcImg->width;

	printf("a=%d b=%d\n", a, b);

	for (int i = 0; i < srcImg->height; i++){//隨機取src的
		for (int j = 0; j < srcImg->widthStep; j = j + 3){
			blue[i][(int)j / 3] = srcImg->imageData[i*srcImg->widthStep + j];
			green[i][(int)j / 3] = srcImg->imageData[i*srcImg->widthStep + j + 1];
			red[i][(int)j / 3] = srcImg->imageData[i*srcImg->widthStep + j + 2];
		}
	}

	for (int i = 0; i < square; i++){
		for (int j = 0; j <square; j++){
			blue2[i][j] = blue[i][j];
			green2[i][j] = green[i][j];
			red2[i][j] = red[i][j];
		}
	}

	for (int i = 0; i < desImg->height; i++){
		for (int j = 0; j < desImg->widthStep; j = j + 3){
			desImg->imageData[i*desImg->widthStep + j] = blue2[i][(int)j / 3];
			desImg->imageData[i*desImg->widthStep + j + 1] = green2[i][(int)j / 3];
			desImg->imageData[i*desImg->widthStep + j + 2] = red2[i][(int)j / 3];
		}
	}
	second(srcImg, desImg, square, 0);
}
void second(IplImage *srcImg, IplImage *desImg, int x, int y){   //將方格邊長傳下來  x=square
	int path = 0;
	int min = 1000000;
	int cost = 0;
	int lenth = x;
	int count = 1;
	unsigned seed;
	seed = (unsigned)time(NULL); // 取得時間序列
	srand(seed); // 以時間序列當亂數種子
	printf("-----\n");
	int size = 10;
	int xx = srcImg->height;
	int yy = srcImg->width;
	int sub = 5200001;

	while (lenth < 240){
		sub = 4000001; //2
		while (sub > 4000000){ //2
			xx = rand() / srcImg->height;
			yy = rand() / srcImg->width;
			while (xx > srcImg->height - x)   //xx,yy是另一張圖的起始位置
				xx = rand() / srcImg->height;
			while (yy > srcImg->width - x)
				yy = rand() / srcImg->width;

			sub = 0;
			printf(" xx = %d ", xx);

			for (int i = 0; i < x; i++){  //------------x=square=64  圖形的邊長
				for (int j = 0; j < x; j++){
					//bbbb[i][j] = temp[xx + i][yy + j];
					red3[i][j] = red[xx + i][yy + j];
					green3[i][j] = green[xx + i][yy + j];
					blue3[i][j] = blue[xx + i][yy + j];
				}
			}

			for (int i = 0; i < x; i++){
				for (int j = 0; j < size; j++){

					sub = sub + (red2[i][x - size + j] - red3[i][j])*(red2[i][x - size + j] - red3[i][j]);

				}
			}
			printf(" sub=%d\n", sub);
		}
		//-------當誤差小於800000--------

		for (int i = 0; i < x; i++){
			for (int j = 0; j < x; j++){
				red3[i][j] = red[xx + i][yy + j];
				green3[i][j] = green[xx + i][yy + j];
				blue3[i][j] = blue[xx + i][yy + j];
			}
		}

		for (int i = 0; i < x; i++){
			for (int j = 0; j < 10; j++){
				cost = (red2[i][x - size + j] - red3[i][j]) *(red2[i][x - size + j] - red3[i][j]);
				if (min > cost){
					min = cost;
					path = j;
					printf("cost%d\n", cost);
				}
				for (int k = 0; k <path; k++){
					red3[i][k] = red2[i][x - size + k];
					green3[i][k] = green2[i][x - size + k];
					blue3[i][k] = blue2[i][x - size + k];
				}
				min = 1000000;

			}
		}

		for (int i = 0; i < x; i++){
			for (int j = 0; j < x; j++){
				red2[i][j] = red3[i][j];
				green2[i][j] = green3[i][j];
				blue2[i][j] = blue3[i][j];
			}
		}


		if (lenth + x > 240){
			for (int i = 0; i < x; i++)
			{
				for (int j = count*(x - size) * 3; j < 240 * 3; j = j + 3)
				{
					desImg->imageData[i*desImg->widthStep + j] = blue3[i][(int)(j / 3) - count*(x - size)];
					desImg->imageData[i*desImg->widthStep + j + 1] = green3[i][(int)(j / 3) - count*(x - size)];
					desImg->imageData[i*desImg->widthStep + j + 2] = red3[i][(int)(j / 3) - count*(x - size)];

				}
			}
			printf("%d\n", lenth);

		}


		if (lenth + x < 240){
			for (int i = 0; i < x; i++)
			{
				for (int j = count*(x - size) * 3; j < (x + count*(x - size)) * 3; j = j + 3)
				{
					desImg->imageData[i*desImg->widthStep + j] = blue3[i][(int)(j / 3) - count*(x - size)];
					desImg->imageData[i*desImg->widthStep + j + 1] = green3[i][(int)(j / 3) - count*(x - size)];
					desImg->imageData[i*desImg->widthStep + j + 2] = red3[i][(int)(j / 3) - count*(x - size)];

				}
			}
			printf("%d\n", lenth);
		}
		lenth = lenth + (x - size);
		printf("lenth=%d\n", lenth);
		printf("%d\n", count);
		count = count + 1;
	}
}
void Click_Quit(Fl_Widget*, void*)
{
	mode_Quit->value(1);
	exit(0);
}
void Click_Draw(Fl_Widget *, void*)
{
	char* ImgFileName = "cans_sc.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("cans_sc", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("cans_sc_big", img2);
	cvSaveImage("cans_sc_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("cans_sc_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();
	
	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}
void Click_Clear(Fl_Widget*, void*)
{
	char* ImgFileName = "berry.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("berry", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("berry_big", img2);
	cvSaveImage("berry_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("berry_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}
void Click_Line(Fl_Widget *, void*)
{
	char* ImgFileName = "mesh.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("mesh", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("mesh_big", img2);
	cvSaveImage("mesh_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("mesh_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}

void Click_Triangle(Fl_Widget *, void*)
{
	char* ImgFileName = "btile.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("btile", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("btile_big", img2);
	cvSaveImage("btile_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("btile_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}

void Click_Point(Fl_Widget *, void*)
{
	char* ImgFileName = "fabric.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("fabric", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("fabric_big", img2);
	cvSaveImage("fabric_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("fabric_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}

void Click_New1(Fl_Widget *, void*)
{
	char* ImgFileName = "greek.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("greek", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("greek_big", img2);
	cvSaveImage("greek_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("fabric_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}
void Click_New2(Fl_Widget *, void*)
{
	char* ImgFileName = "rice.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("rice", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("rice_big", img2);
	cvSaveImage("rice_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("fabric_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}
void Click_New3(Fl_Widget *, void*)
{
	char* ImgFileName = "wool.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("wool", img1);

	IplImage *img2 = cvLoadImage(ImgFileName);
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("wool_big", img2);
	cvSaveImage("wool_big.bmp", img2);

	/*int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("fabric_big.bmp", &img, w, h);

	//readimage1 = new Bmp_print(405, 10, 400, 350);
	//readimage1->setImage(img, w, h);

	readimage2 = new Bmp_print(10, 10, 380, 350);
	readimage2->setImage(img, w, h);*/

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);

	Interface->end();

	//drawpicture->draw_number =4 ;
	//mode_Draw->value(1);
	printf("draw\n");
}
int main(int argc, char **argv){
	Interface = new Fl_Window(900, 500, "HW04_605415032");

	mode_Quit = new Fl_Button(100, 450, 100, 30, "Quit");
	mode_Quit->callback((Fl_Callback*)Click_Quit);
	
	mode_Draw = new Fl_Button(250, 450, 100, 30, "cans_sc.bmp");
	mode_Draw->callback((Fl_Callback*)Click_Draw);

	mode_Clear = new Fl_Button(400, 450, 100, 30, "berry.bmp");
	mode_Clear->callback((Fl_Callback*)Click_Clear);


	mode_Line = new Fl_Button(100, 400, 100, 30, "mesh.bmp");
	mode_Line->callback((Fl_Callback*)Click_Line);

	mode_Triangle = new Fl_Button(250, 400, 180, 30, "btile.bmp(very~slow!!)");
	mode_Triangle->callback((Fl_Callback*)Click_Triangle);

	mode_Point = new Fl_Button(500, 400, 80, 30, "fabric.bmp");
	mode_Point->callback((Fl_Callback*)Click_Point);


	mode_New1 = new Fl_Button(100, 350, 80, 30, "greek(very~slow!!).bmp");
	mode_New1->callback((Fl_Callback*)Click_New1);

	mode_New2 = new Fl_Button(250, 350, 80, 30, "rice.bmp");
	mode_New2->callback((Fl_Callback*)Click_New2);

	mode_New3 = new Fl_Button(400, 350, 80, 30, "wool.bmp");
	mode_New3->callback((Fl_Callback*)Click_New3);

	//////////////////////////////////////////////////////
	char* ImgFileName = "lobelia.bmp";
	IplImage *img1 = cvLoadImage(ImgFileName);
	cvShowImage("lobelia", img1);
	
	IplImage *img2 = cvLoadImage(ImgFileName);  
	CvSize imgSize2 = cvSize(512, 512);
	img2 = cvCreateImage(imgSize2, IPL_DEPTH_8U, 3);
	overlap(img1, img2, img1->height, img1->widthStep);
	cvShowImage("lobelia_big", img2);
	cvSaveImage("lobelia_big.bmp", img2);

	int w, h;
	BYTE *img = (BYTE*)malloc(sizeof(BYTE*));
	BMP_Read("lobelia_big.bmp", &img, w, h);
	
	readimage1 = new Bmp_print(405, 10, 400, 350);
	readimage1->setImage(img, w, h);

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	///////////////////////////////////////////////////////
	
	Interface->end();
	Interface->show(argc, argv);
	
	cvWaitKey();
	return Fl::run();
}