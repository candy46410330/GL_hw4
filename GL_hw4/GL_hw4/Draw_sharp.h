//�e��.h
//**************************************************************************************
//�m�W:�����
//�Ǹ�:605415032
//E - mail : candy46410330@yahoo.com.tw
//�@�~���� : Win10 64bit
//�sĶ�� : Visual Studio 2013
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
	int draw_number; //mode�Ҧ�
	//int draw_open;
	int frame;
	int valid =  0 ;
}; 
#endif



