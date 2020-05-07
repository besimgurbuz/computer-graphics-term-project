#pragma once
#include "glew.h"

class Plane
{
	public:
		int x = 0, y = 0, velocity;

		Plane(int velocity) {
			this->velocity = velocity;
		}

		void move(bool axis_x, bool axis_y, char direction) {
			if (axis_x && !axis_y) {
				if (direction == 'r')
					this->x += this->velocity;
				else if (direction == 'l')
					this->x -= this->velocity;
			}
			else if (axis_y && !axis_x) {
				if (direction == 'u')
					this->y += this->velocity;
				else if (direction == 'd')
					this->y -= this->velocity;
			}
		}

		void draw() {
			glColor3f(0, 0, 1);
			glLineWidth(5.0f);

			glBegin(GL_LINES);
			// Plane Body
			glVertex2f(240 + this->x, 145 + this->y);
			glVertex2f(240 + this->x, 95 + this->y);
			// Plane Wing
			glVertex2f(215 + this->x, 130 + this->y);
			glVertex2f(265 + this->x, 130 + this->y);
			// Plane Tail
			glVertex2f(227.5 + this->x, 105 + this->y);
			glVertex2f(252.5 + this->x, 105 + this->y);
			glEnd();
		}
};

