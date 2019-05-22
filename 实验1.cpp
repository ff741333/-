#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

static GLsizei iMode = 0;

int iPointNum = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
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

void print1(int iPointNum) {//画直线
	if (iPointNum >= 1) {
		glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glEnd();
	}
	glutSwapBuffers();
}
void print2(int iPointNum) {//画矩形
	if (iPointNum >= 1) {
		glRectf(x1, y1, x2, y2);
	}
	glutSwapBuffers();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25f, 1.0f, 0.0f);
	switch (iMode) {
	case 1:
		print1(iPointNum); break;
	case 2:
		print2(iPointNum); break;
	default:break;
	}

}

void ProcessMenu(int value) {
	iMode = value;
	glutPostRedisplay();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			x1 = xMouse;   y1 = winHeight - yMouse;
		}
		else {
			iPointNum = 2;
			x2 = xMouse;       y2 = winHeight - yMouse;
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
			x1 = x;      y1 = winHeight - y;
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

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("1");
	int nGLutCurveMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("矩形", 2);
	glutAddMenuEntry("直线", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouse);
	Initial();
	glutMainLoop();
	return 0;
}
