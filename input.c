#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>
#include "geometry.h"
#include "input.h"

Wrong_input *init_wrong_input(size_t initial_wronger) {
  Wrong_input *wronger = malloc(sizeof(*wronger));
  if (wronger != NULL) {
    wronger->size = 1;
  }
  return wronger;
}

void increase_wrong_input(Wrong_input *wronger) {
  wronger->size += 1;
  wronger = realloc(wronger, wronger->size * sizeof(*wronger));
}
