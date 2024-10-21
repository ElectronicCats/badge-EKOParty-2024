#include "mision.h"
#include "bitmaps_general.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "general/general_screens.h"
#include "general_submenu.h"
#include "inventory.h"
#include "items.h"
#include "llamaneitor.h"
#include "menus_module.h"
#include "oled_screen.h"
#include "preferences.h"

static uint8_t code_gato_1[4] = {0, 1, 2, 3};
static uint8_t code_gato_2[4] = {4, 5, 6, 7};
static uint8_t code_gato_3[4] = {8, 9, 0, 1};

static uint8_t current_mision = 0;
static uint8_t current_x_pos = 0;
static uint8_t current_y_pos = 0;
static uint8_t code_selected[4] = {0, 0, 0, 0};

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
static const general_menu_t mision_2_menu = {
    .menu_items = mision_2,
    .menu_count = MISION2_COUNT,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static void *exit_cb;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event);
static void module_exit_missions_app();
static void module_display_code_selector();
static void module_validate_code();

static void module_validate_code() {
  if (current_x_pos != 4) {
    return;
  }
  if (code_selected[0] == code_gato_1[0] &&
      code_selected[1] == code_gato_1[1] &&
      code_selected[2] == code_gato_1[2] &&
      code_selected[3] == code_gato_1[3]) {
    oled_screen_clear();
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Gato", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text(CAT1_STR, 40, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Desbloqueado", 40, 3, OLED_DISPLAY_NORMAL);
    inventory_unlock_item(GM_CAT_1);
    vTaskDelay(pdMS_TO_TICKS(3000));
    if (exit_cb != NULL) {
      ((void (*)(void))exit_cb)();
    }
  } else if (code_selected[0] == code_gato_2[0] &&
             code_selected[1] == code_gato_2[1] &&
             code_selected[2] == code_gato_2[2] &&
             code_selected[3] == code_gato_2[3]) {
    oled_screen_clear();
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Gato", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text(CAT2_STR, 40, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Desbloqueado", 40, 3, OLED_DISPLAY_NORMAL);
    inventory_unlock_item(GM_CAT_2);
    vTaskDelay(pdMS_TO_TICKS(3000));
    if (exit_cb != NULL) {
      ((void (*)(void))exit_cb)();
    }
  } else if (code_selected[0] == code_gato_3[0] &&
             code_selected[1] == code_gato_3[1] &&
             code_selected[2] == code_gato_3[2] &&
             code_selected[3] == code_gato_3[3]) {
    oled_screen_clear();
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Gato", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text(CAT3_STR, 40, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Desbloqueado", 40, 3, OLED_DISPLAY_NORMAL);
    inventory_unlock_item(GM_CAT_3);
    vTaskDelay(pdMS_TO_TICKS(3000));
    if (exit_cb != NULL) {
      ((void (*)(void))exit_cb)();
    }
  } else {
    oled_screen_clear();
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Codigo", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("incorrecto", 40, 2, OLED_DISPLAY_NORMAL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    current_x_pos = 0;
    current_y_pos = code_selected[current_x_pos];
    module_display_code_selector();
  }
}

static void module_exit_missions_app() {
  current_mision = 0;
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Volvere..", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
  menus_module_set_app_state(true, module_cb_event);
  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}

static void mision_selection_handler(uint8_t selection) {
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);

  switch (selection) {
  case MISION_1:
    oled_screen_display_text("No es un", 40, 0, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("hombre...", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("es una", 40, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("maquina", 40, 3, OLED_DISPLAY_NORMAL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    general_register_scrolling_menu(&mision_1_menu);
    general_screen_display_scrolling_text_handler(module_exit_missions_app);
    break;
  case MISION_2:
    oled_screen_display_text("El destino", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("no ha sido", 40, 2, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("escrito", 40, 3, OLED_DISPLAY_NORMAL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    general_register_scrolling_menu(&mision_2_menu);
    general_screen_display_scrolling_text_handler(module_exit_missions_app);
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
    if (exit_cb != NULL) {
      ((void (*)(void))exit_cb)();
    }
    break;
  default:
    break;
  }
}

static void module_display_code_selector() {
  oled_screen_clear();
  char code[4];
  oled_screen_display_text_center("Ingresa codigo", 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_up_arrow_bmp, 0, 8 * 2, 8, 8,
                             OLED_DISPLAY_NORMAL);
  oled_screen_display_bitmap(simple_down_arrow_bmp, 0, 8 * 3, 8, 8,
                             OLED_DISPLAY_NORMAL);
  uint8_t x_post_offset = 8;
  for (uint8_t i = 0; i < 4; i++) {
    snprintf(code, 4, "%d", code_selected[i]);
    oled_screen_display_text(code, (x_post_offset + 16 * i) + 16, 2,
                             (i == current_x_pos) ? OLED_DISPLAY_INVERT
                                                  : OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_text("OK", 100, 2,
                           (current_x_pos == 4) ? OLED_DISPLAY_INVERT
                                                : OLED_DISPLAY_NORMAL);
}

static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }

  switch (button_name) {
  case BUTTON_UP:
    current_y_pos++;
    if (current_y_pos > 9) {
      current_y_pos = 0;
    }
    code_selected[current_x_pos] = current_y_pos;
    module_display_code_selector();
    break;
  case BUTTON_DOWN:
    current_y_pos--;
    if (current_y_pos == 255) {
      current_y_pos = 9;
    }
    code_selected[current_x_pos] = current_y_pos;
    module_display_code_selector();
    break;
  case BUTTON_RIGHT:
    if (current_x_pos == 4) {
      module_validate_code();
      current_x_pos = 0;
      current_y_pos = code_selected[current_x_pos];
    } else {
      current_x_pos++;
      current_y_pos = code_selected[current_x_pos];
      module_display_code_selector();
    }

    break;
  case BUTTON_LEFT:
    current_x_pos--;
    current_y_pos = code_selected[current_x_pos];
    module_display_code_selector();
    break;
  default:
    break;
  }
}

// static void mision_exit_handler() { menus_module_exit_app(); }

void mision_register_cb_exit(void *cb) { exit_cb = cb; }

void mision_begin() {
  menus_module_set_app_state(true, module_cb_event);
  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}

void mision_enter_code() {
  menus_module_set_app_state(true, module_cb_code_register_event);
  module_display_code_selector();
}