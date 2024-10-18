#pragma once

#include "llamaneitor.h"

#define CAT1_STR "Naranjo"
#define CAT2_STR "Panterita"
#define CAT3_STR "Pelon"

typedef enum { GM_CAT_1, GM_CAT_2, GM_CAT_3, GM_CATS_COUNT } game_cats_t;

typedef struct {
  const char *name;
  epd_bitmap_t bitmap;
  char **desc;
  uint8_t desc_len;
  char **hint;
  uint8_t hint_len;
  bool unlocked;
} llamaneitor_item_t;

const char *cat1_desc[] = {"Gato", "1"};
const char *cat1_hint[] = {"No encontrado", "Completa la", "mision #1"};
const char *cat2_desc[] = {"Gato", "2"};
const char *cat2_hint[] = {"No encontrado", "Completa la", "mision #2"};
const char *cat3_desc[] = {"Gato", "3"};
const char *cat3_hint[] = {"No encontrado", "Completa la", "mision #3"};

llamaneitor_item_t cat_items[] = {
    {.bitmap = minino_face_bitmap,
     .name = CAT1_STR,
     .desc = cat1_desc,
     .desc_len = 2,
     .hint = cat1_hint,
     .hint_len = 3,
     .unlocked = false},
    {.bitmap = minino_face_bitmap,
     .name = CAT2_STR,
     .desc = cat2_desc,
     .desc_len = 2,
     .hint = cat2_hint,
     .hint_len = 3,
     .unlocked = false},
    {.bitmap = minino_face_bitmap,
     .name = CAT3_STR,
     .desc = cat3_desc,
     .desc_len = 2,
     .hint = cat3_hint,
     .hint_len = 3,
     .unlocked = false},
};