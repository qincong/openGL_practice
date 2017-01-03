#include "glut.h"
#include "stdio.h"
#include "math.h"

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void) {
	
	GLfloat y;
	GLint factor = 3;
	GLushort pattern = 0x5555;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//glEnable(GL_LINE_STIPPLE);
	for (y = -90.0f; y < 90.0f; y += 20.0f) {
		glLineStipple(factor, pattern);
		glBegin(GL_LINES);
			glVertex2f(-80.0f, y);
			glVertex2f(80.0f, y);
		glEnd();
		factor++;
	}


	glPopMatrix();
	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat nRange = 100.0f;
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glEnable(GL_LINE_STIPPLE);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	SetupRC();
	glutMainLoop();
	return 0;
}