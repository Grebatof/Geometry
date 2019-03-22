#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "geometry.h"

Geometry *int_geometry(size_t initial_figure) {
	Geometry *geo = malloc(sizeof(*geo));
	if (geo != NULL) {
		geo->triangle = malloc(sizeof(Triangle));
		geo->size_triangle = 1;
		geo->triangle->point = malloc(sizeof(Point) * 40);
		geo->triangle->point[0].x = geo->triangle->point[1].x = geo->triangle->point[2].x = geo->triangle->point[3].x =
			geo->triangle->point[0].y = geo->triangle->point[1].y = geo->triangle->point[2].y = geo->triangle->point[3].y = 0;
		// geo->triangle->point0.x = geo->triangle->point1.x = geo->triangle->point2.x = geo->triangle->point3.x =
		// 	geo->triangle->point0.y = geo->triangle->point1.y = geo->triangle->point2.y = geo->triangle->point3.y = 0;
		//сделать v->data->data для poligon и его points
		// Poligon *pol = malloc(sizeof(*pol));
		// if (pol != NULL) pol->points = malloc(sizeof(Point));
		geo->poligon = malloc(sizeof(Poligon));
		geo->size_poligon = 1;
		geo->circle = malloc(sizeof(Circle));
		geo->size_circle = 1;
		geo->circle->point.x = geo->circle->point.y = 0;
		geo->circle->radius = 0;
	}
	return geo;
}

Poligon *int_poligon(size_t initial_points) {
	Poligon *pol = malloc(sizeof(*pol));
	if (pol != NULL) pol->points = malloc(sizeof(Point));
	return pol;
}

void int_geometry_push_triangle(Geometry *geo) {
	geo->size_triangle += 1;
	geo->triangle = realloc(geo->triangle, geo->size_triangle * sizeof(Triangle));
	geo->triangle[geo->size_triangle - 1].point[0].x = geo->triangle[geo->size_triangle - 1].point[1].x = geo->triangle[geo->size_triangle - 1].point[2].x = geo->triangle[geo->size_triangle - 1].point[3].x =
		geo->triangle[geo->size_triangle - 1].point[0].y = geo->triangle[geo->size_triangle - 1].point[1].y = geo->triangle[geo->size_triangle - 1].point[2].y = geo->triangle[geo->size_triangle - 1].point[3].y = 0;
}

void int_geometry_push_circle(Geometry *geo) {
	geo->size_circle += 1;
	geo->circle = realloc(geo->circle, geo->size_circle * sizeof(Circle));
	geo->circle[geo->size_circle - 1].point.x = geo->circle[geo->size_circle - 1].point.y = 0;
	geo->circle[geo->size_circle - 1].radius = 0;
}




// int int_vector_push_back(IntVector *v, int item) {
// 	if (v->data == NULL || v == NULL) return -1;
// 	if (v->capacity == 0) v->capacity = 2;
// 	if (v->size == v->capacity) {
// 		v->capacity *= 2;
// 		v->data = realloc(v->data, v->capacity * sizeof(int));
// 	}
// 	v->size++;
// 	v->data[v->size - 1] = item;
// 	return 0;
// }

/*IntVector *int_vector_new(size_t initial_capacity) {
	IntVector *v = malloc(sizeof(*v));
	if (v != NULL &&  initial_capacity > 0) {
		v->data = malloc(sizeof(int) * initial_capacity);
		v->size = 0;
		v->capacity = initial_capacity;
		if (v->data == NULL) printf("WARNING! ARRAY IS NULL\n");
	}
	return v;
}*/
