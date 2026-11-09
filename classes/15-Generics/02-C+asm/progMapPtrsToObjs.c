#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

typedef struct {
    int x;
    int y;
} Point;

void map_rect_to_point(void * pin, void * pout) {
	Rectangle * prect = (Rectangle *)pin;
	Point * pptr = (Point *)pout;
	pptr->x = prect->x;
	pptr->y = prect->y;
}

void map_string_to_int(void * pin, void * pout) {
	char * numstr = (char *)pin;
	int * pnum = (int *)pout;
	*pnum = atoi(numstr);
}

extern void map_ptrs_to_objs(
	void * * inputs,
	void * outputs,
	size_t count,
	size_t output_size,
	void (*map_obj)(void *, void *)
);

void example_strings_to_ints(void) {

    void * number_strings[] = {
        "42107", "58321", "49872", "51234",
        "40655", "57619", "44783", "53910"
    };

    size_t number_count =
        sizeof(number_strings) / sizeof(number_strings[0]);

    int numbers[number_count];

    map_ptrs_to_objs(
        number_strings,
        numbers,
        number_count,
        sizeof(numbers[0]),
        map_string_to_int
    );

    printf("Converted numbers:\n");

    for (size_t i = 0; i < number_count; i++) {
        printf("%d\n", numbers[i]);
    }
}


void example_rects_to_points(void) {

    Rectangle rectangles[4] = {
        { 10, 20, 30, 40 },
        { 50, 60, 20, 10 },
        {  5, 15, 10, 25 },
        { 70, 80, 15, 15 }
    };

    void * rectangle_pointers[4] = {
        &rectangles[0],
        &rectangles[1],
        &rectangles[2],
        &rectangles[3]
    };

    Point points[4];

    map_ptrs_to_objs(
        rectangle_pointers,
        points,
        4,
        sizeof(points[0]),
        map_rect_to_point
    );

    printf("\nConverted points:\n");

    for (size_t i = 0; i < 4; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
}

int main(void) {
	
	example_strings_to_ints();
	
	example_rects_to_points();
	
	return 0;
}
