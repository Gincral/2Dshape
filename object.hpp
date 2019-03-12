/*
 *  file: object.hpp
 *  author: Ni Yang
 *  date: 2018/09/14
 *  description: data structures and operation functions being used in simple draw
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <GL/gl.h>
#include <stdlib.h>


typedef struct {
    GLint x1, y1, x2, y2;
    GLint t, s;
    GLfloat r, g, b;
} shape;

typedef struct node{
    shape *sp;
    struct node *prev, *next;
} node;

shape * new_object(GLint x1, GLint y1, GLint x2,  GLint y2, GLint t, GLint s, GLfloat r,  GLfloat g, GLfloat b);

void clean(node **frontp, node **backp);

void insert_back(node **frontp, node **backp, shape *shapep);

void delete_node(node **frontp, node **backp, node *np);

void to_front(node **frontp, node **backp, node *np);

void to_back(node **frontp, node **backp, node *np);

#endif /* OBJECT_HPP_ */
