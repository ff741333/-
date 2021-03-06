#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

int iPointNum = 0;
int x1 = 0, x2 = 0, y11 = 0, y2 = 0;
int winWidth = 300, winHeight = 400;

void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    
	glMatrixMode(GL_PROJECTION);       
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void ChangeSize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void putpixel(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glVertex2f((int)((x1+x2)/2) + x,(int)((y11+y2)/2) + y);
	glEnd();
	glFlush();
}
void MidBresenhamEllipse(int a, int b)
{
	int x, y;
	float d1, d2;
	x = 0;
	y = b;
	d1 = b * b + a * a*(-b + 0.25);
	putpixel(x, y);
	putpixel(-x, -y);
	putpixel(-x, y);
	putpixel(x, -y);
	while (b*b*(x + 1)<a*a*(y - 0.5))
	{
		if (d1 <= 0)
		{
			d1 += b * b*(2 * x + 3);
			x++;
		}
		else
		{
			d1 += b * b*(2 * x + 3) + a * a*(-2 * y + 2);
			x++;
			y--;
		}
		putpixel(x, y);
		putpixel(-x, -y);
		putpixel(-x, y);
		putpixel(x, -y);
	}
	d2 = b * b*(x + 0.5)*(x + 0.5) + a * a*(y - 1)*(y - 1) - a * a*b*b;
	while (y>0)
	{
		if (d2 <= 0)
		{
			d2 += b * b*(2 * x + 2) + a * a*(-2 * y + 3);
			x++;
			y--;
		}
		else
		{
			d2 += a * a*(-2 * y + 3);
			y--;
		}
		putpixel(x, y);
		putpixel(-x, -y);
		putpixel(-x, y);
		putpixel(x, -y);
	}
	glutSwapBuffers();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25f, 1.0f, 0.0f);
	MidBresenhamEllipse(((int)fabs(x1-x2)/2), ((int)fabs(y11-y2)/2)); 
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			x1 = xMouse;   
			y11 = winHeight - yMouse;
		}
		else {
			iPointNum = 2;
			x2 = xMouse;       
			y2 = winHeight - yMouse;
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
			x1 = x;      y11 = winHeight - y;
		}
		else {
			iPointNum = 2;
			x2 = x;     y2 = winHeight - y;
			glutPostRedisplay();
		}
		break;
	default:break;
	}
}

void PassiveMouse(GLint xMouse, GLint yMouse) {
	if (iPointNum == 1) {
		x2 = xMouse;
		y2 = winHeight - yMouse;
		glutPostRedisplay();
	}
}
int main(int argc, char*argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(500, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("中点Bresenham画椭圆");
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouse);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;

}
