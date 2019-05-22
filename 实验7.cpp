#include<GL/glut.h>
#include<stdio.h>
int iPointNum = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int x3 = 0, x4 = 0, y3 = 0, y4 = 0;
int winWidth = 400, winHeight = 400;
GLfloat Controlp[4][3];

void initial(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(4.0);
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	GLfloat z;

	z = (GLfloat)(x1 - 200.0) / 2.0;
	Controlp[0][0] = { z };
	z = (GLfloat)(y1 - 200.0) / 2.0;
	Controlp[0][1] = { z };
	Controlp[0][2] = { 0.0 };
	z = (GLfloat)(x2 - 200.0) / 2.0;
	Controlp[1][0] = { z };
	z = (GLfloat)(y2 - 200.0) / 2.0;
	Controlp[1][1] = { z };
	Controlp[1][2] = { 0.0 };
	z = (GLfloat)(x3 - 200.0) / 2.0;
	Controlp[2][0] = { z };
	z = (GLfloat)(y3 - 200.0) / 2.0;
	Controlp[2][1] = { z };
	Controlp[2][2] = { 0.0 };
	z = (GLfloat)(x4 - 200.0) / 2.0;
	Controlp[3][0] = { z };
	z = (GLfloat)(y4 - 200.0) / 2.0;
	Controlp[3][1] = { z };
	Controlp[3][2] = { 0.0 };
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *Controlp);
	glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100, 0.0, 1.0);
	glEvalMesh1(GL_LINE, 0, 100);

	glColor3f(0.0, 0.4, 0.2);

	glBegin(GL_LINES);
	glVertex2i((x1 - 200.0) / 2.0, (y1 - 200.0) / 2.0);
	glVertex2i((x2 - 200.0) / 2.0, (y2 - 200.0) / 2.0);
	glVertex2i((x2 - 200.0) / 2.0, (y2 - 200.0) / 2.0);
	glVertex2i((x3 - 200.0) / 2.0, (y3 - 200.0) / 2.0);
	glVertex2i((x3 - 200.0) / 2.0, (y3 - 200.0) / 2.0);
	glVertex2i((x4 - 200.0) / 2.0, (y4 - 200.0) / 2.0);
	glEnd();
	glutSwapBuffers();
	glFlush();
	//printf("x1=%d,x2=%d,x3=%d,x4=%d",x1,x2,x3,x4);
	//printf("y1=%d,y2=%d,y3=%d,y4=%d i=%d\n", y1, y2, y3, y4,iPointNum);
}
void Reshape(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 4) {
			iPointNum = 1;
			x1 = xMouse;   y1 = winHeight - yMouse;
		}
		else if(iPointNum == 1){
			iPointNum = 2;
			x2 = xMouse;       y2 = winHeight - yMouse;
			glutPostRedisplay();
		}
		else if (iPointNum == 2) {
			iPointNum = 3;
			x3 = xMouse;       y3 = winHeight - yMouse;
			glutPostRedisplay();
		}
		else if (iPointNum == 3) {
			iPointNum = 4;
			x4 = xMouse;       y4 = winHeight - yMouse;
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
		if (iPointNum == 0 || iPointNum == 4) {
			iPointNum = 1;
			x1 = x;   y1 = winHeight - y;	

		}
		else if (iPointNum == 1) {
			iPointNum = 2;
			x2 = x;       y2 = winHeight - y;
			glutPostRedisplay();
		}
		else if (iPointNum == 2) {
			iPointNum = 3;
			x3 = x-200;       y3 = winHeight - y;
			glutPostRedisplay();
		}
		else if (iPointNum == 3) {
			iPointNum = 4;
			x4 = x-200;       y4 = winHeight - y;
			glutPostRedisplay();
		}
		break;
	default:break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("สตั้7");
	initial();
	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}