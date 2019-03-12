/*
 *  file: simpledraw.cpp
 *  author: Ni Yang
 *  date: 20/09/2018
 *  description: CP411A1 simple draw program
 */

#include "simpledraw.hpp"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glFlush();
}

void drawList(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	drawObjectList(front);
	if (selection == 1 && snodep != NULL) {
		drawObject(snodep->sp->x1, snodep->sp->y1, snodep->sp->x2,
				snodep->sp->y2, 0.0, 0.0, 0.0, snodep->sp->t, 2);
	}
	glFlush();
	glutSwapBuffers();
}

void mouseDraw(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (tool == 0 && selection == 0) {
		if (button == GLUT_LEFT_BUTTON) {
			shape *p = new_object(0, 0, 0, 0, type, style, red, green, blue);
			//printf("%d\n",p->s);
			if (action == GLUT_DOWN) {
				insert_back(&front, &back, p);
				p->x1 = xMouse;
				p->y1 = yMouse;

				p->x2 = xMouse;
				p->y2 = yMouse;

				printf("%d, %d\n", p->x1, p->y1);
				//printf("%d, %d\n", p->x2, p->y2); // for debugging
			} else if (action == GLUT_UP) {
				p->x2 = xMouse;
				p->y2 = yMouse;
				//printf("\n");
				//printf("%d, %d\n", p->x1, p->y1);
				printf("%d, %d\n", p->x2, p->y2); // for debugging
			}
		}
	} else {
		if (selection == 1) {
			if (button == GLUT_LEFT_BUTTON) {
				if (action == GLUT_DOWN) {
					snodep = select(back, xMouse, yMouse);
				}
			}
		}
		if (move == 1) {
			if (button == GLUT_LEFT_BUTTON) {
				if (action == GLUT_DOWN) {
					xbegin = xMouse;
					ybegin = yMouse;

					xend = xMouse;
					yend = yMouse;
				} else if (action == GLUT_UP) {
					xend = xMouse;
					yend = yMouse;

					snodep->sp->x1 = snodep->sp->x1+(xend-xbegin);
					snodep->sp->x2 = snodep->sp->x2+(xend-xbegin);
					snodep->sp->y1 = snodep->sp->y1+(yend-ybegin);
					snodep->sp->y2 = snodep->sp->y2+(yend-ybegin);
				}
			}
		}
	}
//	printf("%d, %d, \n",  p->x1, p->y1);
//	printf("%d, %d, \n",  p->x2, p->y2);
	glutPostRedisplay();
	glFlush();
}

//here is a BUG! :3
void mouseMotion(GLint xMouse, GLint yMouse) {
//xMouse, yMouse gives the moouse pointer coordinates while dragging with mouse button down.
	if (tool == 1 && move == 1) {
		xend = xMouse;
		yend = yMouse;
		snodep->sp->x1 = snodep->sp->x1+(xend-xbegin);
		snodep->sp->x2 = snodep->sp->x2+(xend-xbegin);
		snodep->sp->y1 = snodep->sp->y1+(yend-ybegin);
		snodep->sp->y2 = snodep->sp->y2+(yend-ybegin);
		xbegin = xMouse;
		ybegin = yMouse;

	} else {
		if (back != NULL and selection == 0) {
			back->sp->x2 = xMouse;
			back->sp->y2 = yMouse;
		}
	}
	glutPostRedisplay();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	/*  Reset viewport and projection parameters  */
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);
	/*  Reset display-window size parameters.  */
	winWidth = newWidth;
	winHeight = newHeight;
	drawList();
	glFlush();
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0);  //used for prompt Eclipse console output
	setvbuf(stderr, NULL, _IONBF, 0);
//  ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);  //used to hide console

	glutInit(&argc, argv);

//  //menu setting
	GLint edit_subMenu = glutCreateMenu(editSubMenu);
	glutAddMenuEntry("Select ", 1);
	glutAddMenuEntry("Deselect ", 2);
	glutAddMenuEntry("Delete", 3);
	glutAddMenuEntry("Pull to top", 4);
	glutAddMenuEntry("Push to bottom", 5);
	glutAddMenuEntry("Move ", 6);

	GLint type_subMenu = glutCreateMenu(typeSubMenu);
	glutAddMenuEntry(" Rectangle ", 1);
	glutAddMenuEntry(" Circle (Midpoint Alg.) ", 2);
	glutAddMenuEntry(" Line (Bresenham Alg.) ", 3); //

	GLint style_subMenu = glutCreateMenu(styleSubMenu);
	glutAddMenuEntry("Filled ", 1);
	glutAddMenuEntry("Outline ", 2);

	GLint file_subMenu = glutCreateMenu(fileSubMenu);
	glutAddMenuEntry("Save SVG File ", 1);
	glutAddMenuEntry("Open SVG File ", 2);
	glutAddMenuEntry("Export to Bitmap ", 3);

	GLint color_subMenu = glutCreateMenu(colorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Aquamarine", 4);
// more colors

	GLint dataview_subMenu = glutCreateMenu(dataviewSubMenu);
	glutAddMenuEntry("Linear Regression", 1);

	glutCreateMenu(mainMenu); // Create main pop-up menu.
	glutAddMenuEntry("New ", 1);
	glutAddSubMenu("Draw ", type_subMenu);
	glutAddSubMenu("Edit ", edit_subMenu);
	glutAddSubMenu("Styles ", style_subMenu);
	glutAddSubMenu("Colors ", color_subMenu);
	glutAddSubMenu("Files ", file_subMenu);
	glutAddSubMenu("Data visualization ", dataview_subMenu);
	glutAddMenuEntry("Quit", 4);
// end of menu

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleDraw Ni Yang");

	init();
	glutDisplayFunc(drawList);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseDraw);
	glutMotionFunc(mouseMotion);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
