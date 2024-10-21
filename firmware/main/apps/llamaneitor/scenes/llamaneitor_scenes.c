#include "llamaneitor_scenes.h"
#include "bitmaps_general.h"
#include "character.h"
#include "general_submenu.h"
#include "inventory.h"
#include "items.h"
#include "llamaneitor.h"
#include "menus_module.h"
#include "mision.h"
#include "oled_screen.h"

static llamaneitor_scenes_t current_scene = 0;
static uint8_t item = 0;

static void open_item();
static void show_item_desc();

void llamaneitor_scenes_main_menu();
void llamaneitor_scenes_inventory();

llamaneitor_scenes_t llamaneitor_scenes_get_scene() { return current_scene; }

//////////////////////////////////// Main Menu ////////////////////////////////
typedef enum {
  CHARACTER_OPTION,
  MISSIONS_OPTION,
  INVENTORY_OPTION,
  MATRIX_OPTION
} llamaneitor_main_menu_options;
const char *llamaneitor_main_menu_items[] = {"Personaje", "Misiones",
                                             "Inventario", "Matrix"};

static void main_menu_selection_handler(uint8_t selection) {
  switch (selection) {
  case CHARACTER_OPTION:
    character_open_profile();
    break;
  case MISSIONS_OPTION:
    mision_register_cb_exit(llamaneitor_scenes_main_menu);
    mision_begin();
    break;
  case INVENTORY_OPTION:
    llamaneitor_scenes_inventory();
    break;
  case MATRIX_OPTION:
    mision_register_cb_exit(llamaneitor_scenes_main_menu);
    mision_enter_code();
    break;
  default:
    break;
  }
}

static void main_menu_exit_handler() { menus_module_exit_app(); }

void llamaneitor_scenes_main_menu() {
  current_scene = LLAMANEITOR_MAIN_SCENE;
  general_submenu_menu_t main_menu;
  main_menu.options = llamaneitor_main_menu_items;
  main_menu.options_count =
      sizeof(llamaneitor_main_menu_items) / sizeof(char *);
  main_menu.select_cb = main_menu_selection_handler;
  main_menu.exit_cb = main_menu_exit_handler;
  general_submenu(main_menu);
}

//////////////////////////////////// Inventory Menu
///////////////////////////////////

static char **items_names = NULL;

static char **get_items_names() {
  uint8_t items_count = sizeof(cat_items) / sizeof(llamaneitor_item_t);
  char **names = malloc(sizeof(char *) * items_count);
  for (uint8_t i = 0; i < items_count; i++) {
    names[i] = cat_items[i].name;
  }
  return names;
}

static void inventory_selection_handler(uint8_t selection) {
  item = selection;
  open_item();
}

void llamaneitor_scenes_inventory() {
  inventory_load_items();
  current_scene = LLAMANEITOR_INVENTORY_SCENE;
  uint8_t items_count = sizeof(cat_items) / sizeof(llamaneitor_item_t);
  items_names = get_items_names();

  general_submenu_menu_t inventory_menu;
  inventory_menu.options = items_names;
  inventory_menu.options_count = items_count;
  inventory_menu.select_cb = inventory_selection_handler;
  inventory_menu.exit_cb = llamaneitor_scenes_main_menu;
  general_submenu(inventory_menu);
}

//////////////////////////////////// Item Description Menu
///////////////////////////////////
static void item_input_cb(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    break;
  case BUTTON_DOWN:
    break;
  case BUTTON_RIGHT:
    show_item_desc();
    break;
  case BUTTON_LEFT:
    llamaneitor_scenes_inventory();
    break;
  default:
    break;
  }
}

static void show_item_desc() {
  static general_menu_t item_menu;
  item_menu.menu_items =
      cat_items[item].unlocked ? cat_items[item].desc : cat_items[item].hint;
  item_menu.menu_count = cat_items[item].unlocked ? cat_items[item].desc_len
                                                  : cat_items[item].hint_len;
  item_menu.menu_level = GENERAL_TREE_APP_INFORMATION;
  general_register_scrolling_menu(&item_menu);
  general_screen_display_scrolling_text_handler(llamaneitor_scenes_inventory);
}

static void open_item() {
  if (!cat_items[item].unlocked) {
    show_item_desc();
    return;
  }
  menus_module_set_app_state(true, item_input_cb);
  uint8_t x = strlen(cat_items[item].name) * 8 / 2 + 64;
  oled_screen_clear();
  oled_screen_display_text_center(cat_items[item].name, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_right_arrow_bmp, x, 0, 8, 8,
                             OLED_DISPLAY_NORMAL);
  x = 64 - cat_items[item].bitmap.width / 2;
  uint8_t y = 20 - cat_items[item].bitmap.height / 2;
  oled_screen_display_bitmap(
      cat_items[item].bitmap.bitmap, x, y, cat_items[item].bitmap.width,
      cat_items[item].bitmap.height, OLED_DISPLAY_NORMAL);
}