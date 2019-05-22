#include <windows.h>
#include<stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#undef main;

int iPointNum = 0;

int x1 = 0, x2 = 200, y1 = 150, y2 = 200;
int xwl = 0, xwr = 0, ywb = 0, ywt = 0;
int winWidth = 300, winHeight = 400;

void Initial(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

void ChangeSize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void swap(GLint& a, GLint& b) { GLint t = a; a = b; b = t; }

/*BresenhamLine算法*/
void Bresenhamline(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容

	if (x2<x1)
	{
		swap(x2, x1);
		swap(y2, y1);
	}
	//画第一个点
	int x, y;
	x = x1;
	y = y1;
	setPixel(x, y);
	//首先处理直线平行坐标轴
	if (y1 == y2)
	{
		//平行x轴
		while (x<x2)
		{
			x++;
			setPixel(x, y);
		}
		return;
	}
	if (x1 == x2)
	{
		//平行y轴
		while (y<y2)
		{
			y++;
			setPixel(x, y);
		}
		return;
	}
	int dx = x2 - x1, dy = y2 - y1;
	int p;
	int twoDy = 2 * dy, twoMinusDx = 2 * (dy - dx), twoDx = 2 * dx, twoMinusDy = 2 * (dx - dy);
	int twoSum = 2 * (dy + dx);
	double k = (double)dy / (double)dx;

	//0<k<1的情况
	if (k<1.0&&k>0.0)
	{
		p = 2 * dy - dx;
		while (x<x2)
		{
			x++;
			if (p<0)
				p += twoDy;
			else
			{
				y++;
				p += twoMinusDx;
			}
			setPixel(x, y);
		}
	}
	//k>=1的情况
	if (k >= 1.0)
	{
		p = dy;
		while (y<y2)
		{
			y++;
			if (p<0)
				p += twoDx;
			else
			{
				x++;
				p += twoMinusDy;
			}
			setPixel(x, y);
		}
	}
	//0>k>-1的情况
	if (k>-1 && k<0)
	{
		p = 2 * dy + dx;
		while (x<x2)
		{
			x++;
			if (p >= 0)
				p += twoDy;
			else
			{
				y--;
				p += twoSum;
			}
			setPixel(x, y);
		}
	}
	//k<-1的情况
	if (k <= -1)
	{
		p = 2 * dx - dy;
		while (y>y2)
		{
			y--;
			if (p >= 0)
				p -= twoDx;
			else
			{
				x++;
				p -= twoSum;
			}
			setPixel(x, y);
		}
	}
	//glutSwapBuffers();

}

int LBLineClipTest(float p, float q, float &umax, float &umin) {
	float r = 0.0;
	if (p < 0.0) {
		r = q / p;
		if (r > umin)      return 0;
		else if (r > umax)    umax = r;
	}
	else if (p > 0.0) {
		r = q / p;
		if (r < umax)      return 0;
		else if (r < umin)    umin = r;
	}
	else if (q < 0.0)        return 0;
	return 1;
}

void LBLineClip(float xwl, float xwr, float ywb, float ywt, float x1, float y1, float x2, float y2) {
	float umax, umin, deltax, deltay;
	deltax = x2 - x1;    deltay = y2 - y1;     umax = 0.0;     umin = 1.0;
	if (LBLineClipTest(-deltax, x1 - xwl, umax, umin)) {
		if (LBLineClipTest(deltax, xwr - x1, umax, umin)) {
			if (LBLineClipTest(-deltay, y1 - ywb, umax, umin)) {
				if (LBLineClipTest(deltay, ywt - y1, umax, umin)) {
					x2 = int(x1 + umin * deltax + 0.5);
					y2 = int(y1 + umin * deltay + 0.5);
					x1 = int(x1 + umax * deltax + 0.5);
					y1 = int(y1 + umax * deltay + 0.5);

				}
					Bresenhamline(x1, y1, x2, y2);
			}
		}
	}
	glutSwapBuffers();
}



void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25f, 1.0f, 0.0f);
	//glRectf(xwl, ywt, xwr, ywb);
	if(iPointNum == 2) LBLineClip(xwl, xwr, ywb, ywt, x1, y1, x2, y2);
	else {
		Bresenhamline(x1, y1, x2, y2);
		glutSwapBuffers();
	}
	printf("%d,%d,%d,%d,     %d,%d,%d,%d\n", x1, y1, x2, y2, xwl, xwr, ywb, ywt);

}



void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			xwr = xMouse;   ywb = winHeight - yMouse;
		}
		else {
			iPointNum = 2;
			xwl = xMouse;       ywt = winHeight - yMouse;
			glutPostRedisplay();
		}
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0;
		glutPostRedisplay();
	}
}

void Key(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			xwr = x;      ywb = winHeight - y;
		}
		else {
			iPointNum = 2;
			xwl = x;     ywt = winHeight - y;
			glutPostRedisplay();
		}
		break;
	default:break;
	}
}

void PassiveMouse(GLint xMouse, GLint yMouse) {
	if (iPointNum == 1) {
		xwl = xMouse;
		ywt = winHeight - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("实验3");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouse);
	Initial();
	glutMainLoop();

	return 0;
}
