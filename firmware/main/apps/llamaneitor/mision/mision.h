#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MISION1_COUNT 29
#define MISION2_COUNT 21

typedef enum {
  MISION_1,
  MISION_2,
  MISION_3,
  MISION_COUNT
} mision_t;

char* list_mision[MISION_COUNT] = {
  "Sin encontrar",
  "Sin encontrar",
  "Sin encontrar",
};

// PatagonSpace - Hardware village
char* mision_1[MISION1_COUNT] = {
  "No es posible",
  "conseguir que",
  "se desarrrolle",
  "el combustible",
  "ekologico para",
  "los",
  "transbordadores",
  "en el espacio",
  "si no",
  "conseguimos",
  "arreglar este",
  "tema el problema",
  "no parece ser",
  "demasiado grave,",
  "solo retrasara el",
  "lanzamiento. Pero",
  "vas a necesitar",
  "herramientas",
  "     ...     ",
  "             ",
  "puedes ayudarlos",
  "buscando algo",
  "con los amigos?",
  "             ",
  "             ",
  "             ",
  "             ",
  "Pista: Soldar?",
  "Hardware?",
};

// Yes we hack - EC Villages
char* mision_2[MISION2_COUNT] = {
  "Esto es un reto",
  "no? ...",
  "Debemos ganar,",
  "YES WE HACK!!",
  "Que interesante",
  "esto de hackear",
  "no?",
  "Tal vez decirlo",
  "nos otorgue",
  "poderes o addons",
  "             ",
  "             ",
  "             ",
  "             ",
  "     Espera!    ",
  "Oh los gatos!",
  "a los gatos les",
  "gustan los addons",
  "si tienes uno",
  "tal vez les",
  "guste verlo"
};

void mision_register_cb_exit(void* cb);
void mision_begin();
void mision_enter_code();