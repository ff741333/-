#include <GL/glut.h>

int flag = 2;
GLubyte chess[] = {
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
};
GLuint lineList;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	if (flag == 2) {
		glColor3f(0.0, 0.0, 0.0);
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonStipple(chess);
		glCallList(lineList);
		glRectf(50.0f, 100.0f, 150.0f, 50.0f);
		glDisable(GL_POLYGON_STIPPLE);
	}


	glLineWidth(12.0);
	glColor4f(0.0, 0.6, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(lineList);

	glFlush();
	glutSwapBuffers();
}


void Initial() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	lineList = glGenLists(1);
	glNewList(lineList, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(0.0f, 0.6f, 1.0f, 0.5f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor4f(1.0f, 0.6f, 1.0f, 0.5f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);

	glColor4f(1.0f, 0.6f, 0.0f, 0.5f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();
	glEndList();
}

void changeSize(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-2.5, 2.5, -3.0, 3.0 * (GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-2.5, 2.5 * (GLfloat)w / (GLfloat)h, -3.0, 3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayW() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(12.0);
	glColor4f(0.0, 0.6, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(lineList);
	glFlush();
}


void ProcessMenu(int value) {
	flag = value;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("实验4");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutCreateMenu(ProcessMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("线框", 1);
	glutAddMenuEntry("填充", 2);
	Initial();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("实验4（反走样）");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(displayW);
	Initial();

	glutMainLoop();
	return 0;
}


