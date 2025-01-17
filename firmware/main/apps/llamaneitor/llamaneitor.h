#pragma once
#include "general/bitmaps_general.h"
#include "general/general_screens.h"

#define HISTORY_MENU_COUNT 40
#define HISTORY_CONT_COUNT 89

typedef enum { CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHARS_NUM } characteres_e;

typedef struct {
  const unsigned char *bitmap;
  uint8_t width;
  uint8_t height;
} epd_bitmap_props_t;

typedef struct {
  epd_bitmap_props_t character_bitmap;
  char *cats_unlocked[3];
} game_ctx_t;

const unsigned char llamaneitor_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x0c, 0x18, 0x00,
    0x00, 0x0c, 0x18, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x00, 0x1e, 0x18, 0x00,
    0x00, 0x1c, 0x18, 0x00, 0x00, 0x0c, 0x98, 0x00, 0x00, 0x0f, 0x98, 0x00,
    0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xd0, 0x00, 0x00, 0x05, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1f, 0xd0, 0x00,
    0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xb0, 0x00, 0x00, 0x1f, 0xf8, 0x00,
    0x00, 0x1f, 0xf8, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00,
    0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00,
    0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00,
    0x00, 0x0f, 0xe0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// 'Character 1', 32x32px
const unsigned char epd_bitmap_char1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xc0, 0x00, 0x00, 0x1b, 0xe0, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x40, 0x48, 0x00, 0x00, 0x01, 0x98, 0x00,
    0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x1c, 0x00, 0x01, 0x90, 0xc6, 0x00, 0x01, 0x10, 0x42, 0x00,
    0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x04, 0xe0, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// 'Character 2', 32x32px
const unsigned char epd_bitmap_char2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x0c, 0xc0, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x3c, 0xc0, 0x00,
    0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x1f, 0xf0, 0x00,
    0x00, 0x3f, 0xf8, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x7f, 0xf8, 0x00,
    0x00, 0x7f, 0xb8, 0x00, 0x00, 0xdf, 0x66, 0x00, 0x00, 0xdf, 0xce, 0x00,
    0x00, 0xde, 0x5e, 0x00, 0x00, 0x40, 0x5e, 0x00, 0x00, 0xc0, 0xc0, 0x38,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x02,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// 'Character 3', 32x32px
const unsigned char epd_bitmap_char3[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x0f, 0x38, 0x00,
    0x00, 0x0b, 0xe8, 0x00, 0x00, 0x0b, 0xe8, 0x00, 0x00, 0x06, 0x30, 0x00,
    0x00, 0x04, 0x90, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x06, 0xb0, 0x00,
    0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00,
    0x00, 0x02, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x0e, 0x20, 0x00,
    0x00, 0x1e, 0x30, 0x00, 0x00, 0x1e, 0x30, 0x00, 0x00, 0x1e, 0x38, 0x00,
    0x00, 0x1e, 0x38, 0x00, 0x00, 0x1c, 0x18, 0x00, 0x00, 0x1c, 0x18, 0x00,
    0x00, 0x1c, 0x18, 0x00, 0x00, 0x1c, 0x10, 0x00, 0x00, 0x1e, 0x30, 0x00,
    0x00, 0x08, 0x90, 0x00, 0x00, 0x0a, 0xa0, 0x00, 0x00, 0x0a, 0xa0, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00};

