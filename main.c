#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>
#include "geometry.h"
#include "innput.h"

int main()
{
	Geometry *geo = int_geometry(1);

	//Wrong_input *wronger = init_wrong_input(1);

	char arr[1100];

	FILE* myfile;
	myfile = fopen("geo.txt", "r");

	if (myfile == NULL) {
		printf("No file\n");
		return 1;
	}
	int i;
	// реалочить по кд
	int j;
	int k = 1;
	int l = 0;
	int circle_letter;
	int triangle_letter;
	int number_figure;
	int symbol_minus;
	int numbers_point;
	int point_split;
	char first_symbol;
	int powka = 1;
	int wrong_step;
	int triangle_number = 0;



	for (i = 0, point_split = 0, triangle_letter = 0, circle_letter = 0, number_figure = 1, symbol_minus = 0, numbers_point = 0; (arr[i] = fgetc (myfile)) != EOF; i++) {
		if (arr[i] == '\n' && l == 0) {
			printf("\nError: invalid input format\n");

		}
		if (arr[i] == '\n') {
			k = 1;
			circle_letter = 0;
			continue; //?
		}
		if (k == 1) {
			first_symbol = arr[i];
			if (first_symbol == 'c') l = 1;
			if (first_symbol == 't') l = 2;
			if (first_symbol == 'p') l = 3;
			k = 0;
		}
		if (wrong_step > 0 && circle_letter == -1) { // ?ждать ввода \n

			for(int abc = 0; abc <= wrong_step; abc++) {
				printf("%c", arr[i - wrong_step + abc - 1]); //создать структуру данных с порядковый номером типа float
			}
			wrong_step = 0;
		}
		if (circle_letter == -1) {
			l = 0;
			circle_letter = -2;
			numbers_point = 0;
			geo->circle[geo->size_circle - 1].point.y = geo->circle[geo->size_circle - 1].point.x = geo->circle[geo->size_circle - 1].radius = 0;
			symbol_minus = 0;
			point_split = 0;
		}

		switch (l) { // внутри сделать проверку на правильность ввода, если нет - не записывать в структуру (отдельными функциями) (что, радиус не меньше/равен 0, в треуг все точки не лежат на одной прямой)
			case 0:
			printf("%c", arr[i]);
			break;
			case 1:
			switch(circle_letter) {
				case 0:
				if (arr[i] == 'c') circle_letter++;
				else circle_letter = -1;
				break;
				case 1:
				wrong_step++;
				if (arr[i] == 'i') circle_letter++;
				else circle_letter = -1;
				break;
				case 2:
				wrong_step++;
				if (arr[i] == 'r') circle_letter++;
				else circle_letter = -1;
				break;
				case 3:
				wrong_step++;
				if (arr[i] == 'c') circle_letter++;
				else circle_letter = -1;
				break;
				case 4:
				wrong_step++;
				if (arr[i] == 'l') circle_letter++;
				else circle_letter = -1;
				break;
				case 5:
				wrong_step++;
				if (arr[i] == 'e') circle_letter++;
				else circle_letter = -1;
				break;
				case 6:
				wrong_step++;
				if (arr[i] == '(') circle_letter++;
				else circle_letter = -1;
				break;
				case 7:
				wrong_step++;
				if (isdigit(arr[i]) && symbol_minus <= 1) {
					geo->circle[geo->size_circle - 1].point.x = arr[i] - '0' + (geo->circle[geo->size_circle - 1].point.x * 10);
					numbers_point++;
				} else if (arr[i] == '-' && numbers_point == 0) {
					symbol_minus++;
				} else if (arr[i] == ' ' && numbers_point != 0) {
					circle_letter++;
					if (symbol_minus == 1) geo->circle[geo->size_circle - 1].point.x *= -1;
					numbers_point = 0;
					symbol_minus = 0;
				} else circle_letter = -1;
				break;
				case 8:
				wrong_step++;
				if (isdigit(arr[i]) && symbol_minus <= 1) {
					geo->circle[geo->size_circle - 1].point.y = arr[i] - '0' + (geo->circle[geo->size_circle - 1].point.y * 10);
					numbers_point++;
				} else if (arr[i] == '-' && numbers_point == 0) {
					symbol_minus++;
				} else if (arr[i] == ',' && numbers_point != 0) {
					circle_letter++;
					if (symbol_minus == 1) geo->circle[geo->size_circle - 1].point.y *= -1;
					numbers_point = 0;
					symbol_minus = 0;
				} else circle_letter = -1;
				break;
				case 9:
				wrong_step++;
				if (arr[i] == ' ') circle_letter++;
				else circle_letter = -1;
				break;
				case 10:
				wrong_step++;
				if (isdigit(arr[i]) && point_split == 0) {
					geo->circle[geo->size_circle - 1].radius = arr[i] - '0' +	(geo->circle[geo->size_circle - 1].radius * 10);
					numbers_point++;
				} else if (numbers_point != 0 && arr[i] == '.') {
					point_split++;
				} else if (isdigit(arr[i]) && point_split == 1 && numbers_point != 0) {
					geo->circle[geo->size_circle - 1].radius += (float)(arr[i] - '0') / pow(10, powka);
					powka++;
				} else if (arr[i] == ')') {
					circle_letter++;
					if (geo->circle[geo->size_circle - 1].radius == 0) {
						point_split = 0;
						powka = 1;
						numbers_point = 0;

						circle_letter = -1;

						numbers_point = 0;
						geo->circle[geo->size_circle - 1].point.y = geo->circle[geo->size_circle - 1].point.x = geo->circle[geo->size_circle - 1].radius = 0;
						symbol_minus = 0;
						point_split = 0;

						for(int abc = 0; abc <= wrong_step; abc++) {
							printf("%c", arr[i - wrong_step + abc]); //создать структуру данных с порядковый номером типа float
						}
						printf("\nError: invalid circle\n");
						wrong_step = 0;
						break;
					}
					geo->circle[geo->size_circle - 1].serial_number = number_figure;
					int_geometry_push_circle(geo);
					number_figure++;
					point_split = 0;
					powka = 1;
					numbers_point = 0;
					wrong_step = 0;
				} else circle_letter = -1;
				break;
				case -1:
				numbers_point = 0;
				geo->circle[geo->size_circle - 1].point.y = geo->circle[geo->size_circle - 1].point.x = geo->circle[geo->size_circle - 1].radius = 0;
				symbol_minus = 0;
				point_split = 0;
				default:
				break;
			}
			break;
			// case 2:
			// switch (triangle_letter) {
			// 	case 0:
			// 	if (arr[i] == 't') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 1:
			// 	wrong_step++;
			// 	if (arr[i] == 'r') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 2:
			// 	wrong_step++;
			// 	if (arr[i] == 'i') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 3:
			// 	wrong_step++;
			// 	if (arr[i] == 'a') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 4:
			// 	wrong_step++;
			// 	if (arr[i] == 'n') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 5:
			// 	wrong_step++;
			// 	if (arr[i] == 'g') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 6:
			// 	wrong_step++;
			// 	if (arr[i] == 'l') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 7:
			// 	wrong_step++;
			// 	if (arr[i] == 'e') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 8:
			// 	wrong_step++;
			// 	if (arr[i] == '(') triangle_letter++;
			// 	else triangle_letter = -1;
			// 	break;
			// 	case 7:
			// 	wrong_step++;
			// 	if (isdigit(arr[i]) && symbol_minus <= 1) {
			// 		geo->triangle[geo->size_triangle - 1].point.x = arr[i] - '0' + (geo->triangle[geo->size_triangle - 1].point.x * 10);
			// 		numbers_point++;
			// 	} else if (arr[i] == '-' && numbers_point == 0) {
			// 		symbol_minus++;
			// 	} else if (arr[i] == ' ' && numbers_point != 0) {
			// 		triangle_letter++;
			// 		if (symbol_minus == 1) geo->triangle[geo->size_triangle - 1].point.x *= -1;
			// 		numbers_point = 0;
			// 		symbol_minus = 0;
			// 	} else triangle_letter = -1;
			// 	break;
			// 	default:
			// 	break;
			// }
			// break;
			default:
			break;
		}
	}

	//сравнение порядков номеров if () вызываем соответственный

	for(int g = 0; g < geo->size_circle - 1; g++) {
		printf("%ld %d %d %.3f\n", geo->circle[g].serial_number, geo->circle[g].point.x, geo->circle[g].point.y, geo->circle[g].radius);
	}

	printf("%d\n", geo->triangle[0].point[2].x);
	int_geometry_push_triangle(geo);
	geo->triangle[1].point[3].x = 5;
	printf("%d\n", geo->triangle[1].point[3].x);

	fclose(myfile);

	return 0;
}

// при пересечении фигур добавить в структуры данные о пересечении (1 фигуры и 2 фигуры)
