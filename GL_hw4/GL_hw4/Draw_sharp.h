//畫圖.h
//**************************************************************************************
//姓名:楊方寧
//學號:605415032
//E - mail : candy46410330@yahoo.com.tw
//作業環境 : Win10 64bit
//編譯器 : Visual Studio 2013
//**************************************************************************************
#ifndef __Draw_sharp
#define __Draw_sharp
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include <glut.h>
#include <gl/gl.h>

class Draw_sharp : public Fl_Gl_Window{ 


	static void Timer_CB(void *userdata) {
		Draw_sharp *pb = (Draw_sharp*)userdata;
		pb->redraw();
		Fl::repeat_timeout(1.0 / 24.0, Timer_CB, userdata);
	}

public:
	void draw();
	Draw_sharp(int x, int y, int w, int h, const char *l = 0);  
	int draw_number; //mode模式
	//int draw_open;
	int frame;
	int valid =  0 ;
}; 
#endif



