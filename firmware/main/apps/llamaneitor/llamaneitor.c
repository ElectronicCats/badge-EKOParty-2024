#include "menus_module.h"
#include "esp_log.h"
#include "oled_screen.h"
#include "llamaneitor.h"
#include "neopixels_events.h"

#define ITEMOFFSET       1
#define ITEM_PAGE_OFFSET 1

static uint16_t current_item = 0;

static const general_menu_t history_menu = {
    .menu_items = history_menu_items,
    .menu_count = HISTORY_MENU_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_display_history();

static void module_display_history() {
  uint16_t items_per_screen = 3;
  uint16_t screen_title = 0;
  uint8_t scroll_pos = (4 * 2) + 2;
  
  oled_screen_clear_buffer();
  genera_screen_display_card_information_nbc("", "");
  
  oled_screen_display_bitmap(simple_up_arrow_bmp, (128 - 10), scroll_pos, 8,
                                 8, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, (128 - 10),
                              scroll_pos + 8, 8, 8, OLED_DISPLAY_NORMAL);

  uint16_t end_index = current_item + items_per_screen;
  if (end_index > history_menu.menu_count) {
    end_index = history_menu.menu_count;
  }

  for (uint16_t i = current_item; i < end_index; i++) {
    oled_screen_display_text(
        history_menu.menu_items[i], 3,
        (i - current_item) + (ITEMOFFSET + screen_title),
        OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_show();
}

static void module_cb_event(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
    case BUTTON_UP:
    current_item = current_item > 0 ? current_item - 1 : (HISTORY_MENU_COUNT - 1);
    module_display_history();
      break;
    case BUTTON_DOWN:
    current_item = current_item < (HISTORY_MENU_COUNT - 1)
                       ? current_item + 1
                       : 0;
    if(current_item == (HISTORY_MENU_COUNT - 1)){
      oled_screen_display_bitmap(llamaneitor_1, 16, 0, 64, 32, OLED_DISPLAY_NORMAL);
    }else{
      module_display_history();
    }
      break;
    case BUTTON_RIGHT:
      current_item = 0;
      break;
    case BUTTON_LEFT:
      break;
    default:
      break;
  }
}

void llamaneitor_begin() {
  neopixel_events_run_event(neopixel_llamaneitor_init);
  oled_screen_display_bitmap(llamaneitor_1, 16, 0, 64, 32, OLED_DISPLAY_NORMAL);
  // general_register_scrolling_menu(&history_menu);
  menus_module_set_app_state(true, module_cb_event);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  module_display_history();
}
