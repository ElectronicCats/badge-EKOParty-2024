#pragma once

#include <stdio.h>

typedef enum {
  LLAMANEITOR_MAIN_SCENE,
  LLAMANEITOR_CHARACTER_SCENE,
  LLAMANEITOR_MISSIONS_SCENE,
  LLAMANEITOR_INVENTORY_SCENE,
  LLAMANEITOR_FLAME_SCENE
} llamaneitor_scenes_t;

llamaneitor_scenes_t llamaneitor_scenes_get_scene();
void llamaneitor_scenes_main_menu();
void llamaneitor_scenes_inventory();
