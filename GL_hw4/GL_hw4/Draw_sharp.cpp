//�e��.cpp
//**************************************************************************************
//�m�W:�����
//�Ǹ�:605415032
//E - mail : candy46410330@yahoo.com.tw
//�@�~���� : Win10 64bit
//�sĶ�� : Visual Studio 2013
//**************************************************************************************
//���ѦҶ����Edraw�譱������idea�C
//�]���쥻�ۤv���{���X�ӹL�l���ηQ�k�ܱo�ӽ����A�{������n��idea�i�H�e��
//�̫�F�ѳo��idea�æۤv�����{���X,�å[�J�s����idea�ﵽ

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
		glColor3f(1, 1, 1); glVertex2f(-1, -1); //����
		glColor3f(1, 1, 1); glVertex2f(-1, 1);
		glColor3f(1, 1, 1); glVertex2f(1, 1);
		glColor3f(1, 1, 1); glVertex2f(1, -1);
		printf("clear2\n");  //�T�{��clear
		glEnd();
		draw_number = 0;

	}
	
	if (draw_number == 1){ //clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_QUADS);
			glColor3f(1, 1, 1); glVertex2f(-1, -1); //����
			glColor3f(1, 1, 1); glVertex2f(-1, 1);
			glColor3f(1, 1, 1); glVertex2f(1, 1);
			glColor3f(1, 1, 1); glVertex2f(1, -1);
			printf("clear2\n");  //�T�{��clear
			glEnd();
			draw_number = 0;
		}

		if (draw_number == 5) //point_mode
		{
			float draw_point[2] = { 0 };
			float color_BLUE = 0.0;
			float color_GREEN = 0.0;
			float color_RED = 0.0;

			for (int i = 0; i<2; i += 2) //�@���I(x,y) 2��
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
			printf("point2\n"); //�T�{�����point
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
			printf("line2\n");////�T�{�����line
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
			printf("Triangle2\n");//�T�{�����Triangle
			glEnd();
			draw_number = 0;
		}
		++frame;
	}
