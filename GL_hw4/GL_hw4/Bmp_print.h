//讀圖.h
//**************************************************************************************
//姓名:楊方寧
//學號:605415032
//E - mail : candy46410330@yahoo.com.tw
//作業環境 : Win10 64bit
//編譯器 : Visual Studio 2013
//**************************************************************************************
#ifndef __Bmp_print
#define __Bmp_print
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include <glut.h>
#include <gl/gl.h>

#define FPS (1.0/10.0)
typedef unsigned char BYTE;

class Bmp_print : public Fl_Gl_Window{
public:
	BYTE *byte;
	int imageW, imageH;
	static void Timer_CB(void *userdata);
	void setImage(BYTE *byte, int w, int h);
	Bmp_print(int x, int y, int w, int h, const char *l = 0);
	void draw();
	void drawPoint(int x, int y, float r, float g, float b);
	void ReshapeViewport();
	int handle(int event);
};
#endif
