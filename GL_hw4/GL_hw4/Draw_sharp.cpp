//畫圖.cpp
//**************************************************************************************
//姓名:楊方寧
//學號:605415032
//E - mail : candy46410330@yahoo.com.tw
//作業環境 : Win10 64bit
//編譯器 : Visual Studio 2013
//**************************************************************************************
//有參考黃翊淳draw方面部分的idea。
//因為原本自己的程式碼太過攏長及想法變得太複雜，認為有更好的idea可以畫圖
//最後了解這個idea並自己完成程式碼,並加入新的的idea改善

#include "Draw_sharp.h"

Draw_sharp::Draw_sharp(int x, int y, int w, int h, const char *l) :
Fl_Gl_Window(x, y, w, h, l)
{
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
	Fl::add_timeout(1.0 / 24.0, Timer_CB, (void*)this);
	frame = 0;
}

void Draw_sharp::draw() {  
	// the valid() property may be used to avoid reinitializing your GL transformation for each redraw:
	if (!valid) {             
		valid = 1;
		glLoadIdentity();
		glViewport(0, 0, w(), h());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_QUADS);
		glColor3f(1, 1, 1); glVertex2f(-1, -1); //全白
		glColor3f(1, 1, 1); glVertex2f(-1, 1);
		glColor3f(1, 1, 1); glVertex2f(1, 1);
		glColor3f(1, 1, 1); glVertex2f(1, -1);
		printf("clear2\n");  //確認有clear
		glEnd();
		draw_number = 0;

	}
	
	if (draw_number == 1){ //clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_QUADS);
			glColor3f(1, 1, 1); glVertex2f(-1, -1); //全白
			glColor3f(1, 1, 1); glVertex2f(-1, 1);
			glColor3f(1, 1, 1); glVertex2f(1, 1);
			glColor3f(1, 1, 1); glVertex2f(1, -1);
			printf("clear2\n");  //確認有clear
			glEnd();
			draw_number = 0;
		}

		if (draw_number == 5) //point_mode
		{
			float draw_point[2] = { 0 };
			float color_BLUE = 0.0;
			float color_GREEN = 0.0;
			float color_RED = 0.0;

			for (int i = 0; i<2; i += 2) //一個點(x,y) 2個
			{
				int min = (rand() % 2) - 1;
				if (min == 0)
					min = 1;

				float point_X = 0.0, point_Y = 0.0;
				while (point_X == point_Y) {
					point_X = rand();
					point_X = point_X/32767;
					point_Y = rand();
					point_Y = point_Y/32767;
					color_BLUE = rand();
					color_BLUE = color_BLUE/32767;
					color_GREEN = rand();
					color_GREEN = color_GREEN/ 32767;
					color_RED = rand();
					color_RED = color_RED/32767;
				} 
				
				draw_point[i] = ((float)min*point_X);
				draw_point[i + 1] = ((float)min*point_Y);
				
			}
			glBegin(GL_POINTS);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(draw_point[0], draw_point[1]);
			printf("point2\n"); //確認有顯示point
			glEnd();
			draw_number = 0;
		}
		
		if (draw_number == 3) //line_mode
		{
			float dlines[4] = { 0 };
			float color_BLUE = 0;
			float color_GREEN = 0;
			float color_RED = 0;

			for (int i = 0; i<4; i += 2)
			{
				int min = (rand() % 2) - 1;
				if (min == 0)
					min = 1;
				
				float point_X = 0, point_Y = 0;
				while (point_X == point_Y){
					point_X = rand();
					point_X = point_X / 32767;
					point_Y = rand();
					point_Y = point_Y / 32767;
					color_BLUE = rand();
					color_BLUE = color_BLUE / 32767;
					color_GREEN = rand();
					color_GREEN = color_GREEN / 32767;
					color_RED = rand();
					color_RED = color_RED / 32767;
				} 

				dlines[i] = ((float)min*point_X);
				dlines[i + 1] = ((float)min*point_Y);

			}
			glBegin(GL_LINES);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(dlines[0], dlines[1]);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(dlines[2], dlines[3]);
			draw_number = 0;
			printf("line2\n");////確認有顯示line
			glEnd();
		}

		if (draw_number == 4)  //Triangle_mode
		{
			float dtTriangle[6] = { 0 };
			float color_BLUE = 0;
			float color_GREEN = 0;
			float color_RED = 0;

			for (int i = 0; i<6; i += 2)
			{
				int min = rand() % 2 - 1;
				if (min == 0)
					min = 1;

				float point_X = 0, point_Y = 0;
				while (point_X == point_Y){
					point_X = rand();
					point_X = point_X / 32767;
					point_Y = rand();
					point_Y = point_Y / 32767;
					color_BLUE = rand();
					color_BLUE = color_BLUE / 32767;
					color_GREEN = rand();
					color_GREEN = color_GREEN / 32767;
					color_RED = rand();
					color_RED = color_RED / 32767;
				}

				dtTriangle[i] = ((float)min*point_X);
				dtTriangle[i + 1] = ((float)min*point_Y);

			}
			glBegin(GL_TRIANGLES);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(dtTriangle[0], dtTriangle[1]);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(dtTriangle[2], dtTriangle[3]);
			glColor3f(color_RED, color_GREEN, color_BLUE);
			glVertex2f(dtTriangle[4], dtTriangle[5]);
			printf("Triangle2\n");//確認有顯示Triangle
			glEnd();
			draw_number = 0;
		}
		++frame;
	}
