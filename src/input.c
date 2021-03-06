#include "input.h"
#include "geometry.h"
#include "processing.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_processing(char* arr, int size, Geometry* geo, int row_count)
{
    if (geo == NULL) {
        return -1;
    }
    int i;
    char figure_name[100]; // dynamic array
    for (i = 0; i < size; i++) {
        if ('a' <= arr[i] && arr[i] <= 'z') {
            figure_name[i] = arr[i];
        } else {
            break;
        }
    }
    figure_name[i] = '\0';

    switch (figure_check(figure_name)) {
    case 0:
        printf("%s", figure_name);
        for (; i < size; i++) {
            printf("%c", arr[i]);
        }
        printf("\n\n(row: %d) Dont know figure '%s'\n\n\n", row_count, figure_name);
        break;
    case 1:
        processing_circle(&i, size, arr, geo, row_count);
        break;
    case 2:
        processing_triangle(&i, size, arr, geo, row_count);
        break;
    case 3:
        processing_poligon(&i, size, arr, geo, row_count);
        break;
    }
    return 0;
}
