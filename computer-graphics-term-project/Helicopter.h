#pragma once
#include "GL/glew.h"
#include <cstdlib>
#include <iostream>

class Helicopter
{
	public:
		int order;
		double x = 25, speed = 0.1;
		char direction;
		float color[3];

		Helicopter() {}

		Helicopter(int order) {
			this->order = order;
		}

		void generateHelicopter() {
			this->randomizeColor();
			this->speed = ((rand() % 2) + 1) * 0.05;
			
			char directions[2] = { 'r', 'l' };
			int direction_index = (rand() % 2);
			this->direction = directions[direction_index];

			if (this->direction == 'l') {
				this->speed = this->speed * -1;
				this->x = 455;
			}
		}

		void randomizeColor() {
			for (int i = 0; i < 3; i++) {
				this->color[i] = ((double)rand() / (RAND_MAX));
			}
		}

		void increaseSpeed(int increaseDegree) {
			this->speed += (((this->speed * increaseDegree) * 5) / 100);
		}

		void draw() {
			glColor3f(this->color[0], this->color[1], this->color[2]);

			if ((int) this->x == 25 && this->direction == 'l') {
				this->direction = 'r';
				this->speed = this->speed * -1;
			}
			else if ((int) this->x == 455 && this->direction == 'r') {
				this->direction = 'l';
				this->speed = this->speed * -1;
			}

			if (this->direction == 'r') {
				glBegin(GL_QUADS);
				glVertex2f(this->x, 265 + (this->order * 50));
				glVertex2f(this->x + 20, 265 + (this->order * 50));
				glVertex2f(this->x + 20, 245 + (this->order * 50));
				glVertex2f(this->x, 245 + (this->order * 50));
				glEnd();

				// Glass
				glColor3f(0.6, 0.6, 0.7);
				glBegin(GL_QUADS);
				glVertex2f(this->x + 10, 265 + (this->order * 50));
				glVertex2f(this->x + 20, 265 + (this->order * 50));
				glVertex2f(this->x + 20, 255 + (this->order * 50));
				glVertex2f(this->x + 10, 255 + (this->order * 50));
				glEnd();

				glColor3f(this->color[0], this->color[1], this->color[2]);

				// Helicopter Foot
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x + 5, 245 + (this->order * 50));
				glVertex2f(this->x + 5, 240 + (this->order * 50));

				glVertex2f(this->x + 15, 245 + (this->order * 50));
				glVertex2f(this->x + 15, 240 + (this->order * 50));

				glVertex2f(this->x, 240 + (this->order * 50));
				glVertex2f(this->x + 20, 240 + (this->order * 50));
				glEnd();

				// Helicopter Tail
				glLineWidth(4.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x, 255 + (this->order * 50));
				glVertex2f(this->x - 25, 255 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x + 10, 265 + (this->order * 50));
				glVertex2f(this->x + 10, 270 + (this->order * 50));
				
				glColor3f(0, 0, 0);
				glVertex2f(this->x + 25, 264 + (this->order * 50));
				glVertex2f(this->x - 5, 276 + (this->order * 50));
				glVertex2f(this->x + 25, 276 + (this->order * 50));
				glVertex2f(this->x - 5, 264 + +(this->order * 50));
				glEnd();

				// Helicopter Tail Propeller
				glBegin(GL_LINES);
				glVertex2f(this->x - 20, 259 + (this->order * 50));
				glVertex2f(this->x - 25, 251 + (this->order * 50));
				glVertex2f(this->x - 20, 251 + (this->order * 50));
				glVertex2f(this->x - 25, 259 + (this->order * 50));
				glEnd();

				this->x += this->speed;
			}
			else {
				glBegin(GL_QUADS);
				glVertex2f(this->x, 265 + (this->order * 50));
				glVertex2f(this->x, 245 + (this->order * 50));
				glVertex2f(this->x - 20, 245 + (this->order * 50));
				glVertex2f(this->x - 20, 265 + (this->order * 50));
				glEnd();


				// Glass
				glColor3f(0.6, 0.6, 0.7);
				glBegin(GL_QUADS);
				glVertex2f(this->x - 10, 265 + (this->order * 50));
				glVertex2f(this->x - 10, 255 + (this->order * 50));
				glVertex2f(this->x - 20, 255 + (this->order * 50));
				glVertex2f(this->x - 20, 265 + (this->order * 50));
				glEnd();

				glColor3f(this->color[0], this->color[1], this->color[2]);

				// Helicopter Foot
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x - 5, 245 + (this->order * 50));
				glVertex2f(this->x - 5, 240 + (this->order * 50));

				glVertex2f(this->x - 15, 245 + (this->order * 50));
				glVertex2f(this->x - 15, 240 + (this->order * 50));

				glVertex2f(this->x, 240 + (this->order * 50));
				glVertex2f(this->x - 20, 240 + (this->order * 50));
				glEnd();

				// Helicopter Tail
				glLineWidth(4.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x, 255 + (this->order * 50));
				glVertex2f(this->x + 25, 255 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x - 10, 265 + (this->order * 50));
				glVertex2f(this->x - 10, 270 + (this->order * 50));

				glColor3f(0, 0, 0);
				glVertex2f(this->x + 5, 264 + (this->order * 50));
				glVertex2f(this->x - 25, 276 + (this->order * 50));
				glVertex2f(this->x + 5, 276 + (this->order * 50));
				glVertex2f(this->x - 25, 264 + +(this->order * 50));
				glEnd();

				// Helicopter Tail Propeller
				glBegin(GL_LINES);
				glVertex2f(this->x + 20, 259 + (this->order * 50));
				glVertex2f(this->x + 25, 251 + (this->order * 50));
				glVertex2f(this->x + 20, 251 + (this->order * 50));
				glVertex2f(this->x + 25, 259 + (this->order * 50));
				glEnd();

				this->x += this->speed;
			}
		}
};

