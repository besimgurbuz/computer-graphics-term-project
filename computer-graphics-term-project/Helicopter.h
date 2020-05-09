#pragma once
#include "GL/glew.h"
#include <cstdlib>
#include <iostream>

class Helicopter
{
	public:
		int speed, order;
		char direction;
		float color[3];

		Helicopter() {}

		Helicopter(int order) {
			this->order = order;
		}

		void generateHelicopter() {
			this->randomizeColor();
			this->speed = (rand() % 5) + 5;
			
			char directions[2] = { 'r', 'l' };
			int direction_index = (rand() % 2);
			this->direction = directions[direction_index];
 			std::cout << "Speed: " << this->speed << std::endl << "Direction is " << directions[direction_index] << " index is " << direction_index;
			std::cout << std::endl << (rand() / RAND_MAX);
			
		}

		void randomizeColor() {
			for (int i = 0; i < 3; i++) {
				this->color[i] = ((double)rand() / (RAND_MAX));
			}
			std::cout << "ORDER IS " << this->order << std::endl;
			std::cout << this->color[0] << std::endl << this->color[1] << std::endl << this->color[2];
		}

		void draw() {
			glColor3f(this->color[0], this->color[1], this->color[2]);
			// Helicopter Body
			if (this->direction == 'l') {
				glBegin(GL_QUADS);
				glVertex2f(30, 265 + (this->order * 50));
				glVertex2f(50, 265 + (this->order * 50));
				glVertex2f(50, 245 + (this->order * 50));
				glVertex2f(30, 245 + (this->order * 50));
				glEnd();

				// Helicopter Foot
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(35, 245 + (this->order * 50));
				glVertex2f(35, 240 + (this->order * 50));

				glVertex2f(45, 245 + (this->order * 50));
				glVertex2f(45, 240 + (this->order * 50));

				glVertex2f(30, 240 + (this->order * 50));
				glVertex2f(50, 240 + (this->order * 50));
				glEnd();

				// Helicopter Tail
				glLineWidth(4.0f);
				glBegin(GL_LINES);
				glVertex2f(30, 255 + (this->order * 50));
				glVertex2f(0, 255 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(40, 265 + (this->order * 50));
				glVertex2f(40, 270 + (this->order * 50));
				
				glColor3f(0, 0, 0);
				glVertex2f(50, 275 + (this->order * 50));
				glVertex2f(30, 265 + (this->order * 50));
				glVertex2f(50, 265 + (this->order * 50));
				glVertex2f(30, 275 + +(this->order * 50));
				glEnd();


			}
			else {
				glBegin(GL_QUADS);
				glVertex2f(430, 265 + (this->order * 50));
				glVertex2f(450, 265 + (this->order * 50));
				glVertex2f(450, 245 + (this->order * 50));
				glVertex2f(430, 245 + (this->order * 50));
				glEnd();

				// Helicopter Foot
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(445, 245 + (this->order * 50));
				glVertex2f(445, 240 + (this->order * 50));

				glVertex2f(435, 245 + (this->order * 50));
				glVertex2f(435, 240 + (this->order * 50));

				glVertex2f(450, 240 + (this->order * 50));
				glVertex2f(430, 240 + (this->order * 50));
				glEnd();

				// Helicopter Tail
				glLineWidth(4.0f);
				glBegin(GL_LINES);
				glVertex2f(450, 255 + (this->order * 50));
				glVertex2f(480, 255 + (this->order * 50));
				glEnd();

				// Helicopter Propeller
				glLineWidth(2.0f);
				glBegin(GL_LINES);
				glVertex2f(440, 265 + (this->order * 50));
				glVertex2f(440, 270 + (this->order * 50));

				glColor3f(0, 0, 0);
				glVertex2f(450, 275 + (this->order * 50));
				glVertex2f(430, 265 + (this->order * 50));
				glVertex2f(450, 265 + (this->order * 50));
				glVertex2f(430, 275 + +(this->order * 50));
				glEnd();
			}
		}
};

