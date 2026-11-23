#pragma once

#include <stdlib.h>

struct point {
	int x;
	int y;
};
typedef struct point Point;

Point * create_point(int xx, int yy);

void destroy_point(Point * p);

void translate_point(Point * pobj, int dx, int dy);
