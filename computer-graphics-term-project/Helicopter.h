#pragma once
#include "GL/glew.h"
#include <cstdlib>
#include <iostream>

class Helicopter
{
	private:
		float increase_index = 0.06;
	public:
		int order;
		double x = 25, speed = 0.1;
		char direction;
		float color[3];
		float proppler_rotation = 0;

		Helicopter() {}

		Helicopter(int order) {
			this->order = order;
		}

		void generateHelicopter() {
			this->randomizeColor();
			this->speed = ((rand() % 2) + 1) * (0.05);
			
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

		void setSpeedIncreaseIndex(int difficulty_index) {
			// 0 easy 1 normal 2 hard
			switch (difficulty_index) {
				case 0:
					this->increase_index /= 2;
					break;
				case 2:
					this->increase_index *= 2;
					break;
			}
		}

		void increaseSpeed(float level) {
			this->speed += (level * 0.1 * (this->direction == 'r' ? 1 : -1)) * this->increase_index;
			std::cout << "Helicopter speeds increased : " << (level * 0.1 * (this->direction == 'r' ? 1 : -1)) * this->increase_index << std::endl;
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
				// Body
				glBegin(GL_QUADS);
				glVertex2f(this->x, 270 + (this->order * 50));
				glVertex2f(this->x + 20, 270 + (this->order * 50));
				glVertex2f(this->x + 20, 245 + (this->order * 50));
				glVertex2f(this->x, 245 + (this->order * 50));
				glEnd();

				// Glass
				glColor3f(0.6, 0.6, 0.7);
				glBegin(GL_POLYGON);
				glVertex2f(this->x + 20, 270 + (this->order * 50));
				glVertex2f(this->x + 20, 255 + (this->order * 50));
				glVertex2f(this->x + 16, 258 + (this->order * 50));
				glVertex2f(this->x + 12, 260 + (this->order * 50));
				glVertex2f(this->x + 8, 270 + (this->order * 50));
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
				glVertex2f(this->x, 260 + (this->order * 50));
				glVertex2f(this->x - 25, 260 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x + 10, 270 + (this->order * 50));
				glVertex2f(this->x + 10, 275 + (this->order * 50));
				glEnd();
				
				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
				glVertex2f(this->x + 25, 269 + (this->order * 50));
				glVertex2f(this->x - 5, 281 + (this->order * 50));
				glVertex2f(this->x + 25, 281 + (this->order * 50));
				glVertex2f(this->x - 5, 269 + +(this->order * 50));
				glEnd();

				// Helicopter Tail Propeller
				glBegin(GL_LINES);
				glVertex2f(this->x - 20, 264 + (this->order * 50));
				glVertex2f(this->x - 25, 256 + (this->order * 50));
				glVertex2f(this->x - 20, 256 + (this->order * 50));
				glVertex2f(this->x - 25, 264 + (this->order * 50));
				glEnd();

				this->x += this->speed;
				this->proppler_rotation += 0.3f;
			}
			else {
				// Body
				glBegin(GL_QUADS);
				glVertex2f(this->x, 270 + (this->order * 50));
				glVertex2f(this->x, 245 + (this->order * 50));
				glVertex2f(this->x - 20, 245 + (this->order * 50));
				glVertex2f(this->x - 20, 270 + (this->order * 50));
				glEnd();


				// Glass
				glColor3f(0.6, 0.6, 0.7);
				glBegin(GL_POLYGON);
				glVertex2f(this->x - 20, 270 + (this->order * 50));
				glVertex2f(this->x - 20, 255 + (this->order * 50));
				glVertex2f(this->x - 16, 258 + (this->order * 50));
				glVertex2f(this->x - 12, 260 + (this->order * 50));
				glVertex2f(this->x - 8, 270 + (this->order * 50));
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
				glVertex2f(this->x, 260 + (this->order * 50));
				glVertex2f(this->x + 25, 260 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(this->x - 10, 270 + (this->order * 50));
				glVertex2f(this->x - 10, 275 + (this->order * 50));
				glEnd();

				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
				glVertex2f(this->x + 5, 269 + (this->order * 50));
				glVertex2f(this->x - 25, 281 + (this->order * 50));
				glVertex2f(this->x + 5, 281 + (this->order * 50));
				glVertex2f(this->x - 25, 269 + +(this->order * 50));
				glEnd();

				// Helicopter Tail Propeller
				glBegin(GL_LINES);
				glVertex2f(this->x + 20, 264 + (this->order * 50));
				glVertex2f(this->x + 25, 256 + (this->order * 50));
				glVertex2f(this->x + 20, 256 + (this->order * 50));
				glVertex2f(this->x + 25, 264 + (this->order * 50));
				glEnd();

				this->x += this->speed;
			}
		}
};

