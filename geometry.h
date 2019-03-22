#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_


typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point point;
	float radius;
	size_t serial_number;
} Circle;

typedef struct {
	Point *point;
	size_t serial_number;
} Triangle;

typedef struct {
	Point *points;
	size_t numeral_points;
	size_t serial_number;
} Poligon;

typedef struct {
	Triangle *triangle;
	size_t size_triangle;
	Poligon *poligon;
	size_t size_poligon;
	Circle *circle;
	size_t size_circle;
} Geometry;


Geometry *int_geometry(size_t initial_figure);
Poligon *int_poligon(size_t initial_points);
void int_geometry_push_triangle(Geometry *geo);
void int_geometry_push_circle(Geometry *geo);


#endif
