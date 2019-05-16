#include "processing.h"
#include "geometry.h"
#include "input.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.1415926535

float distance_between_points(Point first_point, Point second_point)
{
    return sqrt((pow(first_point.x - second_point.x, 2) + pow(first_point.y - second_point.y, 2)));
}

void error_handling(int* i, int size, char* arr, int error, int row_count)
{
    int j;
    for (j = 0; j < size; j++) {
        printf("%c", arr[j]);
    }
    printf("\n");
    for (j = 0; j < *i - 1; j++) {
        printf(" ");
    }
    printf("^\n");
    switch (error) {
    case 11:
        printf("\n(row: %d) Missing '('\n\n\n", row_count);
        break;
    case 12:
        printf("\n(row: %d) Too mush symbol minus\n\n\n", row_count);
        break;
    case 13:
        printf("\n(row: %d) Too mush symbol points\n\n\n", row_count);
        break;
    case 14:
        printf("\n(row: %d) Wrong radius (radius must be > 0)\n\n\n", row_count);
        break;
    case 15:
        printf("\n(row: %d) Wrong last/first coordinates (first coordinates "
               "must be equal last coordinates)\n\n\n",
               row_count);
        break;
    case 16:
        printf("\n(row: %d) Missing ')'\n\n\n", row_count);
        break;
    case 17:
        printf("\n(row: %d) Coordinate X missing\n\n\n", row_count);
        break;
    case 18:
        printf("\n(row: %d) Coordinate Y missing\n\n\n", row_count);
        break;
    case 19:
        printf("\n(row: %d) Missing ','\n\n\n", row_count);
        break;
    case 20:
        printf("\n(row: %d) Unknown error\n\n\n", row_count);
        break;
    case 21:
        printf("\n(row: %d) Missing ' '\n\n\n", row_count);
        break;
    case 22:
        printf("\n(row: %d) Wrong location '-'\n\n\n", row_count);
        break;
    default:
        break;
    }
}

