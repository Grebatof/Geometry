#ifndef _INNPUT_H_
#define _INNPUT_H_

typedef struct {
  char word[20];
  char garbage[20];
  size_t size;
  float serial_number;
} Wrong_input;

Wrong_input *init_wrong_input(size_t initial_wronger);
void increase_wrong_input(Wrong_input *wronger);

#endif
