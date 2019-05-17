#include "geometry.h"
#include "input.h"
#include "processing.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intersects(Geometry* geo)
{
  int number_circle = 0, number_circle2;
  int number_triangle = 0, number_triangle2;
  int number_poligon = 0, number_poligon2;
  int i, a, b, c, j, v;
  float a1, b1, c1, r;
  int size1, size2;
  float aa, ab, ac, ad, ar, ba, bb, bc, bd, br;
  int t, y, u;
  int outside_point, inside_point;
  int serial_number = geo->serial_number;
  int shape_serial_number, shape_serial_number2;
  int error;

  for (j = 1; j < serial_number - 1; j++) {
      shape_serial_number = geo->circle[number_circle].serial_number;
      if (j == shape_serial_number) {
        number_circle2 = number_circle + 1;
        number_triangle2 = 0;
        number_poligon2 = 0;
        v = a = b = c = t = y = u = 0;
        for (i = 1; i < serial_number; i++) {
          outside_point = inside_point = 0;
          shape_serial_number2 = geo->circle[number_circle2].serial_number;
          if (i == shape_serial_number2) {
            if (distance_between_points(geo->circle[number_circle2].point, geo->circle[number_circle].point) > (geo->circle[number_circle2].radius + geo->circle[number_circle].radius)) {
              number_circle2++;
              continue;
            }
            while(1) {
              if (geo->circle[number_circle].intersects[v + a].serial_number != 0) {
                a++;
                continue;
              }
              break;
            }
            geo->circle[number_circle].intersects[v + a].serial_number = shape_serial_number2;
            geo->circle[number_circle].intersects[v + a].name = 1;
            geo->circle[number_circle2].intersects[v].serial_number = shape_serial_number;
            geo->circle[number_circle2].intersects[v].name = 1;
            v++;
            number_circle2++;
            continue;
          }
          shape_serial_number2 = geo->triangle[number_triangle2].serial_number;
          if (i == shape_serial_number2) {
            a1 = distance_between_points(geo->circle[number_circle].point, geo->triangle[number_triangle2].point[0]);
            b1 = distance_between_points(geo->circle[number_circle].point, geo->triangle[number_triangle2].point[1]);
            c1 = distance_between_points(geo->circle[number_circle].point, geo->triangle[number_triangle2].point[2]);
            r = geo->circle[number_circle].radius;
            if (!((a1 > r || b1 > r || c1 > r) && (a1 <= r || b1 <= r || c1 <= r))) {
              number_triangle2++;
              continue;
            }
            while(1) {
              if (geo->circle[number_circle].intersects[v + b].serial_number != 0) {
                b++;
                continue;
              }
              break;
            }
            geo->circle[number_circle].intersects[v + b].serial_number = shape_serial_number2;
            geo->circle[number_circle].intersects[v + b].name = 2;
            geo->triangle[number_triangle2].intersects[t].serial_number = shape_serial_number;
            geo->triangle[number_triangle2].intersects[t].name = 1;
            t++;
            v++;
            number_triangle2++;
            continue;
          }
          shape_serial_number2 = geo->poligon[number_poligon2].serial_number;
          if (i == shape_serial_number2) {
            r = geo->circle[number_circle].radius;
            size1 = geo->poligon[number_poligon2].numeral_points - 1;
            for (int qwe = 0; qwe < size1; qwe++) {
              a1 = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->circle[number_circle].point);
              if (a1 > r) {
                outside_point++;
              } else {
                inside_point++;
              }
            }
            if (!(outside_point > 0 && inside_point > 0)) {
              number_poligon2++;
              continue;
            }
            while(1) {
              if (geo->circle[number_circle].intersects[v + c].serial_number != 0) {
                c++;
                continue;
              }
              break;
            }
            geo->circle[number_circle].intersects[v + c].serial_number = shape_serial_number2;
            geo->circle[number_circle].intersects[v + c].name = 3;
            geo->poligon[number_poligon2].intersects[y].serial_number = shape_serial_number;
            geo->poligon[number_poligon2].intersects[y].name = 1;
            y++;
            v++;
            number_poligon2++;
            continue;
          }
        }
        number_circle++;
        continue;
      }
      shape_serial_number = geo->triangle[number_triangle].serial_number;
      if (j == shape_serial_number) {
        number_triangle2 = number_triangle + 1;
        number_poligon2 = 0;
        v = a = b = c = t = y = u = 0;
        for (i = 1; i < serial_number; i++) {
          error = 0;
          shape_serial_number2 = geo->triangle[number_triangle2].serial_number;
          if (i == shape_serial_number2) {
            for (int qwe = 0; qwe < 3; qwe++) {
              for (int qwert = 0; qwert < 3; qwert++) {
                aa = distance_between_points(geo->triangle[number_triangle2].point[qwe], geo->triangle[number_triangle].point[qwert]);
                ab = distance_between_points(geo->triangle[number_triangle2].point[qwe], geo->triangle[number_triangle].point[qwert + 1]);

                ar = distance_between_points(geo->triangle[number_triangle2].point[qwe], geo->triangle[number_triangle2].point[qwe + 1]);

                ac = distance_between_points(geo->triangle[number_triangle2].point[qwe + 1], geo->triangle[number_triangle].point[qwert]);
                ad = distance_between_points(geo->triangle[number_triangle2].point[qwe + 1], geo->triangle[number_triangle].point[qwert + 1]);

                ba = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->triangle[number_triangle2].point[qwe]);
                bb = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->triangle[number_triangle2].point[qwe + 1]);

                br = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->triangle[number_triangle].point[qwert + 1]);

                bc = distance_between_points(geo->triangle[number_triangle].point[qwert + 1], geo->triangle[number_triangle2].point[qwe]);
                bd = distance_between_points(geo->triangle[number_triangle].point[qwert + 1], geo->triangle[number_triangle2].point[qwe + 1]);
                if (!((aa < ar && ab < ar && ac < ar && ad < ar) || (ba < br && bb < br && bc < br && bd < br))) {
                  error++;
                }
              }
            }
            if (error == 0) {
              number_poligon2++;
              continue;
            }
            while(1) {
              if (geo->triangle[number_triangle].intersects[v + b].serial_number != 0) {
                b++;
                continue;
              }
              break;
            }
            geo->triangle[number_triangle].intersects[v + b].serial_number = shape_serial_number2;
            geo->triangle[number_triangle].intersects[v + b].name = 2;
            geo->triangle[number_triangle2].intersects[y].serial_number = shape_serial_number;
            geo->triangle[number_triangle2].intersects[y].name = 2;
            y++;
            v++;
            number_poligon2++;
            continue;
          }
          shape_serial_number2 = geo->poligon[number_poligon2].serial_number;
          if (i == shape_serial_number2) {
            size2 = geo->poligon[number_poligon2].numeral_points - 2;
            for (int qwert = 0; qwert < 3; qwert++) {
              for (int qwe = 0; qwe < size2; qwe++) {
                aa = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->triangle[number_triangle].point[qwert]);
                ab = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->triangle[number_triangle].point[qwert + 1]);

                ar = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->poligon[number_poligon2].points[qwe + 1]);

                ac = distance_between_points(geo->poligon[number_poligon2].points[qwe + 1], geo->triangle[number_triangle].point[qwert]);
                ad = distance_between_points(geo->poligon[number_poligon2].points[qwe + 1], geo->triangle[number_triangle].point[qwert + 1]);

                ba = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->poligon[number_poligon2].points[qwe]);
                bb = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->poligon[number_poligon2].points[qwe + 1]);

                br = distance_between_points(geo->triangle[number_triangle].point[qwert], geo->triangle[number_triangle].point[qwert + 1]);

                bc = distance_between_points(geo->triangle[number_triangle].point[qwert + 1], geo->poligon[number_poligon2].points[qwe]);
                bd = distance_between_points(geo->triangle[number_triangle].point[qwert + 1], geo->poligon[number_poligon2].points[qwe + 1]);
                if (!((aa < ar && ab < ar && ac < ar && ad < ar) || (ba < br && bb < br && bc < br && bd < br))) {
                  error++;
                }
              }
            }
            if (error == 0) {
              number_poligon2++;
              continue;
            }
            while(1) {
              if (geo->triangle[number_triangle].intersects[v + c].serial_number != 0) {
                c++;
                continue;
              }
              break;
            }
            geo->triangle[number_triangle].intersects[v + c].serial_number = shape_serial_number2;
            geo->triangle[number_triangle].intersects[v + c].name = 3;
            geo->poligon[number_poligon2].intersects[t].serial_number = shape_serial_number;
            geo->poligon[number_poligon2].intersects[t].name = 2;
            t++;
            v++;
            number_poligon2++;
            continue;
          }
        }
          number_triangle++;
          continue;
      }
      shape_serial_number = geo->poligon[number_poligon].serial_number;
      if (j == shape_serial_number) {
        number_poligon2 = number_poligon + 1;
        v = a = b = c = t = y = u = 0;
        y += 3;
        for (i = 1; i < serial_number; i++) {
          error = 0;
          shape_serial_number2 = geo->poligon[number_poligon2].serial_number;
          if (i == shape_serial_number2) {
            size1 = geo->poligon[number_poligon2].numeral_points - 2;
            size2 = geo->poligon[number_poligon].numeral_points - 2;
            for (int qwe = 0; qwe < size1; qwe++) {
              for (int qwert = 0; qwert < size2; qwert++) {
                aa = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->poligon[number_poligon].points[qwert]);
                ab = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->poligon[number_poligon].points[qwert + 1]);

                ar = distance_between_points(geo->poligon[number_poligon2].points[qwe], geo->poligon[number_poligon2].points[qwe + 1]);

                ac = distance_between_points(geo->poligon[number_poligon2].points[qwe + 1], geo->poligon[number_poligon].points[qwert]);
                ad = distance_between_points(geo->poligon[number_poligon2].points[qwe + 1], geo->poligon[number_poligon].points[qwert + 1]);

                ba = distance_between_points(geo->poligon[number_poligon].points[qwert], geo->poligon[number_poligon2].points[qwe]);
                bb = distance_between_points(geo->poligon[number_poligon].points[qwert], geo->poligon[number_poligon2].points[qwe + 1]);

                br = distance_between_points(geo->poligon[number_poligon].points[qwert], geo->poligon[number_poligon].points[qwert + 1]);

                bc = distance_between_points(geo->poligon[number_poligon].points[qwert + 1], geo->poligon[number_poligon2].points[qwe]);
                bd = distance_between_points(geo->poligon[number_poligon].points[qwert + 1], geo->poligon[number_poligon2].points[qwe + 1]);
                if (!((aa < ar && ab < ar && ac < ar && ad < ar) || (ba < br && bb < br && bc < br && bd < br))) {
                  error++;
                }
              }
            }
            if (error == 0) {
              number_poligon2++;
              continue;
            }
            while(1) {
              if (geo->poligon[number_poligon].intersects[v + c].serial_number != 0) {
                c++;
                continue;
              }
              break;
            }
            geo->poligon[number_poligon].intersects[v + c].serial_number = shape_serial_number2;
            geo->poligon[number_poligon].intersects[v + c].name = 3;
            geo->poligon[number_poligon2].intersects[y].serial_number = shape_serial_number;
            geo->poligon[number_poligon2].intersects[y].name = 3;
            y++;
            v++;
            number_poligon2++;
            continue;
          }
        }
        number_poligon++;
        continue;
      }
  }
}

