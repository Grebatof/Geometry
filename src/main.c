#include "geometry.h"
#include "input.h"
#include "processing.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Geometry* geo = int_geometry(1);

    char arr[100]; //сделать 100 и каждый раз идти к arr[0], когда встретили \n,
                   //для полигона выделять +100 памяти
    FILE* myfile;
    myfile = fopen("geo1.txt", "r");

    if (myfile == NULL) {
        printf("No file\n");
        return 1;
    }
    int i;
    int j;
    int row_count = 1;

    for (i = 0; (arr[i] = fgetc(myfile)) != EOF; i++) {
        if (arr[i] == '\n' || arr[i] == '\0') {
            input_processing(arr, i, geo, row_count);
            i = -1;
            row_count++;
        }
    }

    //сравнение порядков номеров if () вызываем соответственный

    int number_circle = 0;
    int number_triangle = 0;
    int number_poligon = 0;
    int k;
    for (j = 1; j < geo->serial_number; j++) {
        if (j == geo->circle[number_circle].serial_number) {
            printf("%ld.  circle(%d %d, %.3f)\n\n",
                   geo->circle[number_circle].serial_number,
                   geo->circle[number_circle].point.x,
                   geo->circle[number_circle].point.y,
                   geo->circle[number_circle].radius);
            printf("\tperimeter = %.3f\n", geo->circle[number_circle].perimeter);
            printf("\tarea = %.3f\n", geo->circle[number_circle].area);
            printf("\n");
            number_circle++;
            continue;
        }
        if (j == geo->triangle[number_triangle].serial_number) {
            printf("%ld.  triangle((%d %d, %d %d, %d %d, %d %d))\n\n",
                   geo->triangle[number_triangle].serial_number,
                   geo->triangle[number_triangle].point[0].x,
                   geo->triangle[number_triangle].point[0].y,
                   geo->triangle[number_triangle].point[1].x,
                   geo->triangle[number_triangle].point[1].y,
                   geo->triangle[number_triangle].point[2].x,
                   geo->triangle[number_triangle].point[2].y,
                   geo->triangle[number_triangle].point[3].x,
                   geo->triangle[number_triangle].point[3].y);
            printf("\tperimeter = %.3f\n", geo->triangle[number_triangle].perimeter);
            printf("\tarea = %.3f\n", geo->triangle[number_triangle].area);
            printf("\n");
            number_triangle++;
            continue;
        }
        if (j == geo->poligon[number_poligon].serial_number) {
            printf("%ld.  poligon((%d %d,", geo->poligon[number_poligon].serial_number, geo->poligon[number_poligon].points[0].x, geo->poligon[number_poligon].points[0].y);
            for (k = 1; k < geo->poligon[number_poligon].numeral_points - 2; k++)
            {
                printf(" %d %d,", geo->poligon[number_poligon].points[k].x, geo->poligon[number_poligon].points[k].y);
            }
            printf(" %d %d))\n\n", geo->poligon[number_poligon].points[k].x, geo->poligon[number_poligon].points[k].y);
            printf("\tperimeter = %.3f\n", geo->poligon[number_poligon].perimeter);
            printf("\tarea = %.3f\n", geo->poligon[number_poligon].area);
            printf("\n");
            number_poligon++;
            continue;
        }
    }

    fclose(myfile);

    return 0;
}

// при пересечении фигур добавить в структуры данные о пересечении (1 фигуры и 2
// фигуры)
