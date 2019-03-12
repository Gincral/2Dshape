/*
 *  file: SimpleDraw.hpp
 *  author: Ni Yang
 *  date: 2018/09/15
 */
#ifndef SIMPLEDRAW_HPP_
#define SIMPLEDRAW_HPP_

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>  // C++ file I/O
#include <iostream>

#include "object.hpp"
#include "algorithm.hpp"
#include "file.hpp"
#include "menu.hpp"
#include "dataview.hpp"

//global variables
shape *sshapep = NULL; //selected shape object pointer
shape tshape;   //temporal shape variable
node *front = NULL, *back = NULL, *snodep = NULL; //pointers for double linked list.

GLsizei winWidth = 800, winHeight = 600;
GLint tool = 0; //0:draw,1:edit,2:dataview
GLint selection = 0; //1: in selection mode, else not.
GLint move = 0; //0:not move, 1:move, used when tool = 1
GLint type = 1; //1:rectangle,2:circle;3:line
GLint style = 1; //1:filled,2:outline,3:no
GLfloat red = 0.0, green = 1.0, blue = 1.0;
GLint dataview_option = 4; //1:bar,2:pi,3:plot,4:regression
GLint xbegin = 0, ybegin = 0, xend = 0, yend = 0;
GLint counter = 0; // number of shape object for testing

void init(void);
void drawList(void);
void mouseDraw(GLint button, GLint action, GLint xMouse, GLint yMouse);
void mouseMotion(GLint x, GLint y);
void winReshapeFcn(GLint newWidth, GLint newHeight);
int main(int argc, char** argv);

#endif /* SIMPLEDRAW_HPP_ */
