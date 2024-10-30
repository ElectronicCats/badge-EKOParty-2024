#pragma once

#include "llamaneitor.h"

#define CAT1_STR "Naranjo"
#define CAT2_STR "Panterita"
#define CAT3_STR "Pelon"
#define SOLDERING_IRON_STR "Cautin"

typedef enum {
  GM_CAT_1,
  GM_CAT_2,
  GM_CAT_3,
  GM_SOLDERING_IRON,
  GM_CATS_COUNT
} game_items_t;

typedef struct {
  const char *name;
  epd_bitmap_t bitmap;
  char **desc;
  uint8_t desc_len;
  char **hint;
  uint8_t hint_len;
  bool unlocked;
  game_items_t item;
} llamaneitor_item_t;

const char *cat1_desc[] = {"Gato " CAT1_STR, "Lorem Ipsum"};
const char *cat1_hint[] = {"No encontrado", "Completa la", "mision #1",
                           "para obtenerlo"};
const char *cat2_desc[] = {"Gato " CAT2_STR, "Lorem Ipsum"};
const char *cat2_hint[] = {"No encontrado", "Completa la", "mision #2",
                           "para obtenerlo"};
const char *cat3_desc[] = {"Gato " CAT3_STR, "Lorem Ipsum"};
const char *cat3_hint[] = {"No encontrado", "Completa la", "mision #3",
                           "para obtenerlo"};

const char *s_iron_desc[] = {"Cautin",       "Rapido!!!", "Necesitan este",
                             "cautin en la", "villa",     "PatagonSpace"};
const char *s_iron_hint[] = {"No encontrado", "Completa", "el reto en la",
                             "villa de",      "Hardware", "para obtenerlo"};

llamaneitor_item_t cat_items[] = {
    {.bitmap = minino_face_bitmap,
     .name = CAT1_STR,
     .desc = cat1_desc,
     .desc_len = 2,
     .hint = cat1_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_1},
    {.bitmap = minino_face_bitmap,
     .name = CAT2_STR,
     .desc = cat2_desc,
     .desc_len = 2,
     .hint = cat2_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_2},
    {.bitmap = minino_face_bitmap,
     .name = CAT3_STR,
     .desc = cat3_desc,
     .desc_len = 2,
     .hint = cat3_hint,
     .hint_len = 4,
     .unlocked = false,
     .item = GM_CAT_3},
    {.bitmap = minino_face_bitmap,
     .name = SOLDERING_IRON_STR,
     .desc = s_iron_desc,
     .desc_len = 6,
     .hint = s_iron_hint,
     .hint_len = 6,
     .unlocked = false,
     .item = GM_SOLDERING_IRON},
};