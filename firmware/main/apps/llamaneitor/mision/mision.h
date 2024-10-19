#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MISION1_COUNT 19

typedef enum {
  MISION_1,
  MISION_2,
  MISION_3,
  MISION_COUNT
} mision_t;

char* list_mision[MISION_COUNT] = {
  "Mision 1",
  "Mision 2",
  "Mision 3",
};


char* mision_1[MISION1_COUNT] = {
  "La Villa",
  "PatagonSpace",
  "se le ha",
  "rompido uno de",
  "sus dispositivos",
  "necesitamos algo",
  "para poder ",
  "volver a soldar",
  "     ...     ",
  "puedes ayudarlos",
  "buscando algo",
  "con los amigos?",
  "             ",
  "             ",
  "             ",
  "             ",
  "Pista: Soldar?",
  "Hardware?",
  "/(O.O)/"
};

void mision_register_cb_exit(void* cb);
void mision_begin();