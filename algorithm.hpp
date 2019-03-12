/*
 *  file: algorithm.hppp
 */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>  // C++ file I/O
#include <iostream>

#include "object.hpp"

GLint min(GLint x, GLint y);
GLint max(GLint x, GLint y);
node *select(node *back, GLint x, GLint y);
void setPixel(GLint x, GLint y);
void polygon(GLint x1, GLint y1, GLint x2, GLint y2);
void polygonFill(GLint x1, GLint y1, GLint x2, GLint y2);
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x, const GLint& y);
void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y);
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2);
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2);
void Bresenham(int x1, int y1, int x2, int y2);
void drawShape(shape *p);
void drawObject(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat r1, GLfloat g1, GLfloat b1, GLint t1, GLint s1);
void drawObjectList(node *front);

#endif /* GOBJECT_HPP_ */


