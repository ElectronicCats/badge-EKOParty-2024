#pragma once

#include "llamaneitor_scenes.h"
#include <stdio.h>

#define FLAME_TIME 86400
#define FLAME_TIME_MEM "flame_time"

// 'flame_1', 24x24px
const unsigned char flame_bmp_1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x18, 0x00,
    0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x1e, 0x00,
    0x00, 0xbe, 0x00, 0x01, 0xfe, 0x00, 0x01, 0xfe, 0x80, 0x03, 0xfe, 0xc0,
    0x07, 0xff, 0xc0, 0x07, 0xff, 0xc0, 0x07, 0xff, 0xc0, 0x0f, 0xff, 0xc0,
    0x0f, 0xff, 0xc0, 0x0f, 0xff, 0xc0, 0x07, 0xff, 0xc0, 0x07, 0xef, 0xc0,
    0x07, 0x87, 0x80, 0x03, 0xc7, 0x80, 0x01, 0xc7, 0x00, 0x00, 0x00, 0x00};
// 'flame_2', 24x24px
const unsigned char flame_bmp_2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x1c, 0x00,
    0x00, 0x3c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0xfe, 0x00,
    0x00, 0xff, 0x00, 0x06, 0xff, 0x80, 0x06, 0xff, 0xc0, 0x0c, 0xff, 0xc0,
    0x0f, 0xff, 0xe8, 0x0f, 0xff, 0xe8, 0x0f, 0xff, 0xfc, 0x1f, 0xff, 0xfc,
    0x1f, 0xf7, 0xfc, 0x1f, 0xf1, 0xf8, 0x1f, 0xd0, 0xf8, 0x0f, 0xc0, 0xf0,
    0x0f, 0x80, 0xe0, 0x07, 0x80, 0xc0, 0x03, 0x81, 0x80, 0x00, 0x80, 0x00};
// 'flame_3', 24x24px
const unsigned char flame_bmp_3[] = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3e, 0x00,
    0x00, 0x3e, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x7f, 0x80,
    0x00, 0xff, 0x80, 0x00, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x03, 0xff, 0xc8,
    0x03, 0xff, 0xc8, 0x03, 0xff, 0xcc, 0x07, 0xff, 0xfc, 0x07, 0xf9, 0xfc,
    0x0f, 0xe3, 0xfc, 0x0f, 0xc1, 0xfc, 0x07, 0xc0, 0xfc, 0x07, 0x80, 0xfc,
    0x03, 0x80, 0x78, 0x03, 0x80, 0x78, 0x01, 0xc0, 0xf0, 0x00, 0xc0, 0xc0};
// 'flame_4', 24x24px
const unsigned char flame_bmp_4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x1e, 0x00,
    0x00, 0x3f, 0x00, 0x00, 0x3f, 0x10, 0x02, 0x3f, 0x30, 0x02, 0x3f, 0xf0,
    0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xf0,
    0x07, 0xff, 0xf0, 0x03, 0xf7, 0xf0, 0x03, 0xe3, 0xf0, 0x01, 0xe3, 0xf0,
    0x01, 0xe3, 0xf0, 0x00, 0xc1, 0xe0, 0x00, 0x61, 0xc0, 0x00, 0x00, 0x00};

const unsigned char *flame_bmp_arr[] = {flame_bmp_1, flame_bmp_2, flame_bmp_3,
                                        flame_bmp_4};

// 'cup', 24x24px
const unsigned char cup_bmp[] = {
    0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0xc0, 0x80, 0x00, 0x80, 0x80,
    0x01, 0x80, 0xc0, 0x01, 0x80, 0x40, 0x01, 0x00, 0x60, 0x01, 0x07, 0xe0,
    0x01, 0xff, 0xe0, 0x01, 0xff, 0xc0, 0x01, 0xff, 0xc0, 0x00, 0xff, 0x80,
    0x00, 0x7f, 0x80, 0x00, 0x3e, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00,
    0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00,
    0x00, 0x1c, 0x00, 0x00, 0x7f, 0x00, 0x00, 0xff, 0x80, 0x00, 0xff, 0x80};

void flame_refresh(uint8_t frame);
void flame_task_begin();
void flame_set_flame_time(uint32_t timestamp);
void flame_feed_flame(uint16_t seconds);
void flame_waken_flame(uint16_t seconds);