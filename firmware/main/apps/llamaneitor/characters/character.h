#pragma once

#include <stdio.h>

#include "bitmaps_general.h"
#include "llamaneitor.h"

#define CHAR1_NAME_STR "Character 1"
#define CHAR2_NAME_STR "Character 2"
#define CHAR3_NAME_STR "Character 3"
#define CHAR4_NAME_STR "Character 4"

typedef struct {
  const char *name;
  epd_bitmap_props_t bitmap;
  char **desc;
  uint8_t desc_len;
} character_t;

const char *char1_desc[] = {CHAR1_NAME_STR, "Lorem Ipsum"};
const char *char2_desc[] = {CHAR2_NAME_STR, "Lorem Ipsum"};
const char *char3_desc[] = {CHAR3_NAME_STR, "Lorem Ipsum"};
const char *char4_desc[] = {CHAR4_NAME_STR, "Lorem Ipsum"};

character_t character_profiles[CHARS_NUM] = {
    {.bitmap = epd_bitmap_char1_props,
     .name = CHAR1_NAME_STR,
     .desc = char1_desc,
     .desc_len = 2},
    {.bitmap = epd_bitmap_char2_props,
     .name = CHAR2_NAME_STR,
     .desc = char2_desc,
     .desc_len = 2},
    {.bitmap = epd_bitmap_char3_props,
     .name = CHAR3_NAME_STR,
     .desc = char3_desc,
     .desc_len = 2},
    {.bitmap = epd_bitmap_char4_props,
     .name = CHAR4_NAME_STR,
     .desc = char4_desc,
     .desc_len = 2},
};

void character_open_profile();
void character_set_current_character(uint8_t character);