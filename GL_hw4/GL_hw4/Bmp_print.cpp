//讀圖.cpp
//**************************************************************************************
//姓名:楊方寧
//學號:605415032
//E - mail : candy46410330@yahoo.com.tw
//作業環境 : Win10 64bit
//編譯器 : Visual Studio 2013
//**************************************************************************************
#include "bmp_print.h"

Bmp_print::Bmp_print(int x, int y, int w, int h, const char *l) : Fl_Gl_Window(x, y, w, h, l){
	Fl::add_timeout(FPS, Timer_CB, (void*)this);
	byte = 0;
	imageW = imageH = 0;
}

void Bmp_print::Timer_CB(void *userdata){
	Bmp_print *readimage = (Bmp_print*)userdata;
	readimage->redraw();
	Fl::repeat_timeout(FPS, Timer_CB, userdata);
}

void Bmp_print::ReshapeViewport(){
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, imageW, 0, imageH);
}

void Bmp_print::setImage(BYTE *byte, int w, int h){
	this->byte = byte;
	this->imageW = w;
	this->imageH = h;
}

void Bmp_print::drawPoint(int x, int y, float r, float g, float b){
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void Bmp_print::draw(){
	if (!valid()){
		valid(1);
		ReshapeViewport();
	}

	if (byte != 0)
	{
		for (int i = 0; i < imageW; i++)
		for (int j = 0; j < imageH; j++)
			drawPoint(i, j, (float)*(byte + (j + i*imageW) * 3 + 0) / 255.0, (float)*(byte + (j + i*imageW) * 3 + 1) / 255.0, (float)*(byte + (j + i*imageW) * 3 + 2) / 255.0);
	}
}

int Bmp_print::handle(int event){
	switch (event){
	case FL_PUSH:
		return 1;

	default:
		return Fl_Gl_Window::handle(event);
	}
}