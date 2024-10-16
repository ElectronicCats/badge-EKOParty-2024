#include "llamaneitor.h"
#include "esp_log.h"
#include "menus_module.h"
#include "modals_module.h"
#include "neopixels_events.h"
#include "oled_screen.h"

#define ITEMOFFSET 1
#define ITEM_PAGE_OFFSET 1

static uint16_t current_item = 0;
static bool is_user_selection = false;

static const general_menu_t history_menu = {
    .menu_items = history_menu_items,
    .menu_count = HISTORY_MENU_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

static const general_menu_t history_cont_menu = {
    .menu_items = history_continue,
    .menu_count = HISTORY_CONT_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

static const general_menu_t main_menu_game = {
    .menu_items = main_menu_items,
    .menu_count = MENU_GM_COUNT,
    .menu_level = GENERAL_TREE_APP_MENU,
};

static game_ctx_t player_ctx = {0};

static general_menu_t current_history = history_menu;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_cb_event_user_selection(uint8_t button_name,
                                           uint8_t button_event);
static void module_cb_event_user_selection(uint8_t button_name,
                                           uint8_t button_event);
static void module_cb_event_main_menu(uint8_t button_name,
                                      uint8_t button_event);
static void module_display_history();

static void module_display_history() {
  uint16_t items_per_screen = 3;
  uint16_t screen_title = 0;
  uint8_t scroll_pos = (4 * 2) + 2;

  oled_screen_clear_buffer();
  genera_screen_display_card_information_nbc("", "");

  oled_screen_display_bitmap(simple_up_arrow_bmp, (128 - 10), scroll_pos, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, (128 - 10), scroll_pos + 8,
                             8, 8, OLED_DISPLAY_NORMAL);

  uint16_t end_index = current_item + items_per_screen;
  if (end_index > current_history.menu_count) {
    end_index = current_history.menu_count;
  }

  for (uint16_t i = current_item; i < end_index; i++) {
    oled_screen_display_text(current_history.menu_items[i], 3,
                             (i - current_item) + (ITEMOFFSET + screen_title),
                             OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_show();
}

static void module_user_option() {
  oled_screen_clear_buffer();
  oled_screen_display_text("Quieres ayudar?", 0, 0, OLED_DISPLAY_NORMAL);
  if (current_item == 0) {
    oled_screen_display_text("> Si", 0, 2, OLED_DISPLAY_INVERT);
    oled_screen_display_text("No", 0, 3, OLED_DISPLAY_NORMAL);
  } else if (current_item == 1) {
    oled_screen_display_text("Si", 0, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("> No", 0, 3, OLED_DISPLAY_INVERT);
  }
}

static void module_display_character_selector() {
  oled_screen_clear_buffer();
  oled_screen_clear();
  oled_screen_display_text("Elige personaje", 0, 0, OLED_DISPLAY_NORMAL);
  uint8_t scroll_pos = (4 * 2) + 2;
  oled_screen_display_bitmap(simple_up_arrow_bmp, 118, 8, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, 118, 16, 8, 8,
                             OLED_DISPLAY_NORMAL);
  epd_bitmap_props_t character_bitmap = characters[current_item];
  oled_screen_display_bitmap(character_bitmap.bitmap, 32, 8,
                             character_bitmap.width, character_bitmap.height,
                             OLED_DISPLAY_NORMAL);
}

static void module_display_player_inventary() {}

static void module_cb_event_main_menu(uint8_t button_name,
                                      uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    current_item = current_item > 0 ? current_item - 1 : (MENU_COUNT - 1);
    general_screen_display_menu(current_item);
    break;
  case BUTTON_DOWN:
    current_item = current_item < (MENU_COUNT - 1) ? current_item + 1 : 0;
    general_screen_display_menu(current_item);
    break;
  case BUTTON_RIGHT:
    break;
  case BUTTON_LEFT:
    break;
  default:
    break;
  }
}

static void module_cb_event_character_selection(uint8_t button_name,
                                                uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    current_item = current_item > 0 ? current_item - 1 : (5 - 1);
    module_display_character_selector();
    break;
  case BUTTON_DOWN:
    current_item = current_item < (5 - 1) ? current_item + 1 : 0;
    module_display_character_selector();
    break;
  case BUTTON_RIGHT:
    player_ctx.character_bitmap = characters[current_item];
    current_item = 0;
    menus_module_set_app_state(true, module_cb_event_main_menu);
    general_register_menu(&main_menu_game);
    general_screen_display_menu(current_item);
    break;
  case BUTTON_LEFT:
    break;
  default:
    break;
  }
}

static void module_cb_event_user_selection(uint8_t button_name,
                                           uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    current_item = current_item > 0 ? current_item - 1 : (2 - 1);
    module_user_option();
    break;
  case BUTTON_DOWN:
    current_item = current_item < (2 - 1) ? current_item + 1 : 0;
    module_user_option();
    break;
  case BUTTON_RIGHT:
    if (current_item == 1) {
      oled_screen_clear_buffer();
      oled_screen_display_text("Igual nos vas", 0, 1, OLED_DISPLAY_NORMAL);
      oled_screen_display_text("Ayudar :)", 0, 1, OLED_DISPLAY_NORMAL);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    current_history = history_cont_menu;
    oled_screen_clear_buffer();
    menus_module_set_app_state(true, module_cb_event);
    neopixel_events_run_event(neopixel_scanning_event);
    current_item = 0;
    is_user_selection = true;
    module_display_history();
    break;
  case BUTTON_LEFT:
    break;
  default:
    break;
  }
}

static void module_cb_event(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    current_item =
        current_item > 0 ? current_item - 1 : (current_history.menu_count - 1);
    module_display_history();
    break;
  case BUTTON_DOWN:
    current_item =
        current_item < (current_history.menu_count - 1) ? current_item + 1 : 0;
    if (current_item == (current_history.menu_count - 1)) {
      current_item = 0;
      if (is_user_selection) {
        menus_module_set_app_state(true, module_cb_event_character_selection);
        module_display_character_selector();
      } else {
        menus_module_set_app_state(true, module_cb_event_user_selection);
        module_user_option();
      }
    } else {
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