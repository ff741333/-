#include <cstdlib>  
#include <cmath>
#include <windows.h>
#include <gl/glut.h>

const int MAX_CHAR = 128;
const float PI = 3.1415926;
const double eyeX = 4.0 / 7, eyeY = 5.0 / 7, eyeZ = 3.0 / 7;

enum ENUM_MOEDELnVIEW {
	SPHERE, CONE, CUBE, TORUS, DODECAHEDRON,
	TEAPOT, OCTAHEDRON, TETRAHEDRON, ICOSAHEDRON,
	FRONT, SIDE, VERTICAL, PERSPECTIVE
};
GLsizei iMode = 1;
GLsizei winWidth = 1000, winHeight = 800;
float rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f;
float l = 13.0f, zoom = 1.0f;
GLint iModel = SPHERE;
GLuint cord;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	cord = glGenLists(2);
	glNewList(cord, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-l, 0.0f, 0.0f);
	glVertex3f(l, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -l, 0.0f);
	glVertex3f(0.0f, l, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -l);
	glVertex3f(0.0f, 0.0f, l);
	glEnd();
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(l, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(0.2, 0.4, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, l, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.2, 0.4, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, l);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCone(0.2, 0.4, 20, 20);
	glPopMatrix();
	glEndList();
}
//按x,y,z为起始位置，显示字符串str
void drawString(const char* str, GLfloat x, GLfloat y, GLfloat z)
{
	GLuint lists;
	lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	glListBase(lists);
	glRasterPos3f(x, y, z);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	glDeleteLists(lists, MAX_CHAR);
}

void label(GLfloat l)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	//drawString("O", 0.0f, 0.0f, 0.0f);
	drawString("x", l + 0.5f, 0.0f, 0.0f);
	drawString("y", 0.0f, l + 0.5f, 0.0f);
	drawString("z", 0.0f, 0.0f, l + 0.5f);
}

void onDraw(int mode)
{
	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	int w = vp[2], h = vp[3];
	float x = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float scale = 15.0f;

	switch (mode)
	{
	case FRONT:
		if (x <= 1) glOrtho(-scale, scale, -scale / x, scale / x, -scale, scale * 2);
		else glOrtho(-scale * x, scale * x, -scale, scale, -scale, scale * 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0f, scale + 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		drawString("Front", l, 0.0f, l);
		break;
	case VERTICAL:
		if (x <= 1) glOrtho(-scale, scale, -scale / x, scale / x, -scale, scale * 2);
		else glOrtho(-scale * x, scale * x, -scale, scale, -scale * 2, scale * 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, scale + 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
		drawString("Vertical", l, -l, 0.0f);
		break;
	case SIDE:
		if (x <= 1) glOrtho(-scale, scale, -scale / x, scale / x, -scale, scale * 2);
		else glOrtho(-scale * x, scale * x, -scale, scale, -scale, scale * 2);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(scale + 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		drawString("Side", 0.0f, -l, l);
		break;
	case PERSPECTIVE:
		gluPerspective(30.0f, (float)w / h, 0.1f, 300.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(scale * 2, scale * 2, scale * 2, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		drawString("Perspective", l * 1.1, 0.0f, l * 1.3);
	}
	glPushMatrix();
	glCallList(cord);
	label(l);

	glPushMatrix();
	glRotatef(rotateX, -1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
	/*glRotatef(rotateY, 0.0f, -sin(rotateX), cos(rotateX));
	glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);*/
	glScalef(zoom, zoom, zoom);

	switch (iModel) {
	case SPHERE: glutWireSphere(8.0f, 20, 20); break;
	case CONE: glutWireCone(4.0f, 8.0f, 20, 20); break;
	case TORUS: glutWireTorus(3.0f, 6.0f, 20, 20); break;
	case TEAPOT: glutWireTeapot(8.0f); break;
	case CUBE: glutWireCube(8.0f); break;
	case TETRAHEDRON:
		glScalef(6.0f, 6.0f, 6.0f);
		glutWireTetrahedron();
		break;
	case OCTAHEDRON:
		glScalef(6.0f, 6.0f, 6.0f);
		glutWireOctahedron();
		break;
	case ICOSAHEDRON:
		glScalef(6.0f, 6.0f, 6.0f);
		glutWireIcosahedron();
		break;
	case DODECAHEDRON:
		glScalef(6.0f, 6.0f, 6.0f);
		glutWireDodecahedron();
		break;
	}
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, winHeight / 2, winWidth / 2, winHeight / 2);
	onDraw(FRONT);
	glViewport(winWidth / 2, winHeight / 2, winWidth / 2, winHeight / 2);
	onDraw(VERTICAL);
	glViewport(0, 0, winWidth / 2, winHeight / 2);
	onDraw(SIDE);
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight / 2);
	onDraw(PERSPECTIVE);
	glFlush();
}

void reshape(GLsizei w, GLsizei h)
{
	winWidth = w;
	winHeight = h;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotateY += 5.0f;
		if (rotateY >= 360.0f)
			rotateY -= 360.0f;
		break;
	case GLUT_KEY_DOWN:
		rotateY -= 5.0f;
		if (rotateY < 0.0f)
			rotateY += 360.0f;
		break;
	case GLUT_KEY_LEFT:
		rotateZ += 5.0f;
		if (rotateZ >= 360.0f)
			rotateZ -= 360.0f;
		break;
	case GLUT_KEY_RIGHT:
		rotateZ -= 5.0f;
		if (rotateZ < 0.0f)
			rotateZ += 360.0f;
		break;
	case GLUT_KEY_PAGE_UP:
		rotateX += 5.0f;
		if (rotateX >= 360.0f)
			rotateX -= 360.0f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		rotateX -= 5.0f;
		if (rotateX < 0.0f)
			rotateX += 360.0f;
		break;
	}
	glutPostRedisplay();
}

void mousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (action == GLUT_UP)
		zoom += 0.01f;
	else if (action == GLUT_UP)
		zoom -= 0.01f;
	glutPostRedisplay();
}

void processMenu(int value)
{
	switch (value)
	{
	case 1:	iModel = SPHERE; break;
	case 2:	iModel = CONE; break;
	case 3:	iModel = TORUS; break;
	case 4:	iModel = TEAPOT; break;
	case 5:	iModel = CUBE; break;
	case 6:	iModel = TETRAHEDRON; break;
	case 7:	iModel = OCTAHEDRON; break;
	case 8:	iModel = ICOSAHEDRON; break;
	case 9:	iModel = DODECAHEDRON; break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 16);
	glutCreateWindow("实验4");

	int nModelMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("球体", 1);
	glutAddMenuEntry("圆锥", 2);
	glutAddMenuEntry("圆环", 3);
	glutAddMenuEntry("茶壶", 4);
	glutAddMenuEntry("立方体", 5);
	glutAddMenuEntry("正四面体", 6);
	glutAddMenuEntry("正八面体", 7);
	glutAddMenuEntry("正十二面体", 8);
	glutAddMenuEntry("正十六面体", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousePlot);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}