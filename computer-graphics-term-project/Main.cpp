#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <list>
#include "Plane.h"
#include "Helicopter.h"

Plane plane = Plane();
Helicopter helicopters[4];
int isScored;
int menuStatus = 0;
int menuItemHover = 1;
bool gameStarted = false;
std::string username;
bool alertAboutUsername = false;

int settingsMenuItemHover = 1;
int selected_plane_color_index = 2;
int difficulty_index = 0.02;
// Color palette
int colors[5][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 0},
	{0, 1, 1}
};

int selected_difficulty_index = 1;
std::string difficulties[3] = {
	"Easy",
	"Normal",
	"Hard"
};

struct LBRecord {
	int rank;
	std::string username;
	int score;

	LBRecord() {}

	LBRecord(std::string username, int score) {
		this->username = username;
		this->score = score;
	}

	LBRecord(int rank, std::string username, int score) {
		this->rank = rank;
		this->username = username;
		this->score = score;
	}

	bool operator <(const LBRecord &other) const {
		return score > other.score;
	}
};

void displayMenu() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Title
	std::string str = gameStarted ? "Menu" : "Welcome to The Plane Game!";
	std::string& string = str;
	glColor3f(1, 0, 0);
	glRasterPos2d(gameStarted ? 215 : 130, 330);
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
	glRasterPos2d(300, 20);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);
	str = "press ENTER for choose";
	glRasterPos2d(300, 5);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);

	// Play Button
	glColor3f(menuItemHover == 1 ? 0 : 1, menuItemHover == 1 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(gameStarted ? 190 : 200, 290);
	glVertex2i(gameStarted ? 190 : 200, 250);
	glVertex2i(gameStarted ? 290 : 280, 250);
	glVertex2i(gameStarted ? 290 : 280, 290);
	glEnd();
	str = gameStarted ? "Continue" : "Play";
	glColor3f(0, 0, 0);
	glRasterPos2d(gameStarted ? 202 : 223, 265);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	// Settings Button
	glColor3f(menuItemHover == 2 ? 0 : 1, menuItemHover == 2 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(190, 240);
	glVertex2i(190, 200);
	glVertex2i(290, 200);
	glVertex2i(290, 240);
	glEnd();
	str = "Settings";
	glColor3f(0, 0, 0);
	glRasterPos2d(205, 215);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	// Leaderboard Button
	glColor3f(menuItemHover == 3 ? 0 : 1, menuItemHover == 3 ? 0 : 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(180, 190);
	glVertex2i(180, 150);
	glVertex2i(300, 150);
	glVertex2i(300, 190);
	glEnd();
	str = "Leaderboard";
	glColor3f(0, 0, 0);
	glRasterPos2d(188, 165);
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

std::list<LBRecord> getLBRecords() {
	using namespace std;

	list<LBRecord> records;
	string line;
	ifstream readLeaderboardFile;
	readLeaderboardFile.open("./leaderboard.txt");


	while (getline(readLeaderboardFile, line)) {
		int rank;
		string username;
		int score;
		int recordindex = 0;

		string word;
		istringstream iss(line, istringstream::in);
		int wordindex = 0;

		while (iss >> word) {
			// int_rank string_username int_score
			if (wordindex == 0) {
				rank = stoi(word);
			}
			if (wordindex == 1) {
				username = word;
			}
			if (wordindex == 2) {
				score = stoi(word);
			}
			wordindex++;
		}
		records.push_back(LBRecord(rank, username, score));
	}
	return records;
}

void updateLeaderboard() {
	using namespace std;
	if (plane.score > 0) {
		ifstream readLeaderboardFile;
		ofstream writeLeaderboardFile;

		readLeaderboardFile.open("./leaderboard.txt");
		if (readLeaderboardFile.peek() == ifstream::traits_type::eof()) {
			// file is empty
			writeLeaderboardFile.open("./leaderboard.txt");
			writeLeaderboardFile << "1 " + username + " " + to_string(plane.score);
		}
		else {
			list<LBRecord> records = getLBRecords();
			records.push_back(LBRecord(username, plane.score));
			records.sort();
			if (records.size() > 10) {
				records.pop_back();
			}
			list<LBRecord>::iterator it;
			int rankindex = 1;
			writeLeaderboardFile.open("./leaderboard.txt");
			for (it = records.begin(); it != records.end(); ++it) {
				writeLeaderboardFile << to_string(rankindex) << " " << it->username << " " << it->score << endl;
				cout << "Username -> " << it->username << " Score -> " << it->score << endl;
				rankindex++;
			}
			writeLeaderboardFile.close();
		}

		readLeaderboardFile.close();
		writeLeaderboardFile.close();
	}
}

void displayGame() {
	glClear(GL_COLOR_BUFFER_BIT);
	bool crashResult = checkCrash();
	std::string str = "";
	std::string& string = str;
	if (crashResult) {
		// game over text
		str = "Game Over!";
		glColor3f(1, 0, 0);
		glRasterPos2d(200, 260);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
		glColor3f(0, 0, 0);
		str = username + "'s score: " + std::to_string(plane.score);
		glRasterPos2d(187, 220);
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

		// Username text
		glColor3f(1, 0, 1);
		glRasterPos2d(5, 470);
		for (int n = 0; n < username.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, username[n]);

		// Status text
		str = "Score: " + std::to_string(plane.score);
		glColor3f(0, 0, 1);
		glRasterPos2d(380, 470);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[n]);
		str = "Health: " + std::to_string(plane.health);
		glRasterPos2d(380, 450);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[n]);

		str = "press ESC for menu";
		glColor3f(0, 0, 0);
		glRasterPos2d(330, 5);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);

		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
}

void displaySettings() {
	glClear(GL_COLOR_BUFFER_BIT);

	std::string str;
	std::string& string = str;

	// Title
	str = "Settings";
	glColor3f(1, 0, 0);
	glRasterPos2d(215, 330);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);


	// Plane Color
	glColor3f(0, 0, 0);
	glLineWidth(2.0f);
	str = "Plane's color: ";
	glRasterPos2d(150, 280);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	glColor3f(colors[selected_plane_color_index][0], colors[selected_plane_color_index][1], colors[selected_plane_color_index][2]);
	glBegin(GL_QUADS);
	glVertex2f(280, 295);
	glVertex2f(330, 295);
	glVertex2f(330, 275);
	glVertex2f(280, 275);
	glEnd();
	
	glColor3f(1, settingsMenuItemHover == 1 ? 0 : 1, settingsMenuItemHover == 1 ? 0 : 1);
	glBegin(GL_LINES);
	glVertex2f(150, 270);
	glVertex2f(330, 270);
	glEnd();

	// Difficulty
	glColor3f(0, 0, 0);
	str = "Difficulty : \t" + difficulties[selected_difficulty_index];
	glRasterPos2d(160, 240);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	glColor3f(1, settingsMenuItemHover == 2 ? 0 : 1, settingsMenuItemHover == 2 ? 0 : 1);
	glBegin(GL_LINES);
	glVertex2f(160, 230);
	glVertex2f(310, 230);
	glEnd();

	glColor3f(0, 0, 0);
	str = "Press ESC to return";
	glRasterPos2d(200, 30);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[n]);

	// Settings Usage
	str = "use UP and DOWN keys";
	glRasterPos2d(170, 20);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);
	str = "press ENTER to change setting";
	glRasterPos2d(150, 10);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[n]);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void displayLeaderboard() {
	glClear(GL_COLOR_BUFFER_BIT);

	std::list<LBRecord> records = getLBRecords();

	std::list<LBRecord>::iterator it;
	int recordindex = 0;

	std::string str;
	std::string& string = str;

	// Title
	str = "Leaderboard";
	glColor3f(1, 0, 0);
	glRasterPos2d(190, 330);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	str = "#rank\t\t\tusername\t\t\tscore";
	glRasterPos2d(145, 300);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);

	glColor3f(0, 0, 0);
	for (it = records.begin(); it != records.end(); ++it) {
		str = "#" + std::to_string(recordindex + 1) + "\t\t\t\t\t" + it->username + "\t\t\t\t\t" + std::to_string(it->score);
		glRasterPos2d(175, 270 - (recordindex) * 20);
		for (int n = 0; n < string.size(); n++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
		recordindex++;
	}

	glColor3f(1, 0, 0);
	str = "Press ESC to return";
	glRasterPos2d(200, 10);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[n]);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void displayGetUsername() {
	glClear(GL_COLOR_BUFFER_BIT);

	std::string str = "Type your username:";
	std::string& string = str;
	glColor3f(1, 0, 0);
	glRasterPos2d(150, 240);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
	str = username.size() != 0 ? username : "________";
	glColor3f(0, 0, 0);
	glRasterPos2d(205, 215);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);


	glColor3f(1, 0, 0);
	str = alertAboutUsername ? "username cannot be empty" : "username can contain up to 8 characters";
	glRasterPos2d(alertAboutUsername ? 170 : 120, 10);
	for (int n = 0; n < string.size(); n++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[n]);

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
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
		case 10:
			// Get username
			displayGetUsername();
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
	else if (menuStatus == 2) {
		switch (key) {
		case GLUT_KEY_UP:
			if (settingsMenuItemHover > 1) {
				settingsMenuItemHover--;
			}
			break;
		case GLUT_KEY_DOWN:
			if (settingsMenuItemHover < 2) {
				settingsMenuItemHover++;
			}
		}
	}

}

