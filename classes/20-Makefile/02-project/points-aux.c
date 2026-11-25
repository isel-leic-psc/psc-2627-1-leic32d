#include <stdio.h>
#include "point.h"

void use_points(Point * p1, Point * p2) {
	printf("Point1(%d, %d)\n", p1->x, p1->y);
	printf("Point2(%d, %d)\n", p2->x, p2->y);
	translate_point(p2, 75, -32);
	printf("Point2(%d, %d)\n", p2->x, p2->y);
}
