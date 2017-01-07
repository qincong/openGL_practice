#include "glut.h"
#include "stdio.h"
#include "math.h"

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void RenderScene(void)
{
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -300.0f);

	glColor3ub(255, 255, 0);
	glDisable(GL_LIGHTING);
	glutSolidSphere(15.0f, 15, 15);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glColor3ub(0, 0, 255);
	glTranslatef(105.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 15, 15);

	glColor3ub(200, 200, 200);
	glTranslatef(30.0f, 0.0f, 0.0f);
	fMoonRot += 15.0f;
	if (fMoonRot > 360)
		fMoonRot = 0;
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	fEarthRot += 5.0f;
	if (fEarthRot > 360.0f)
		fEarthRot = 0;
	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat fAspect;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 1.0, 425.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(500, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}