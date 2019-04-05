#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "geometry.h"
#include "input.h"
#include "processing.h"

Geometry *int_geometry(size_t initial_figure) {
	Geometry *geo = malloc(sizeof(*geo));
	if (geo != NULL) {
		geo->triangle = malloc(sizeof(Triangle));
		geo->size_triangle = 1;
		geo->triangle->point = malloc(sizeof(Point) * 4);
		for (int k = 0; k < 4; k++) {
	    geo->triangle[geo->size_triangle - 1].point[k].x = geo->triangle[geo->size_triangle - 1].point[k].y = 0;
	  }
		//сделать v->data->data для poligon и его points
		// Poligon *pol = malloc(sizeof(*pol));
		// if (pol != NULL) pol->points = malloc(sizeof(Point));
		geo->poligon = malloc(sizeof(Poligon));
		geo->poligon->points = malloc(sizeof(Point) * 4);
		geo->size_poligon = 1;
		geo->poligon->numeral_points = 4;
		geo->circle = malloc(sizeof(Circle));
		geo->size_circle = 1;
		geo->serial_number = 1;
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
	geo->triangle[geo->size_triangle - 1].point = realloc(geo->triangle[geo->size_triangle - 1].point, sizeof(Point) * 4);
	for (int k = 0; k < 4; k++) {
    geo->triangle[geo->size_triangle - 1].point[k].x = geo->triangle[geo->size_triangle - 1].point[k].y = 0;
  }
}

void int_geometry_push_circle(Geometry *geo) {
	geo->size_circle += 1;
	geo->circle = realloc(geo->circle, geo->size_circle * sizeof(Circle));
}

void int_geometry_push_poligon(Geometry *geo) {
	geo->size_poligon += 1;
	geo->poligon = realloc(geo->poligon, geo->size_poligon * sizeof(Poligon));
	geo->poligon[geo->size_poligon - 1].numeral_points = 4;

	geo->poligon[geo->size_poligon - 1].points = calloc(0, sizeof(Point) * 4);
	/*for (int k = 0; k < 4; k++) {
    geo->poligon[geo->size_poligon - 1].points[k].x = geo->poligon[geo->size_poligon - 1].points[k].y = 0;
  }*/
}

void int_geometry_push_poligon_point(Geometry *geo) {
	geo->poligon[geo->size_poligon - 1].numeral_points++;
	geo->poligon[geo->size_poligon - 1].points = realloc(geo->poligon[geo->size_poligon - 1].points, sizeof(Point) * geo->poligon->numeral_points);
	geo->poligon[geo->size_poligon - 1].points[geo->poligon[geo->size_poligon - 1].numeral_points - 1].x = geo->poligon[geo->size_poligon - 1].points[geo->poligon[geo->size_poligon - 1].numeral_points - 1].y = 0;
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