void gameControlKeyEventsCallback(unsigned char key, int x, int y) {
	int key_val = key;
	if (menuStatus == 0) {
		switch (key_val) {
			case 13:
				if (menuItemHover == 1 && !gameStarted) {
					menuStatus = 10;
				}
				else {
					menuStatus = menuItemHover;
					if (menuStatus == 1)
						gameStarted = true;
				}
				break;
		}

	}
	else if (menuStatus == 1) {
		switch (key_val) {
			case 13:
				// Enter Key
				if (plane.health == 0) {
					updateLeaderboard();
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
	else if (menuStatus == 2) {
		switch (key_val) {
			case 13:
				if (settingsMenuItemHover == 1) {
					// change color
					if (selected_plane_color_index == 4) {
						selected_plane_color_index = 0;
					}
					else if (selected_plane_color_index >= 0) {
						selected_plane_color_index++;
					}
					plane.setColor(colors[selected_plane_color_index][0], colors[selected_plane_color_index][1], colors[selected_plane_color_index][2]);
				}
				else if (settingsMenuItemHover == 2) {
					if (selected_difficulty_index == 2) {
						selected_difficulty_index = 0;
					}
					else if (selected_difficulty_index >= 0) {
						selected_difficulty_index++;
					}
					for (int i = 0; i < 4; i++)
						helicopters[i].setSpeedIncreaseIndex(selected_difficulty_index);
				}
				break;
			case 27:
				menuStatus = 0;
				break;
		}
	}
	else if (menuStatus == 3) {
		// Leaderboard or Settings page
		switch (key_val) {
			case 27:
				// Esc Key
				menuStatus = 0;
				break;
		}
	}
	else if (menuStatus == 10) {
		// username defining
		switch (key_val) {
			case 8:
				if (username.size() > 0)
					username.pop_back();
				break;
			case 13:
				if (username.size() > 0 && username.find_first_not_of(' ') != std::string::npos) {
					menuStatus = 1;
					gameStarted = true;
				}
				else {
					alertAboutUsername = true;
				}
				break;
			case 27:
				menuStatus = 0;
				break;
			default:
				alertAboutUsername = false;
				if (username.size() < 8)
					username += key;
				break;
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(480, 640);
	glutCreateWindow("Computer Graphics Term Project - Besim Gürbüz");

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