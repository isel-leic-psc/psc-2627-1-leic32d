#include "point.h"

Point * create_point(int xx, int yy) {
	Point * pnt = (Point *)malloc(sizeof(Point));
	pnt->x = xx;
	pnt->y = yy;
	return pnt;
}

void destroy_point(Point * p) {
	free(p);
}

void translate_point(Point * pobj, int dx, int dy) {
	pobj->x += dx;
	pobj->y += dy;
}
