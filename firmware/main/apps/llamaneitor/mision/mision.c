#include "bitmaps_general.h"
#include "general_submenu.h"
#include "menus_module.h"
#include "general/general_screens.h"
#include "mision.h"
#include "oled_screen.h"

static uint8_t current_mision = 0;
static const general_menu_t mision_menu = {
  .menu_items = list_mision,
  .menu_count = MISION_COUNT,
  .menu_level = GENERAL_TREE_APP_INFORMATION,
};
static const general_menu_t mision_1_menu = {
  .menu_items = mision_1,
  .menu_count = MISION1_COUNT,
  .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static void* exit_cb;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_exit_app();

static void module_exit_app(){
  current_mision = 0;
  menus_module_set_app_state(true, module_cb_event);
  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}

static void mision_selection_handler(uint8_t selection) {
  switch (selection) {
  case MISION_1:
    general_register_scrolling_menu(&mision_1_menu);
    general_screen_display_scrolling_text_handler(module_exit_app);
    break;
  case MISION_2:
    break;
  case MISION_3:
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
    current_mision =
        current_mision > 0 ? current_mision - 1 : (mision_menu.menu_count - 1);
    general_screen_display_menu(current_mision);
    break;
  case BUTTON_DOWN:
    current_mision =
        current_mision < (mision_menu.menu_count - 1) ? current_mision + 1 : 0;
    general_screen_display_menu(current_mision);
    break;
  case BUTTON_RIGHT:
    mision_selection_handler(current_mision);
    current_mision = 0;
    break;
  case BUTTON_LEFT:
    if(exit_cb != NULL){
      ((void (*)(void))exit_cb)();
    }
    break;
  default:
    break;
  }
}

// static void mision_exit_handler() { menus_module_exit_app(); }


void mision_register_cb_exit(void* cb) { exit_cb = cb; }

void mision_begin(){
  menus_module_set_app_state(true, module_cb_event);
  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}