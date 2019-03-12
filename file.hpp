/*
 *  file: file.hppp
 */
#ifndef FILE_HPP_
#define FILE_HPP_

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>  // C++ file I/O
#include <iostream>

#include "object.hpp"

#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

int save_svg(node *front, const char *filename);
int open_svg(node **frontp, node **backp,  char *filename);
int SaveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);

#endif /* FILE_HPP_ */