int figure_check(char* figure_name)
{
    if (!(strcmp(figure_name, "circle")))
        return 1;
    if (!(strcmp(figure_name, "triangle")))
        return 2;
    if (!(strcmp(figure_name, "poligon")))
        return 3;

    return 0;
}
// возвращать тип ошибки
void circle_area_calculation(Geometry* geo)
{
    geo->circle[geo->size_circle - 1].area = (float)geo->circle[geo->size_circle - 1].radius * geo->circle[geo->size_circle - 1].radius * M_PI;
}
void circle_perimeter_calculation(Geometry* geo)
{
    geo->circle[geo->size_circle - 1].perimeter = (float)geo->circle[geo->size_circle - 1].radius * M_PI * 2;
}
int processing_radius(int* i, int size, char* arr, Geometry* geo)
{
    int powka = 1;
    int point = 0;
    int numbers_points = 0;
    int last_symbol = 0;
    geo->circle[geo->size_circle - 1].radius = 0;

    if (arr[++(*i)] != ' ')
        return 21;
    (*i)++;

    for (; *i < size; (*i)++) {
        if (point > 1)
            return 13;
        if (isdigit(arr[*i]) && point == 0) {
            geo->circle[geo->size_circle - 1].radius = arr[*i] - '0' + (geo->circle[geo->size_circle - 1].radius * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }

        if (arr[*i] == '.') {
            point++;
            continue;
        }

        if (isdigit(arr[*i])) {
            geo->circle[geo->size_circle - 1].radius
                    = (float)(arr[*i] - '0') / (pow(10, powka)) + geo->circle[geo->size_circle - 1].radius; // преобразуем строку в число
            numbers_points++;
            powka++;
            continue;
        }

        if ((numbers_points > 0) && (arr[*i] == ')')) {
            if (geo->circle[geo->size_circle - 1].radius > 0) {
                last_symbol = 1;
                break;
            }
            return 14;
        } else {
            return 15;
        }
    }
    if (last_symbol == 1) {
        return -1;
    } else {
        return 16;
    }
}
int processing_coordinates_circle(int* i, int size, char* arr, Geometry* geo)
{
    int symbol_minus = 0;
    int numbers_points = 0;
    geo->circle[geo->size_circle - 1].point.x = geo->circle[geo->size_circle - 1].point.y = geo->circle[geo->size_circle - 1].radius
            = 0; // "зануляем" значения // можно сделать функцию zeroing();

    if (arr[(*i)] != '(')
        return 11;
    (*i)++;
    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }

        if (isdigit(arr[*i])) {
            geo->circle[geo->size_circle - 1].point.x
                    = arr[*i] - '0' + (geo->circle[geo->size_circle - 1].point.x * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }

        if (arr[*i] == ' ') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->circle[geo->size_circle - 1].point.x *= -1;
                break;
            }
            return 17;
        } else {
            return 17;
        }
    }

    (*i)++;
    symbol_minus = 0;
    numbers_points = 0;

    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }
        if (isdigit(arr[*i])) {
            geo->circle[geo->size_circle - 1].point.y
                    = arr[*i] - '0' + (geo->circle[geo->size_circle - 1].point.y * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }
        if (arr[*i] == ',') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->circle[geo->size_circle - 1].point.y *= (-1);
                break;
            }
            return 18;
        } else {
            return 19;
        }
    }

    return -1;
}
int processing_circle(int* i, int size, char* arr, Geometry* geo, int row_count)
{
    int error;

    if ((error = processing_coordinates_circle(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    if ((error = processing_radius(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    circle_perimeter_calculation(geo);
    circle_area_calculation(geo);
    geo->circle[geo->size_circle - 1].serial_number = geo->serial_number++;
    int_geometry_push_circle(geo);
    return 0;
}

void triangle_area_calculation(Geometry* geo)
{
    float p = geo->triangle[geo->size_triangle - 1].perimeter / 2.0;
    geo->triangle[geo->size_triangle - 1].area = (float)sqrt(
            p * (p - distance_between_points(geo->triangle[geo->size_triangle - 1].point[0], geo->triangle[geo->size_triangle - 1].point[1]))
            * (p - distance_between_points(geo->triangle[geo->size_triangle - 1].point[1], geo->triangle[geo->size_triangle - 1].point[2]))
            * (p - distance_between_points(geo->triangle[geo->size_triangle - 1].point[2], geo->triangle[geo->size_triangle - 1].point[0])));
}
void triangle_perimeter_calculation(Geometry* geo)
{
    geo->triangle[geo->size_triangle - 1].perimeter
            = (float)distance_between_points(geo->triangle[geo->size_triangle - 1].point[0], geo->triangle[geo->size_triangle - 1].point[1])
            + distance_between_points(geo->triangle[geo->size_triangle - 1].point[1], geo->triangle[geo->size_triangle - 1].point[2])
            + distance_between_points(geo->triangle[geo->size_triangle - 1].point[2], geo->triangle[geo->size_triangle - 1].point[0]);
}
int processing_first_coordinates_triangle(int* i, int size, char* arr, Geometry* geo)
{
    int symbol_minus = 0;
    int numbers_points = 0;
    for (int k = 0; k < 4; k++) {
        geo->triangle[geo->size_triangle - 1].point[k].x = geo->triangle[geo->size_triangle - 1].point[k].y = 0;
    }
    // "зануляем" значения // можно сделать функцию zeroing();
    if (arr[(*i)++] != '(')
        return 11;
    if (arr[(*i)++] != '(')
        return 11;

    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }

        if (isdigit(arr[*i])) {
            geo->triangle[geo->size_triangle - 1].point[0].x
                    = arr[*i] - '0' + (geo->triangle[geo->size_triangle - 1].point[0].x * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }

        if (arr[*i] == ' ') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->triangle[geo->size_triangle - 1].point[0].x *= -1;
                break;
            }
            return 17;
        } else {
            return 17;
        }
    }

    (*i)++;
    symbol_minus = 0;
    numbers_points = 0;

    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }
        if (isdigit(arr[*i])) {
            geo->triangle[geo->size_triangle - 1].point[0].y
                    = arr[*i] - '0' + (geo->triangle[geo->size_triangle - 1].point[0].y * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }
        if (arr[*i] == ',') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->triangle[geo->size_triangle - 1].point[0].y *= (-1);
                break;
            }
            return 18;
        } else {
            return 19;
        }
    }
    return -1;
}
int processing_next_coordinates_triangle(int* i, int size, char* arr, Geometry* geo)
{
    int symbol_minus = 0;
    int numbers_points = 0;
    int point_number = 1;
    int counterXY = -1;
    int space = 0;
    int last_symbol = 0;
    int countX = 0;
    int countY = 0;

    (*i)++;
    for (; *i < size; (*i)++) {
        if (isdigit(arr[*i]) && arr[*i - 1] == ',')
            return 21;
        if (space > 2)
            return 19;
        if (symbol_minus > 1)
            return 12;
        /*if (point_number) {
          counterXY -= 2;
        }*/
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }

        if (counterXY == 0 && isdigit(arr[*i])) {
            geo->triangle[geo->size_triangle - 1].point[point_number].x
                    = arr[*i] - '0' + (geo->triangle[geo->size_triangle - 1].point[point_number].x * 10);
            numbers_points++;
            countX++;
            continue;
        }
        if (arr[*i] == ' ') {
            if (counterXY == 0 && symbol_minus == 1) {
                geo->triangle[geo->size_triangle - 1].point[point_number].x *= -1;
            }
            symbol_minus = 0;
            numbers_points = 0;
            counterXY++;
            space++;
            continue;
        }
        if (counterXY == 1 && isdigit(arr[*i]) && countX > 0) {
            geo->triangle[geo->size_triangle - 1].point[point_number].y
                    = arr[*i] - '0' + (geo->triangle[geo->size_triangle - 1].point[point_number].y * 10);
            numbers_points++;
            countY++;
            continue;
        } else if (countX == 0) {
            (*i)--;

            return 18;
        }

        if (arr[*i] == ',') {
            if (numbers_points > 0) {
                if (counterXY == 1 && symbol_minus == 1) {
                    geo->triangle[geo->size_triangle - 1].point[point_number].y *= -1;
                }
                symbol_minus = 0;
                numbers_points = 0;
                point_number++;
                counterXY -= 2;
                space -= 2;
                countY = 0;
                countX = 0;
                continue;
            }
            return 18;
        }

        if (numbers_points == 0) {
            if (arr[(*i) - 1] == ',') {
                (*i)--;
                return 18;
            }

            return 18;
        }
        if ((numbers_points > 0) && (arr[*i] == ')')) {
            if (arr[++(*i)] == ')') {
                if (counterXY == 1 && symbol_minus == 1) {
                    geo->triangle[geo->size_triangle - 1].point[point_number].y *= -1;
                }
                last_symbol = 1;
                break;
            }
            return 16;
        }
        return 20;
    }
    if (countY == 0) {
        (*i)--;

        return 18;
    }
    if (last_symbol == 1) {
        if (geo->triangle[geo->size_triangle - 1].point[3].x == geo->triangle[geo->size_triangle - 1].point[0].x
            && geo->triangle[geo->size_triangle - 1].point[3].y == geo->triangle[geo->size_triangle - 1].point[0].y) {
            return -1;
        } else {
            (*i)--;
            return 15;
        }
    } else {
        (*i)++;
        return 16;
    }
    return -1;
}
int processing_triangle(int* i, int size, char* arr, Geometry* geo, int row_count)
{
    int error;

    if ((error = processing_first_coordinates_triangle(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    if ((error = processing_next_coordinates_triangle(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    triangle_perimeter_calculation(geo);
    triangle_area_calculation(geo);
    geo->triangle[geo->size_triangle - 1].serial_number = geo->serial_number++;
    int_geometry_push_triangle(geo);
    return 0;
}

void poligon_area_calculation(Geometry* geo)
{
    float a1, a2, b1, b2, c1, c2, p1, p2;
    int numeral_points = geo->poligon[geo->size_poligon - 1].numeral_points;
    // null i = 0 here
    a1 = (float)distance_between_points(
            geo->poligon[geo->size_poligon - 1].points[0], geo->poligon[geo->size_poligon - 1].points[numeral_points - 1]);
    b1 = (float)distance_between_points(
            geo->poligon[geo->size_poligon - 1].points[numeral_points - 1], geo->poligon[geo->size_poligon - 1].points[1]);
    c1 = (float)distance_between_points(geo->poligon[geo->size_poligon - 1].points[1], geo->poligon[geo->size_poligon - 1].points[0]);
    p1 = (a1 + b1 + c1) / 2;
    geo->poligon[geo->size_poligon - 1].area = sqrt(p1 * (p1 - a1) * (p1 - b1) * (p1 - c1)) / 2;
    for (int i = 1; i < numeral_points / 2; i++) {
        a1 = (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[i], geo->poligon[geo->size_poligon - 1].points[numeral_points - i]);
        b1 = (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[numeral_points - i], geo->poligon[geo->size_poligon - 1].points[i + 1]);
        c1 = (float)distance_between_points(geo->poligon[geo->size_poligon - 1].points[i + 1], geo->poligon[geo->size_poligon - 1].points[i]);
        p1 = (a1 + b1 + c1) / 2;
        geo->poligon[geo->size_poligon - 1].area += sqrt(p1 * (p1 - a1) * (p1 - b1) * (p1 - c1)) / 2;
        a2 = (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[numeral_points - i], geo->poligon[geo->size_poligon - 1].points[i + 1]);
        b2 = (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[i + 1], geo->poligon[geo->size_poligon - 1].points[numeral_points - i - 1]);
        c2 = (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[numeral_points - i - 1], geo->poligon[geo->size_poligon - 1].points[numeral_points - i]);
        p2 = (a2 + b2 + c2) / 2;
        geo->poligon[geo->size_poligon - 1].area += sqrt(p2 * (p2 - a2) * (p2 - b2) * (p2 - c2)) / 2;
        ;
    }
}
void poligon_perimeter_calculation(Geometry* geo)
{
    int points_poligon = geo->poligon[geo->size_poligon - 1].numeral_points - 1 - 1;
    for (int number = 0; number < points_poligon; number++) {
        geo->poligon[geo->size_poligon - 1].perimeter += (float)distance_between_points(
                geo->poligon[geo->size_poligon - 1].points[number], geo->poligon[geo->size_poligon - 1].points[number + 1]);
    }
}
int processing_first_coordinates_poligon(int* i, int size, char* arr, Geometry* geo)
{
    int symbol_minus = 0;
    int numbers_points = 0;
    if (arr[(*i)++] != '(')
        return 11;
    if (arr[(*i)++] != '(')
        return 11;

    geo->poligon[geo->size_poligon - 1].points[0].x = geo->poligon[geo->size_poligon - 1].points[0].y = 0;
    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }

        if (isdigit(arr[*i])) {
            geo->poligon[geo->size_poligon - 1].points[0].x
                    = arr[*i] - '0' + (geo->poligon[geo->size_poligon - 1].points[0].x * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }

        if (arr[*i] == ' ') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->poligon[geo->size_poligon - 1].points[0].x *= -1;
                break;
            }
            return 17;
        } else {
            return 17;
        }
    }

    (*i)++;
    symbol_minus = 0;
    numbers_points = 0;

    for (; *i < size; (*i)++) {
        if (symbol_minus > 1)
            return 12; // проверка на кол-во минусов (если больше 1 -
                       // возвращение места, где произошла ошибка)
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }
        if (isdigit(arr[*i])) {
            geo->poligon[geo->size_poligon - 1].points[0].y
                    = arr[*i] - '0' + (geo->poligon[geo->size_poligon - 1].points[0].y * 10); // преобразуем строку в число
            numbers_points++;
            continue;
        }
        if (arr[*i] == ',') {
            if (numbers_points > 0) {
                if (symbol_minus == 1)
                    geo->poligon[geo->size_poligon - 1].points[0].y *= (-1);
                break;
            }
            return 18;
        } else {
            return 19;
        }
    }
    return -1;
}
int processing_next_coordinates_poligon(int* i, int size, char* arr, Geometry* geo)
{
    int symbol_minus = 0;
    int numbers_points = 0;
    int point_number = 1;
    int counterXY = -1;
    int space = 0;
    int last_symbol = 0;
    int countX = 0;
    int countY = 0;
    int add_point = 3;

    (*i)++;

    for (; *i < size; (*i)++) {
        if (add_point == point_number) {
            add_point++;
            int_geometry_push_poligon_point(geo);
            geo->poligon[geo->size_poligon - 1].points[add_point].x = geo->poligon[geo->size_poligon - 1].points[add_point].y = 0;
        }
        if (isdigit(arr[*i]) && arr[*i - 1] == ',')
            return 21;
        if (space > 2)
            return 19;
        if (symbol_minus > 1)
            return 12;
        /*if (point_number) {
          counterXY -= 2;
        }*/
        if (arr[*i] == '-' && numbers_points == 0) {
            symbol_minus++;
            continue;
        }
        if (arr[*i] == '-' && numbers_points > 0) {
            return 22;
        }

        if (counterXY == 0 && isdigit(arr[*i])) {
            geo->poligon[geo->size_poligon - 1].points[point_number].x
                    = arr[*i] - '0' + (geo->poligon[geo->size_poligon - 1].points[point_number].x * 10);
            numbers_points++;
            countX++;
            continue;
        }
        if (arr[*i] == ' ') {
            if (counterXY == 0 && symbol_minus == 1) {
                geo->poligon[geo->size_poligon - 1].points[point_number].x *= -1;
            }
            symbol_minus = 0;
            numbers_points = 0;
            counterXY++;
            space++;
            continue;
        }
        if (counterXY == 1 && isdigit(arr[*i]) && countX > 0) {
            geo->poligon[geo->size_poligon - 1].points[point_number].y
                    = arr[*i] - '0' + (geo->poligon[geo->size_poligon - 1].points[point_number].y * 10);
            numbers_points++;
            countY++;
            continue;
        } else if (countX == 0) {
            (*i)--;

            return 18;
        }

        if (arr[*i] == ',') {
            if (numbers_points > 0) {
                if (counterXY == 1 && symbol_minus == 1) {
                    geo->poligon[geo->size_poligon - 1].points[point_number].y *= -1;
                }
                symbol_minus = 0;
                numbers_points = 0;
                point_number++;
                counterXY -= 2;
                space -= 2;
                countY = 0;
                countX = 0;
                continue;
            }
            return 18;
        }

        if (numbers_points == 0) {
            if (arr[(*i) - 1] == ',') {
                (*i)--;
                return 18;
            }

            return 18;
        }

        if ((numbers_points > 0) && (arr[*i] == ')')) {
            if (arr[++(*i)] == ')') {
                if (counterXY == 1 && symbol_minus == 1) {
                    geo->poligon[geo->size_poligon - 1].points[point_number].y *= -1;
                }
                last_symbol = 1;
                break;
            }
            return 16;
        }
        return 20;
    }
    if (countY == 0) {
        (*i)--;

        return 18;
    }
    if (last_symbol == 1) {
        if (geo->poligon[geo->size_poligon - 1].points[point_number].x == geo->poligon[geo->size_poligon - 1].points[0].x
            && geo->poligon[geo->size_poligon - 1].points[point_number].y == geo->poligon[geo->size_poligon - 1].points[0].y) {
            return -1;
        } else {
            (*i)--;
            return 15;
        }
    } else {
        (*i)++;
        return 16;
    }
    return -1;
}
int processing_poligon(int* i, int size, char* arr, Geometry* geo, int row_count)
{
    int error;
    free(geo->poligon[geo->size_poligon - 1].points);
    geo->poligon[geo->size_poligon - 1].numeral_points = 0;
    int_geometry_push_poligon_point(geo);
    int_geometry_push_poligon_point(geo);
    int_geometry_push_poligon_point(geo);
    int_geometry_push_poligon_point(geo);
    if ((error = processing_first_coordinates_poligon(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    if ((error = processing_next_coordinates_poligon(i, size, arr, geo)) != -1) {
        error_handling(i, size, arr, error, row_count);
        return -1;
    }
    poligon_perimeter_calculation(geo);
    poligon_area_calculation(geo);
    geo->poligon[geo->size_poligon - 1].serial_number = geo->serial_number++;
    int_geometry_push_poligon(geo);
    return 0;
}
