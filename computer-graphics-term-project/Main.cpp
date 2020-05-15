#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include "Plane.h";
#include "Helicopter.h";
#include <string>

Plane plane = Plane(5);
Helicopter helicopters[4];
int isScored;
bool menuOpened = true;

void displayMenu() {
	std::string str = "TEST TEST TEST";
	std::string& string = str;
	glColor3f(1, 0, 0);
	glRasterPos2d(240, 240);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void menuKeyEventsCallback(int key, int x, int y) {
}

void displayGame() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	
	// Draw plane 50 x 50
	plane.draw();

	// Draw random helicopters
	for (int i = 0; i < 4; i++) {
		helicopters[i].draw();
	}

	std::string str = "Score: " + std::to_string(plane.score) + " Health: " + std::to_string(plane.health);
	std::string &string = str;
	glColor3f(1, 0, 0);
	glRasterPos2d(350, 450);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void keyEventsCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			isScored = plane.move(false, true, 'u');
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			plane.move(false, true, 'd');
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			plane.move(true, false, 'r');
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			plane.move(true, false, 'l');
			glutPostRedisplay();
			break;
	}
	if (isScored == 1) {
		for (int i = 0; i < 4; i++) {
			helicopters[i].generateHelicopter();
			helicopters[i].increaseSpeed(plane.score / 10);
			plane.velocity += (plane.velocity * 0.01);
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Computer Graphics Term Project - Besim Gurbuz");

	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0.0, 480, 0.0, 480);

	/*while (menuOpened) {
		int devam;
		glutSpecialFunc(menuKeyEventsCallback);
		glutDisplayFunc(displayMenu);
		glutMainLoop();
	}*/

	plane.randomizePosition();
	for (int i = 0; i < 4; i++) {
		helicopters[i] = Helicopter(i);
		helicopters[i].generateHelicopter();
	}

	glutSpecialFunc(keyEventsCallback);
	glutDisplayFunc(displayGame);

	glutMainLoop();

	return 0;
}