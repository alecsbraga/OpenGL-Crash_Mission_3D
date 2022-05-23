#include <iostream>
#include <fstream>
#include<gl/freeglut.h>
#include<math.h>
#include "SOIL.h"

using namespace std;
// actual vector representing the camera's direction
float lx = 0.0000001f;
// XZ position of the camera
float x = 0.0f, zAdv = -50.0f, xAdv;
int parte;
bool over = false;
int score = 0;
bool changeScore = false;
int highscore;
int pct = 1000;
bool gameover = false;

bool inMenu = true;
bool inEndScreen = false;

float xs = -20.0, ys = 30.0, zs = 5.0, ts = 0.0;


void delay(float secs)
{
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}


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

	alphaDifuz = 0.3;
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
	if ((xAdv + 0.5f >= x && xAdv - 0.5 <= x) && zAdv > 4.0f)
	{
		over = true;
		

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


		float dificultate = 0.5f;

		if (zAdv >= -90.0f)
			zAdv = zAdv + dificultate;

		if (zAdv > 5.0f) {
			parte = rand() % 3;
			zAdv = -90.0f;
			score += 100;
			cout << "Score:  " << score << endl;
			changeScore = true;
		}

		if (score >= pct && pct <= 15000)
		{
			dificultate += 0.1;
			pct += 1000;
		}

		if (highscore < score) {
			highscore = score;
		}

	}
}

GLfloat coloareText[] = { 0.0, 0.0, 0.0 };


void RenderString(float x, float y,float z, void* font, const unsigned char* string)
{

	glPushAttrib(GL_CURRENT_BIT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, coloareText);
	glRasterPos3f(x, y, z);

	glutBitmapString(font, string);
	glPopAttrib();
}

void LoadTexture(void)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	unsigned char* image = SOIL_load_image("1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// SOIL_free_image_data(image);
	// glBindTexture(GL_TEXTURE_2D, 0);

}



void startMenu(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(x, 1.0f, 5.0f,
		x + lx, 1.0f, 4.0f,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	LoadTexture();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);glVertex3f(-2.5, -3.0, -0.1);
	glTexCoord2f(1.0, 0.0);glVertex3f(-2.5, 4.0, -0.1);
	glTexCoord2f(0.0, 0.0);glVertex3f(2.5, 4.0, -0.1);
	glTexCoord2f(0.0, 1.0);glVertex3f(2.5, -3.0, -0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, coloareText);
	glRasterPos3f(-0.5, 1.5, 0);
	char message[] = "Crashing mission!";
	for (int i = 0; i < strlen(message); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message[i]);

	glRasterPos3f(-1, 1.3, 0);
	char message2[] = "A game about cars, crashes and you!";
	for (int i = 0; i < strlen(message2); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message2[i]);


	glRasterPos3f(-0.75, 1.1, 0);
	char message3[] = "Press X to start the game";
	for (int i = 0; i < strlen(message3); i++) {
		glColor3f(0, 0, 0);
		if (message3[i] == 'X') {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
		}
		else glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
	}

	glutSwapBuffers();
}

void endScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(x, 1.0f, 5.0f,
		x + lx, 1.0f, 4.0f,
		0.0f, 1.0f, 0.0f);


	glColor3f(1.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, coloareText);

	glRasterPos3f(-1.55 + x, 1.9, 0);
	char message4[] = "You crashed, too bad";
	for (int i = 0; i < strlen(message4); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message4[i]);


	glRasterPos3f(-1.75 + x, 1.6, 0);
	char message3[] = "Press C to close the game";
	for (int i = 0; i < strlen(message3); i++) {
		if (message3[i] == 'X') {
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
		}
		else glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
	}


	glutSwapBuffers();
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

	char* text = new char[200];
	text = (char*)"Fereste-te de masini!";

	char scorText[10 + sizeof(char)];
	char highscoreText[10 + sizeof(char)];

	sprintf_s(scorText, "%d", score);
	sprintf_s(highscoreText, "%d", highscore);
	//cout << scorText;
	//strcat(text, scorText);

	RenderString(-0.5f + x, 2.9f, 0.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)text);

	RenderString(-2.0f + x, 2.90f, 0.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)"Scor: ");
	RenderString(-1.5f + x, 2.90f, 0.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)scorText);

	RenderString(-2.0f + x, 2.70f, 0.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)"Highscore: ");
	RenderString(-1.1f + x, 2.70f, 0.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)highscoreText);


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


	GLfloat liniieSoasea[] = { 1.0, 1.0, 1.0 };
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
	glTranslatef(xAdv, 0.95f, zAdv);

	//Draw corpul masinii
	glBegin(GL_POLYGON);

	GLfloat culoareMasina[] = { 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoareMasina);

	//FRONT
	glVertex3f(0.5, -0.25, 1.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.25, 1.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.25, 2.5);
	glVertex3f(0.5, -0.25, 1.5);
	glVertex3f(-0.5, -0.25, 1.5);
	glVertex3f(-0.5, -0.25, 2.5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(0.5, -0.25, 2.5);
	glVertex3f(-0.5, -0.25, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glEnd();

	//BACK
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	// RIGHT
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.25, 1.5);
	glVertex3f(0.5, -0.25, 2.5);
	glVertex3f(0.5, -0.5, 2.5);
	glEnd();

	//LEFT
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.25, 2.5);
	glVertex3f(-0.5, -0.25, 1.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//TOP
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//BOTTOM
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, 2.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glFlush();

	//Faruri
	GLfloat culoareFaruri[] = { 1.0, 1.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoareFaruri);
	glPushMatrix();
	glTranslatef(0.25, -0.3f, 2.5);
	glutSolidSphere(0.1f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25, -0.3f, 2.5);
	glutSolidSphere(0.1f, 50, 50);
	glPopMatrix();


	//Roti
	GLfloat culoareRoti[] = { 0.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoareRoti);
	glPushMatrix();
	glTranslatef(-0.5, -0.5f, 2.0);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5, -0.5f, -0.25);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -0.5f, 2.0);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, -0.5f, -0.25);
	glutSolidSphere(0.2f, 50, 50);
	glPopMatrix();


	//parbriz
	glBegin(GL_POLYGON);
	GLfloat culoareParbriz[] = { 0.0, 0.76, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, culoareParbriz);
	glVertex3f(0.4, -0.15, 1.5);
	glVertex3f(0.4, 0.47, 0.5);
	glVertex3f(-0.4, 0.47, 0.5);
	glVertex3f(-0.4, -0.15, 1.5);


	glEnd();

	glPopMatrix();


	if (over == true) {


		delay(1);

		inEndScreen = true;
		glutDisplayFunc(endScreen);
		if (gameover == false) {
			ofstream g("Highscore.txt");
			g << highscore;
			g.close();
			gameover = true;
			//exit(0);
		}
	}

	lumina();
	gameplay();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void keys(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		if (inMenu) {
			inMenu = false;
			glutDisplayFunc(renderScene);
		}
		break;
	case 'c':
		if (inEndScreen)
			exit(0);
		break;
	}
	glutPostRedisplay();
}



void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 1000000.0f;

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (!inMenu){
		x += lx * fraction;
		if (x > 2)
			x = 2;
		}
		break;
	case GLUT_KEY_LEFT:
		if (!inMenu) {
			x -= lx * fraction;
			if (x < -2)
				x = -2;
		}

	}
}

int main(int argc, char** argv) {

	// init GLUT and create window
	ifstream f("Highscore.txt");
	f >> highscore;
	f.close();
	cout << highscore;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Crash Mission");
	Initialize();
	// register callbacks
	glutDisplayFunc(startMenu);
	//glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(keys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
