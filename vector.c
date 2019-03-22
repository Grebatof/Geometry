#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "vector.h"

IntVector *int_vector_new(size_t initial_capacity) {
	IntVector *v = malloc(sizeof(*v));
	if (v != NULL &&  initial_capacity > 0) {
		v->data = malloc(sizeof(int) * initial_capacity);
		v->size = 0;
		v->capacity = initial_capacity;
		if (v->data == NULL) printf("WARNING! ARRAY IS NULL\n");
	}
	return v;
}

IntVector *int_vector_copy(const IntVector *v) {
	IntVector *vc = int_vector_new(v->capacity);
	for (int i = 0; i < v->size; i++) {
		vc->data[i] = v->data[i];
	}
	vc->size = v->size;
	return vc;
}

void int_vector_free(IntVector *v) {
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index) {
	if (index > v->size || v->data == NULL) {
		printf("Wrond index, try again\n");
		return 0;
	}
	int number = v->data[--index];
	return number;
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
	if (index > v->size || v->data == NULL) {
		printf("Wrond index, try again\n");
		return;
	}
	v->data[--index] = item;
}

size_t int_vector_get_size(const IntVector *v) {
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v) {
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item) {
	if (v->data == NULL || v == NULL) return -1;
	if (v->capacity == 0) v->capacity = 2;
	if (v->size == v->capacity) {
		v->capacity *= 2;
		v->data = realloc(v->data, v->capacity * sizeof(int));
	}
	v->size++;
	v->data[v->size - 1] = item;
	return 0;
}

void int_vector_pop_back(IntVector *v) {
	if (v->size != 0) {
		v->data[--(v->size)] = 0;
	}
}

int int_vector_shrink_to_fit(IntVector *v) {
	if (v->size != v->capacity && v->data != NULL && v != NULL) {
		int *array = malloc(v->size * sizeof(int));
		for (int i = 0; i < v->size; i++) {
			*(array + i) = v->data[i];
		}
		free(v->data);
		v->data = array;
		v->capacity = v->size;
		return 0;
	}
	return -1;
}

int int_vector_resize(IntVector *v, size_t new_size) {
	if (new_size > v->capacity || new_size < 0 || v->data == NULL || v == NULL) return -1;
	if (new_size > v->size) {
		int EOA = v->size - 1;
		v->size = new_size;
		for (int i = EOA; i < (new_size - 1); i++) {
			v->data[i] = 0;
		}
	}
	if (new_size < v->size) {
		v->size = new_size;
	}
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity) {
	if (new_capacity > v->capacity || v->data == NULL) {
		v->capacity = new_capacity;
		v->data = realloc(v->data, new_capacity * sizeof(int));
		return 0;
	}
	return -1;
}