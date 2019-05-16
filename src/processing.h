#ifndef _PROCESSING_H_
#define _PROCESSING_H_
#include "geometry.h"
#include <stddef.h>


void circle_perimeter_calculation(Geometry* geo);
int processing_circle(
        int* i, int size, char* arr, Geometry* geo, int row_count);
int processing_radius(int* i, int size, char* arr, Geometry* geo);
int processing_coordinates_circle(int* i, int size, char* arr, Geometry* geo);


void triangle_perimeter_calculation(Geometry* geo);
int processing_triangle(
        int* i, int size, char* arr, Geometry* geo, int row_count);
int processing_next_coordinates_triangle(
        int* i, int size, char* arr, Geometry* geo);
int processing_first_coordinates_triangle(
        int* i, int size, char* arr, Geometry* geo);


void poligon_perimeter_calculation(Geometry* geo);
int processing_first_coordinates_poligon(
        int* i, int size, char* arr, Geometry* geo);
int processing_next_coordinates_poligon(
        int* i, int size, char* arr, Geometry* geo);
int processing_poligon(
        int* i, int size, char* arr, Geometry* geo, int row_count);


float distance_between_points(Point first_point, Point second_point);

int figure_check(char* figure_name);

void error_handling(int* i, int size, char* arr, int error, int row_count);

#endif
