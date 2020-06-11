#pragma once
#include "GL/glew.h"
#include <cstdlib>
#include <iostream>

class Plane
{
	public:
		double x = 0, y = 0, velocity;
		int score = 0, health = 3;

		Plane(double velocity) {
			this->velocity = velocity;
		}

		void randomizePosition() {
			this->y = (rand() % 190) + 25;
			this->x = (rand() % 430) + 25;
			std::cout << "Planes position => x = " << this->x << " y = " << this->y << std::endl;
		}

		int move(bool axis_x, bool axis_y, char direction) {
			if (axis_x && !axis_y) {
				if (direction == 'r' && (int) this->x < 455)
					this->x += this->velocity;
				else if (direction == 'l' && (int) this->x > 25)
					this->x -= this->velocity;
			}
			else if (axis_y && !axis_x) {
				if (direction == 'u')
					this->y += this->velocity;
				else if (direction == 'd')
					this->y -= this->velocity;
				if ((int)this->y >= 480) {
					this->score += 10;
					std::cout << "SCORE:: " << this->score << std::endl;
					this->randomizePosition();
					return 1;
				}
			}
			return 0;
		}

		void draw() {
			glColor3f(0, 0, 1);
			glLineWidth(5.0f);

			glBegin(GL_LINES);
			// Plane Body
			glVertex2f(this->x, this->y + 25);
			glVertex2f(this->x, this->y - 25);
			// Plane Wing
			glVertex2f(this->x - 25, this->y + 15);
			glVertex2f(this->x + 25, this->y + 15);
			// Plane Tail
			glVertex2f(this->x + 12.5, this->y - 15);
			glVertex2f(this->x - 12.5, this->y - 15);
			glEnd();
		}

		void resetPlane() {
			this->health = 3;
			this->score = 0;
			this->randomizePosition();
		}
};

