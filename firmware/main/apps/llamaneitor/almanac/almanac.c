#include "almanac.h"

#include "preferences.h"

void almanac_load_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    almanac[i].found = preferences_get_bool(str, false);
  }
}

void almanac_save_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    preferences_put_bool(str, almanac[i].found);
  }
}

void almanac_unlock_item(villages_e village) {
  if (almanac[village].found) {
    return;
  }
  almanac[village].found = true;
  almanac_save_items();
}
