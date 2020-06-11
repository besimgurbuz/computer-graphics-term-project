#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include "Plane.h"
#include "Helicopter.h"
#include <string>
#include <math.h>

Plane plane = Plane(5);
Helicopter helicopters[4];
int isScored;
int menuStatus = 0;
int menuItemHover = 1;
bool gameStarted = false;

void displayMenu() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Title
	std::string str = gameStarted ? "Menu" : "Welcome to The Plane Game!";
	std::string& string = str;
	glColor3f(1, 0, 0);
	glRasterPos2d(gameStarted ? 225 : 150, 330);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
	glColor3f(0, 0, 0);

	// Sign
	str = "created by besimgurbuz";
	glRasterPos2d(0, 5);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);

	// Menu Usage
	str = "use UP and DOWN keys";
	glRasterPos2d(345, 20);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);
	str = "press ENTER for choose";
	glRasterPos2d(345, 5);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);

	// Play Button
	glColor3f(menuItemHover == 1 ? 0 : 1, menuItemHover == 1 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(200, 290);
	glVertex2i(200, 250);
	glVertex2i(280, 250);
	glVertex2i(280, 290);
	glEnd();
	str = gameStarted ? "Continue" : "Play";
	glColor3f(0, 0, 0);
	glRasterPos2d(gameStarted ? 212 : 228, 260);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	// Settings Button
	glColor3f(menuItemHover == 2 ? 0 : 1, menuItemHover == 2 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(200, 240);
	glVertex2i(200, 200);
	glVertex2i(280, 200);
	glVertex2i(280, 240);
	glEnd();
	str = "Settings";
	glColor3f(0, 0, 0);
	glRasterPos2d(215, 210);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	// Leaderboard Button
	glColor3f(menuItemHover == 3 ? 0 : 1, menuItemHover == 3 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(195, 190);
	glVertex2i(195, 150);
	glVertex2i(285, 150);
	glVertex2i(285, 190);
	glEnd();
	str = "Leaderboard";
	glColor3f(0, 0, 0);
	glRasterPos2d(202, 160);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);



	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

bool checkCrash() {
	for (int i = 0; i < 4; i++) {
		Helicopter target = helicopters[i];
		float distance = sqrt(pow(plane.y - (261 + target.order * 50), 2) + pow(plane.x - target.x, 2));
		if (distance < 50.0) {
			plane.health--;
			plane.randomizePosition();
		}
	}
	if (plane.health <= 0) {
		return true;
	}
	return false;
}

void displayGame() {
	glClear(GL_COLOR_BUFFER_BIT);
	bool crashResult = checkCrash();
	std::string str = "press ESC for menu";
	std::string& string = str;
	glColor3f(0, 0, 0);
	glRasterPos2d(368, 5);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);
	if (crashResult) {
		// game over text
		str = "Game Over!";
		glColor3f(1, 0, 0);
		glRasterPos2d(200, 260);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
		glColor3f(0, 0, 0);
		str = "your score: " + std::to_string(plane.score);
		glRasterPos2d(195, 220);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
		str = "press enter to play again";
		glRasterPos2d(180, 10);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[n]);
		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
	else {
		glColor3f(0, 0, 1);

		// Draw plane 50 x 50
		plane.draw();

		// Draw random helicopters
		for (int i = 0; i < 4; i++) {
			helicopters[i].draw();
		}

		// Status text
		str = "Score: " + std::to_string(plane.score);
		glColor3f(0, 0, 1);
		glRasterPos2d(410, 450);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[n]);
		str = "Health: " + std::to_string(plane.health);
		glRasterPos2d(410, 430);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[n]);

		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
}

void displaySettings() {

}

void displayLeaderboard() {

}

void mainDisplayer() {
	switch (menuStatus) {
		case 0:
			displayMenu();
			break;
		case 1:
			displayGame();
			break;
		case 2:
			displaySettings();
			break;
		case 3:
			displayLeaderboard();
			break;
	}
}

void gamePlayKeyEventsCallback(int key, int x, int y) {
	if (menuStatus == 0) {
		std::cout << "Key:: " << key << std::endl;
		switch (key) {
			case GLUT_KEY_UP:
				if (menuItemHover > 1) {
					menuItemHover--;
				}
				break;
			case GLUT_KEY_DOWN:
				if (menuItemHover < 3) {
					menuItemHover++;
				}
		}
	} 
	else if (menuStatus == 1 && plane.health > 0) {
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
			case 32:
				if (plane.health == 0) {
					plane.health = 3;
				}
				break;
		}

		if (isScored == 1) {
			for (int i = 0; i < 4; i++) {
				helicopters[i].generateHelicopter();
				helicopters[i].increaseSpeed(plane.score / 10);
			}
		}
	}
}

void gameControlKeyEventsCallback(unsigned char key, int x, int y) {
	int key_val = key;
	if (menuStatus == 0) {
		switch (key_val) {
			case 13:
				menuStatus = menuItemHover;
				if (menuStatus == 1)
					gameStarted = true;
				break;
		}

	}
	else if (menuStatus == 1) {
		switch (key_val) {
			case 13:
				// Enter Key
				if (plane.health == 0) {
					for (int i = 0; i < 4; i++) {
						helicopters[i].generateHelicopter();
					}
					plane.resetPlane();
				}
				break;
			case 27:
				// Esc Key
				menuStatus = 0;
				break;
		}
	}
	std::cout << "Key: " << key_val << std::endl;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Computer Graphics Term Project");

	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0.0, 480, 0.0, 480);

	plane.randomizePosition();
	for (int i = 0; i < 4; i++) {
		helicopters[i] = Helicopter(i);
		helicopters[i].generateHelicopter();
	}

	glutSpecialFunc(gamePlayKeyEventsCallback);
	glutKeyboardFunc(gameControlKeyEventsCallback);
	glutDisplayFunc(mainDisplayer);

	glutMainLoop();

	return 0;
}