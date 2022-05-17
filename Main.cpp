#include <iostream>
#include <fstream>
#include<gl/freeglut.h>
#include<math.h>

using namespace std;
// actual vector representing the camera's direction
float lx = 0.0000001f;
// XZ position of the camera
float x = 0.0f, zAdv = -50.0f , xAdv;
int parte;
bool over = false;


float xs = -20.0, ys = 30.0, zs = 5.0, ts = 0.0;





void Initialize()
{

	glClearColor(0.67, 0.84, 0.89, 0.0);

}
void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void lumina()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	// initializari si proprietatile universale
	GLfloat alphaAmb = 1.0;
	GLfloat alphaDifuz = 1.0;
	GLfloat difuzLumina[4];
	GLfloat unghiCutOff = 180.0;

	ts = 0.0;

	alphaAmb = 1;

	alphaDifuz = 0.2;
	difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;

	unghiCutOff = 180;

	// Sursa de lumina
	GLfloat ambientLumina[] = { alphaAmb, alphaAmb, alphaAmb, alphaAmb };
	GLfloat pozitial0[] = { xs, ys, zs, ts };
	GLfloat directieSpot[] = { 0, 0, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLumina);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuzLumina);

	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, directieSpot);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, unghiCutOff);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 3.0);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

};



void Copaci() {

	//Trunchi
	GLfloat maro[] = { 0.5f, 0.3f, 0.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, maro);
	GLUquadricObj* cylinder;
	glPushMatrix();
	glTranslatef(0, 0.5, 0.0);
	glRotated(270, 0.5, 0, 0);
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.25, 0.25, 2.0, 15, 7.5);
	glPopMatrix();


	GLfloat verde[] = { 0, 0.5, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, verde);
	// Draw Body
	glTranslatef(0.0f, 2.27f, 0.0f);
	glutSolidSphere(0.75f, 25, 25);

}

void gameplay() {

	//cout << over;
	if ((xAdv+0.5f >= x && xAdv - 0.5 <= x) && zAdv > 4.0f)
	{
		over = true;
		exit(0);

	}
	else {
		switch (parte)
		{
		case 0:
			xAdv = 0.0f;
			break;
		case 1:
			xAdv = -2.0f;
			break;
		case 2:
			xAdv = 2.0f;
			break;
		}


		float dificultate = 0.1f;

		if (zAdv >= -90.0f)
			zAdv = zAdv + dificultate;

		if (zAdv > 5.0f) {
			parte = rand() % 3;
			zAdv = -90.0f;
		}
	}
}



void renderScene(void) {

	// Clear Color and Depth Buffers

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, 5.0f,
		x + lx, 1.0f, 4.0f,
		0.0f, 1.0f, 0.0f);

	// Draw iarba
	GLfloat coloareIarba[] = { 0.0, 0.3, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, coloareIarba);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	//Draw sosea

	GLfloat coloareSoasea[] = { 0.01, 0.01, 0.01 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, coloareSoasea);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.2f, -100.0f);
	glVertex3f(-3.0f, 0.2f, 100.0f);
	glVertex3f(3.0f, 0.2f, 100.0f);
	glVertex3f(3.0f, 0.2f, -100.0f);
	glEnd();

	//Draw linii-sosea


	GLfloat liniieSoasea[] = {1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, liniieSoasea);
	glBegin(GL_QUADS);
	glVertex3f(-3.0f, 0.21f, -100.0f);
	glVertex3f(-3.0f, 0.21f, 100.0f);
	glVertex3f(-2.9f, 0.21f, 100.0f);
	glVertex3f(-2.9f, 0.21f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(3.0f, 0.21f, -100.0f);
	glVertex3f(3.0f, 0.21f, 100.0f);
	glVertex3f(2.9f, 0.21f, 100.0f);
	glVertex3f(2.9f, 0.21f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 0.21f, -100.0f);
	glVertex3f(-1.0f, 0.21f, 100.0f);
	glVertex3f(-0.9f, 0.21f, 100.0f);
	glVertex3f(-0.9f, 0.21f, -100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.0f, 0.21f, -100.0f);
	glVertex3f(1.0f, 0.21f, 100.0f);
	glVertex3f(0.9f, 0.21f, 100.0f);
	glVertex3f(0.9f, 0.21f, -100.0f);
	glEnd();


	// Draw copaci

	for (int j = -50; j < 1; j++) {
		glPushMatrix();
		glTranslatef(-3.3, -0.3, 100 + zAdv + j * 5.0);
		Copaci();
		glPopMatrix();
	}
	for (int j = -50; j < 1; j++) {
		glPushMatrix();
		glTranslatef(3.3, -0.3, 100 + zAdv + j * 5.0);
		Copaci();
		glPopMatrix();
	}

	//Draw adversar

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(xAdv, 0.75f, zAdv);
	glutSolidSphere(0.5f, 50, 50);
	glEnd();

	glPopMatrix();

	lumina();
	gameplay();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}



void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 1000000.0f;

	switch (key) {
	case GLUT_KEY_RIGHT:
		x += lx * fraction;
		if (x > 2)
			x = 2;

		break;
	case GLUT_KEY_LEFT:
		x -= lx * fraction;
		if (x < -2)
			x = -2;

	}
}

int main(int argc, char** argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Crash Mission");
	Initialize();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
