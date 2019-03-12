/*
 *  file: algorithm.cpp
 */

#include "algorithm.hpp"

GLint min(GLint x, GLint y) {
	return (x < y) ? x : y;
}

GLint max(GLint x, GLint y) {
	return (x < y) ? y : x;
}

node *select(node *back, GLint x, GLint y) {
	node *n = NULL, *p = back;
	shape *sp;
	while (p != NULL) {
		sp = p->sp;
		if (sp->t == 1) {
			if (min(sp->x1, sp->x2) < x && x < max(sp->x1, sp->x2)
					&& min(sp->y1, sp->y2) < y && y < max(sp->y1, sp->y2)) {
				n = p;
				break;
			}
		} else if (sp->t == 2) {
			GLint r = sqrt(
					(sp->x2 - sp->x1) * (sp->x2 - sp->x1)
							+ (sp->y1 - sp->y2) * (sp->y1 - sp->y2));
			GLint r2 = sqrt(
					(x - sp->x1) * (x - sp->x1) + (sp->y1 - y) * (sp->y1 - y));
			if (r2 <= r) {
				n = p;
				break;
			}
		} else if (sp->t == 3) {
//			GLint mx = min(sp->x1, sp->x2);
//			GLint my = min(sp->y1, sp->y2);
			if (min(sp->x1, sp->x2) < x && x < max(sp->x1, sp->x2)
					&& min(sp->y1, sp->y2) < y && y < max(sp->y1, sp->y2)) {
				if ((x == sp->x1 && y == sp->y1) || (x == sp->x2 && y == sp->y2)) {
					n = p;
					break;
				} else if ((x-sp->x1)/(sp->x2-sp->x1)==(y-sp->y1)/(sp->y2-sp->y1)) {
					n = p;
					break;
				}
			}
		}p = p->prev;
		//printf("next");
	}
	if(n == NULL){
			printf("null\n");
		}else{
			printf("selected\n");
		}
	return n;
}

/* Drawing funtions */
void setPixel(GLint x, GLint y) {
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

/* draw 8 symmetric points on circle by a given point
 * this function is used by circleMidpoint function
 */

void Bresenham(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
//printf("%d, %d\n", tp->sp->x1, tp->sp->y1);
	glEnd();
}

void polygon(GLint x1, GLint y1, GLint x2, GLint y2) {
	Bresenham(x1, y1, x2, y1);
	Bresenham(x1, y1, x1, y2);
	Bresenham(x1, y2, x2, y2);
	Bresenham(x2, y2, x2, y1);
}

void polygonFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	glBegin(GL_POLYGON);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {
	setPixel(xc + x, yc + y);
	setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc - x);
}

/* draw 4 line segments by a given point on circle
 * this function is used by circleMidpointFill for drawing filled circle
 */
void circlePlotPointsFill(GLint xc, GLint yc, GLint x, GLint y) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc - x);
	glVertex2i(xc + y, yc - x);
	glEnd();
}

// draw circle outline bye midpoint algorithm
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint r = sqrt((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2));
	GLint p = 1 - r; // Initial value of midpoint parameter.
	GLint x = 0, y = r;      // Set coordinates for top point of circle.
	/* Plot the initial point in each circle quadrant. */
	circlePlotPoints(x1, y1, x, y);
	while (x < y) {
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x - y) + 1;
		}
		circlePlotPoints(x1, y1, x, y);
	}
}

// draw filled circle by midpoint algorithm
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint r = sqrt((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2));
	GLint p = 1 - r; // Initial value of midpoint parameter.
	GLint x = 0, y = r;      // Set coordinates for top point of circle.
	/* Plot the initial point in each circle quadrant. */
	circlePlotPointsFill(x1, y1, x, y);
	while (x < y) {
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x - y) + 1;
		}
		circlePlotPointsFill(x1, y1, x, y);
	}
}

void drawShape(shape *p) {
	drawObject(p->x1, p->y1, p->x2, p->y2, p->r, p->g, p->b, p->t, p->s);
	//printf("%d", p->s);
}

void drawObject(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat r1, GLfloat g1,
		GLfloat b1, GLint t1, GLint s1) {
	glColor3f(r1, g1, b1);
	if (t1 == 1) {
		if (s1 == 2) {
			polygon(x1, y1, x2, y2);
		} else if (s1 == 1) {
			polygonFill(x1, y1, x2, y2);
		}
	} else if (t1 == 2) {
		if (s1 == 2) {
			circleMidpoint(x1, y1, x2, y2);
		} else if (s1 == 1) {
			circleMidpointFill(x1, y1, x2, y2);
		}
	} else if (t1 == 3) {
		Bresenham(x1, y1, x2, y2);
		//printf("%d\n",type);
	}
}

void drawObjectList(node *front) {
	node *tp = front;
	while (tp != NULL) {
		drawShape(tp->sp);
		tp = tp->next;
	}
}


