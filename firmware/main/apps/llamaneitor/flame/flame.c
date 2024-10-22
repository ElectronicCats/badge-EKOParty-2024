#include "flame.h"

#include "preferences.h"

uint32_t flame;

static void load_flame_time() {
  flame = preferences_get_uint(FLAME_TIME_MEM, FLAME_TIME);
}

static void save_flame_time() { preferences_put_uint(FLAME_TIME_MEM, flame); }

static void show_scanning_dots() {}

static void flame_task() {}