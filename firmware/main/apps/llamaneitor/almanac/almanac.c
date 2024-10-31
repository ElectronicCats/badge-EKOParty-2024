#include "almanac.h"

#include "inventory.h"
#include "items.h"
#include "preferences.h"

void almanac_load_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    almanac[i].found = preferences_get_bool(str, 0 ? false : true);
  }
}

void almanac_save_items() {
  char str[12];
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    sprintf(str, "almanac%d", i);
    preferences_put_bool(str, almanac[i].found);
  }
}

bool almanac_is_first_completed() {
  if (inventory_is_unlocked_item(GM_CAT_3)) {
    return false;
  }
  uint8_t cnt = 0;
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    cnt += almanac[i].found;
  }
  if (cnt >= VILLAGES_COUNT) {
    // TODO: Play NGGYU Song
    inventory_unlock_item(GM_CAT_3);
    return true;
  }
  return false;
}

void almanac_unlock_item(villages_e village) {
  if (almanac[village].found) {
    return;
  }
  almanac[village].found = true;
  almanac_save_items();
}