int main()
{
    Geometry* geo = int_geometry();

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

    intersects(geo);

    //сравнение порядков номеров if () вызываем соответственный

    int number_circle = 0;
    int number_triangle = 0;
    int number_poligon = 0;
    int k, v;
    int serial_number = geo->serial_number;
    int shape_serial_number;
    int points_poligon;

    //geo->circle[0].intersects[0].serial_number = 5;
    //printf("%d\n\n", geo->circle[0].intersects[0].serial_number);

    for (j = 1; j < serial_number; j++) {
        shape_serial_number = geo->circle[number_circle].serial_number;
        if (j == shape_serial_number) {
            printf("%ld.  circle(%d %d, %.3f)\n\n",
                   geo->circle[number_circle].serial_number,
                   geo->circle[number_circle].point.x,
                   geo->circle[number_circle].point.y,
                   geo->circle[number_circle].radius);
            printf("\tperimeter = %.3f\n", geo->circle[number_circle].perimeter);
            printf("\tarea = %.3f\n", geo->circle[number_circle].area);
            printf("\tintersects:\n");
            for (v = 0; v < 20; v++) {
              if (geo->circle[number_circle].intersects[v].serial_number != 0) {
                printf("\t\t%d. ", geo->circle[number_circle].intersects[v].serial_number);
                if (geo->circle[number_circle].intersects[v].name == 1) {
                  printf("circle\n");
                }
                if (geo->circle[number_circle].intersects[v].name == 2) {
                  printf("triangle\n");
                }
                if (geo->circle[number_circle].intersects[v].name == 3) {
                  printf("poligon\n");
                }
              }
            }
            printf("\n");
            number_circle++;
            continue;
        }
        shape_serial_number = geo->triangle[number_triangle].serial_number;
        if (j == shape_serial_number) {
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
            printf("\tintersects:\n");
            for (v = 0; v < 20; v++) {
              if (geo->triangle[number_triangle].intersects[v].serial_number != 0) {
                printf("\t\t%d. ", geo->triangle[number_triangle].intersects[v].serial_number);
                if (geo->triangle[number_triangle].intersects[v].name == 1) {
                  printf("circle\n");
                }
                if (geo->triangle[number_triangle].intersects[v].name == 2) {
                  printf("triangle\n");
                }
                if (geo->triangle[number_triangle].intersects[v].name == 3) {
                  printf("poligon\n");
                }
              }
            }
            printf("\n");
            number_triangle++;
            continue;
        }
        shape_serial_number = geo->poligon[number_poligon].serial_number;
        if (j == shape_serial_number) {
            points_poligon = geo->poligon[number_poligon].numeral_points - 2;
            printf("%ld.  poligon((%d %d,",
                   geo->poligon[number_poligon].serial_number,
                   geo->poligon[number_poligon].points[0].x,
                   geo->poligon[number_poligon].points[0].y);
            for (k = 1; k < points_poligon; k++) {
                printf(" %d %d,", geo->poligon[number_poligon].points[k].x, geo->poligon[number_poligon].points[k].y);
            }
            printf(" %d %d))\n\n", geo->poligon[number_poligon].points[k].x, geo->poligon[number_poligon].points[k].y);
            printf("\tperimeter = %.3f\n", geo->poligon[number_poligon].perimeter);
            printf("\tarea = %.3f\n", geo->poligon[number_poligon].area);
            printf("\tintersects:\n");
            for (v = 0; v < 20; v++) {
              if (geo->poligon[number_poligon].intersects[v].serial_number != 0) {
                printf("\t\t%d. ", geo->poligon[number_poligon].intersects[v].serial_number);
                if (geo->poligon[number_poligon].intersects[v].name == 1) {
                  printf("circle\n");
                }
                if (geo->poligon[number_poligon].intersects[v].name == 2) {
                  printf("triangle\n");
                }
                if (geo->poligon[number_poligon].intersects[v].name == 3) {
                  printf("poligon\n");
                }
              }
            }
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
