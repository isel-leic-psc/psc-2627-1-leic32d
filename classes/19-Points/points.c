#include <stdio.h>
#include <stdlib.h>
#include "point.h"

void use_points(Point * p1, Point * p2);

int main() {
	Point * p1 = create_point(3, 4);
	Point * p2 = create_point(4, 5);

	use_points(p1, p2);

	destroy_point(p2);
	destroy_point(p1);
	return 0;
}