// 'White Rabbit', 32x32px
const unsigned char white_rabbit_bitmap[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x38, 0x00,
    0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x01, 0xf8, 0x00,
    0x00, 0x03, 0xfc, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x1f, 0xfe, 0x00,
    0x00, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xfe, 0x00,
    0x00, 0x7f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x7f, 0x9c, 0x00,
    0x00, 0x7f, 0x9c, 0x00, 0x00, 0x7f, 0x18, 0x00, 0x00, 0x3f, 0x00, 0x00,
    0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// 'Pineapple', 32x32px
const unsigned char pineapple_item[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x06,
    0x60, 0x0c, 0x00, 0x06, 0x20, 0x0c, 0x00, 0x04, 0x20, 0x0c, 0x00, 0x04,
    0x20, 0x0c, 0x00, 0x04, 0x20, 0x0c, 0x00, 0x04, 0x20, 0x0c, 0x00, 0x00,
    0x20, 0x0c, 0x00, 0x04, 0x30, 0x0c, 0x00, 0x04, 0x30, 0x0e, 0x00, 0x04,
    0x30, 0x0e, 0x00, 0x0c, 0x70, 0x0e, 0x00, 0x0c, 0x78, 0x06, 0x00, 0x0c,
    0x30, 0x0e, 0x00, 0x0c, 0x38, 0x06, 0x00, 0x0c, 0x38, 0x06, 0x00, 0x0c,
    0x38, 0x06, 0x00, 0x0c, 0x38, 0x06, 0x00, 0x0c, 0x38, 0x06, 0x00, 0x0c,
    0x38, 0x06, 0x00, 0x0c, 0x38, 0x84, 0x00, 0x0c, 0x1d, 0x00, 0x00, 0x0c,
    0x1d, 0xc0, 0x00, 0x3c, 0x1f, 0xf0, 0x00, 0xfc, 0x1f, 0xfc, 0x0f, 0xfc,
    0x1c, 0x7f, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x07, 0xfc, 0x00,
    0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00};

const epd_bitmap_props_t epd_bitmap_char1_props = {
    .bitmap = epd_bitmap_char1, .width = 32, .height = 32};

const epd_bitmap_props_t epd_bitmap_char2_props = {
    .bitmap = epd_bitmap_char2, .width = 32, .height = 32};

const epd_bitmap_props_t epd_bitmap_char3_props = {
    .bitmap = epd_bitmap_char3, .width = 32, .height = 32};

const epd_bitmap_props_t epd_bitmap_char4_props = {
    .bitmap = epd_bitmap_baby_dragon_ss, .width = 32, .height = 32};

const epd_bitmap_props_t epd_bitmap_white_rabbit = {
    .bitmap = white_rabbit_bitmap, .width = 32, .height = 32};

const epd_bitmap_props_t epd_bitmap_pineapple = {
    .bitmap = pineapple_item, .width = 32, .height = 32};

epd_bitmap_props_t characters[CHARS_NUM] = {
    epd_bitmap_char1_props, epd_bitmap_char2_props, epd_bitmap_char3_props,
    epd_bitmap_char4_props};

char *history_menu_items[HISTORY_MENU_COUNT] = {
    "Vengo de hace",   "20 a\32os en",    "el futuro",      "              ",
    "              ",  "El mundo esta",   "gobernado por",  "la inteligencia",
    "artificial",      "EKONet y la",     "humanidad",      "ahora es",
    "prisionera,",     "me he",           "instalado en",   "este",
    "dispositivo",     "y necesito la",   "ayuda de un",    "maestro del",
    "cyber hacking",   "y creo que",      "puedes ser tu",
    "      ...     ", // 20
    "... Para evitar", "el fin de la",    "humanidad",      "en el futuro",
    "es necesario",    "que hagamos",     "algunas cosas",  "para cambiar",
    "el futuro,",      "cosas sencillas", "pero que haran", "para vencer a",
    "      ...     ", // 38
    "              ",  "Me puedes",       "ayudar?",
};

char *history_continue[HISTORY_CONT_COUNT] = {
    " Excelente, ",
    "sabia que ",
    "habia",
    "encontrado al",
    "hacker adecuado",
    "              ",
    "Hace 20 a\32os",
    "En tu presente",
    "en el 2024",
    "     ...      ",
    "              ",
    "Se cumplia el",
    "20 aniversario",
    "de la EkoParty."
    "Este encuentro",
    "es determinante",
    "para el futuro",
    "de la humanidad",
    "y la ",
    "inteligencia",
    "artificial,",
    "te orientare",
    "durante las 3",
    "misiones",
    "principales",
    "para conseguir",
    "los 3 gatos",
    "que indicaran",
    "que hemos",
    "cambiado el",
    "futuro para",
    "bien",
    "      ...     ",
    "No se",
    "exactamente",
    "que hay que",
    "hacer, pero tu",
    "badge cuenta",
    "con",
    "tecnologia que",
    "detecta en que",
    "lugar te",
    "encuentras,",
    "podras",
    "interacturar",
    "con las villas",
    "y lugares de",
    "la eko, que",
    "activaran",
    "acciones, sal",
    "a buscar la",
    "aventura y",
    "platica con ",
    "otros",
    "aventureros",
    "      ...     ",
    "Hay algunas",
    "misiones",
    "alternativas",
    "que podras",
    "realizar si",
    "gustas,",
    "cambiaran cosas",
    "de tu vida como",
    "si vas a tener",
    "novia o no,",
    "pero no es muy",
    "relevante",
    "      ...     ",
    "Por ultimo se",
    "me olvidaba,",
    "cuentas con",
    "una llama de",
    "vida que ",
    "deberas",
    "cuidar y no",
    "dejar que se",
    "apague en los",
    "siguientes dias",
    "cuidala o",
    "realiza",
    "actividades para",
    "mantenerla",
    "fuerte y",
    "seguir en la",
    "travesia",
    "              ",
    "              ",
    "Sigue al conejo",
    "blanco ...",
};

typedef enum {
  MENU_HISTORY = 0,
  MENU_CHARACTER,
  MENU_MISSIONS,
  MENU_INVENTORY,
  MENU_GM_COUNT
} main_menu_t;

const char *main_menu_items[MENU_GM_COUNT] = {
    "Personaje",
    "Misiones",
    "Inventario",
};

void llamaneitor_begin();
void llamaneitor_menu_begin();
game_ctx_t *llamaneitor_get_game_ctx();