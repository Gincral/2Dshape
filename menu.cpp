/*
 *  file: menu.hpp
 */

#include "menu.hpp"

//these global variables will be used in the function, need to import by key word extern
extern GLsizei winWidth;
extern GLsizei winHeight;
extern shape *sshapep;
extern GLfloat red, green, blue;
extern GLint type, style, tool, selection, move, dataview_option, xbegin,ybegin,counter,xend,yend;
extern node *front, *back, *snodep;

// used for new drawing operation
void clear() {
	clean(&front, &back);
	tool = 0; selection = 0; move = 0; type = 1; style = 1; //1:filled,2:outline,3:no
	red = 0.0; green = 1.0; blue = 1.0;
	dataview_option=0; xbegin = 0; ybegin = 0; counter = 0; // number of shape object for testing
}

void mainMenu(GLint menuOption) {
	switch (menuOption) {
	case 1:
		clear();
		break;
	case 4:
		exit(0);
	}
	glutPostRedisplay();
}

void typeSubMenu(GLint typeOption) {
	switch (typeOption) {
	case 1:
		type = 1;
		break;
	case 2:
		type = 2;
		break;
	case 3:
		type = 3;
		break;
	}
}

void fileSubMenu(GLint fileOption) {
	switch (fileOption) {
	case 1:  //save svg
		save_svg(front, "output.svg");
		break;
	case 2:  //open svg
		open_svg(&front, &back, "output.svg");
		break;
	case 3:  //save bit map
		SaveBitmap("output.bmp", 0, 0, winWidth, winHeight);
		break;
	}
}

void editSubMenu(GLint editOption) {
	tool = 1;
	switch (editOption) {
	case 1: { //select
		selection = 1;
	}
		break;
	case 2: { //deselect
		selection = 0;
		tool = 0;
		move =0;
		xbegin = 0;
		ybegin = 0;
		xend = 0;
		yend = 0;
	}
		break;
	case 3: { //delete
		if (selection == 1) {
			//delete_node(&front, &back, back);
			delete_node(&front, &back, snodep);
		}
	}
		break;
	case 4: { //top
		if (selection == 1) {
			to_back(&front, &back, snodep);
			//to_back(&front, &back, front);
		}
	}
		break;
	case 5: { // back
		if (selection == 1) {
			to_front(&front, &back, snodep);
			//to_front(&front, &back, back);
		}
	}
		break;
	case 6: {
		if (selection == 1) {
			move = 1;
		}
	}
		break;
	}
}

void styleSubMenu(GLint styleOption) {
	switch (styleOption) {
	case 1: {
		style = 1;
	}
		break;
	case 2: {
		style = 2;
	}
		break;
	}
}

void colorSubMenu(GLint colorOption) {
	switch (colorOption) {
	case 1: {
		red = 1.0;
		green = 0.0;
		blue = 0.0;
	}
		break;
	case 2: {
		red = 0.0;
		green = 1.0;
		blue = 0.0;
	}
		break;
	case 3: {
		red = 0.0;
		green = 0.0;
		blue = 1.0;
	}
		break;
	case 4: {
		red = 0.0;
		green = 1.0;
		blue = 1.0;
	}
	}
	glutPostRedisplay();
}

void dataviewSubMenu(GLint dataOption) {
	switch (dataOption) {
	case 1: {
		dataOption = 1;
	}
		break;
	case 2: {
		dataOption = 2;
	}
		break;
	case 3: {
		dataOption = 3;
	}
		break;
	case 4: {
		dataOption = 4;
	}
	}
}
