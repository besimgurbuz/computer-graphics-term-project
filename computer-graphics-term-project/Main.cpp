#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include "Plane.h";

Plane plane = Plane(5);


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(240, 320);
	glVertex2f(240, 120);
	glVertex2f(479, 639);
	glEnd();

	// Draw plane 50 x 50
	plane.draw();

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void keyEventsCallback(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			plane.move(false, true, 'u');
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
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Computer Graphics Term Project - Besim Gurbuz");

	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0.0, 480, 0.0, 640);
	glutSpecialFunc(keyEventsCallback);

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}