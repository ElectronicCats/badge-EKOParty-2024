#pragma once

#include <stdbool.h>
#include <stdio.h>

#define MISION1_COUNT 29
#define MISION1_PREAMBLE 51
#define MISION1_PATAGON 43
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
char* mission_1_hardware[MISION1_COUNT] = {
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

char* mission_1_patagon[MISION1_PATAGON] = {
  "... El badge",
  "detecta algo...",
  "             ",
  "             ",
  "El espacio",
  "es un lugar",
  "donde la",
  "tecnologia",
  "es la unica",
  "forma de",
  "sobrevivir",
  "             ",
  "             ",
  "- El equipo de",
  "ingenieros",
  "necesita ayuda",
  "para arreglar",
  "el transbordador",
  "espacial",
  "             ",
  "             ",
  "Maldita sea!",
  "- piensas -",
  "No puede ser",
  "todo tan",
  "complicado, apenas",
  "comenzamos y ya",
  "parece un",
  "obstaculo",
  "insalvable",
  "             ",
  "             ",
  "Ya en voz alta:",
  "- No hay otra",
  "forma de ayudar",
  "a los patagon,",
  "necesito un ",
  "cautin, urgente!",
  "             ",
  "             ",
  "- NUEVA MISION -",
  "             ",
};

char* mission_1_text[MISION1_PREAMBLE] = {
  "... El badge",
  "detecta algo...",
  "             ",
  "             ",
  "La comunidad",
  "de hardware es",
  "un lugar",
  "tranquilo",
  "donde las",
  "tecnicas se",
  "dejan la vision",
  "trabajando con",
  "precision",
  "milimetra",
  "los dise\32os",
  "y probandolos",
  "para que",
  "funcionen bajo",
  "circunstancias",
  "extremas",
  "             ",
  "             ",
  "- El equipo de",
  "labotorio no se",
  "presta... ",
  "- comenta la",
  "jefa de taller.",
  "             ",
  "             ",
  "Maldita sea!",
  "- piensas -",
  "No puede ser",
  "todo tan",
  "complicado, apenas",
  "comenzamos y ya",
  "parece un",
  "obstaculo",
  "insalvable",
  "             ",
  "             ",
  "Ya en voz alta:",
  "- No hay otra",
  "forma de ayudar",
  "a los patagon,",
  "necesito un ",
  "cautin, urgente!",
  "             ",
  "             ",
  "- NUEVA MISION -",
  "             ",
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
void show_mission_screen(uint8_t village_idx);
bool mission_get_state();