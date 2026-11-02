#include <stdio.h>
#include <stddef.h>

/*
struct rect {
    int x;
    int y;
    int width;
    int height;
};
typedef struct rect Rectangle;
*/

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

int rect_area(const Rectangle *r)
{
    return r->width * r->height;
}

void rect_print(const Rectangle *r)
{
    printf("(%d, %d), %d x %d, area = %d\n",
           r->x, r->y, r->width, r->height, rect_area(r));
}

int rects_total_area(
	const Rectangle * rectangles, size_t n
);

int rect_refs_total_area(
	const Rectangle * rectangles[], size_t n
);

int main(void)
{
    // Array of Rectangle objects.
    Rectangle rectangles[4] = {
        { 10, 20, 30, 40 },
        { 50, 60, 20, 10 },
        {  5, 15, 10, 25 },
        { 70, 80, 15, 15 }
    };

    printf("\nAll the rectangles:\n");
    for (size_t i = 0; i < 4; ++i)
        rect_print(&rectangles[i]);

	int total_area = rects_total_area(&rectangles[0], 4);
    printf("\nTotal area: %d\n", total_area);

	const Rectangle * rectangle_refs[3] = {
		&rectangles[3], &rectangles[0], &rectangles[2],
	};

	int total_refs_area = rect_refs_total_area(
		&rectangle_refs[0], 3
	);
    printf("\nTotal refs area: %d\n", total_refs_area);

	return 0;
} 
