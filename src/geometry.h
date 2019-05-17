#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stddef.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int serial_number;
    int name;
} Intersects;

typedef struct {
    float perimeter;
    float area;
    Point point;
    float radius;
    Intersects intersects[20];
    size_t serial_number;
} Circle;

typedef struct {
    float perimeter;
    float area;
    Point* point;
    Intersects intersects[20];
    size_t serial_number;
} Triangle;

typedef struct {
    float perimeter;
    float area;
    Point* points;
    Intersects intersects[20];
    size_t numeral_points;
    size_t serial_number;
} Poligon;

typedef struct {
    Triangle* triangle;
    size_t size_triangle;
    Poligon* poligon;
    size_t size_poligon;
    Circle* circle;
    size_t size_circle;
    size_t serial_number;
} Geometry;

Geometry* int_geometry();
Poligon* int_poligon();
void int_geometry_push_triangle(Geometry* geo);
void int_geometry_push_circle(Geometry* geo);
void int_geometry_push_poligon(Geometry* geo);
void int_geometry_push_poligon_point(Geometry* geo);

#endif
