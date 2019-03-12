#include "object.hpp"

shape * new_object(GLint x1, GLint y1, GLint x2, GLint y2, GLint t, GLint s,
		GLfloat r, GLfloat g, GLfloat b) {
	shape *p = (shape *) malloc(sizeof(shape));
	p->x1 = x1;
	p->y1 = y1;
	p->x2 = x2;
	p->y2 = y2;

	p->t = t;
	p->s = s;

	p->r = r;
	p->g = g;
	p->b = b;

	return p;
}

void clean(node **frontp, node **backp) {
	node *tp = *frontp;
	while (tp != NULL) {
		*frontp = (*frontp)->next;
		free(tp->sp);
		free(tp);
		tp = *frontp;
	}
	*frontp = NULL;
	*backp = NULL;

}

void insert_back(node **frontp, node **backp, shape *shapep) {
	node *p = (node*) malloc(sizeof(node));
	p->sp = shapep;
	p->next = NULL;
	p->prev = NULL;
	if (*backp == NULL) {
		*frontp = p;
		*backp = p;
	} else {
		(*backp)->next = p;
		p->prev = *backp;
		*backp = p;
	}
}

void delete_node(node **frontp, node **backp, node *np) {
	if (np->prev == NULL && np->next == NULL) {
		*frontp = NULL;
		*backp = NULL;
	} else if (np == *frontp && np->next != NULL) {
		*frontp = (*frontp)->next;
		(*frontp)->prev = NULL;
	} else if (np == *backp && np->prev != NULL) {
		*backp = (*backp)->prev;
		(*backp)->next = NULL;
	} else {
		np->prev->next = np->next;
		np->next->prev = np->prev;
	}
	free(np->sp);
	free(np);
}

void to_front(node **frontp, node **backp, node *np) {
	if (np == *frontp) {
		return;
	} else if (np == *backp) {
		*backp = np->prev;
		(*backp)->next = NULL;
		np->next = *frontp;
		np->prev = NULL;
		(*frontp)->prev = np;
		*frontp = np;
	} else {
		np->prev->next = np->next;
		np->next->prev = np->prev;
		np->next = *frontp;
		np->prev = NULL;
		(*frontp)->prev = np;
		*frontp = np;
	}
}

void to_back(node **frontp, node **backp, node *np) {
	if (np == *backp) {
		return;
	} else if (np == *frontp) {
		*frontp = np->next;
		(*frontp)->prev = NULL;
		np->prev = *backp;
		np->next = NULL;
		(*backp)->next = np;
		*backp = np;
	} else {
		np->prev->next = np->next;
		np->next->prev = np->prev;
		np->prev = *backp;
		np->next = NULL;
		(*backp)->next = np;
		*backp = np;
	}

}
