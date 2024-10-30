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
#include "villages.h"
#include "sounds.h"
#include "lora_manager.h"

#define CODE_LEN 4
#define ITEMOFFSET 1
#define ITEM_PAGE_OFFSET 1

static uint8_t code_gato_1[CODE_LEN]   = {1, 3, 3, 7};
static uint8_t code_gato_2[CODE_LEN]   = {4, 5, 6, 7};
static uint8_t code_gato_3[CODE_LEN]   = {8, 9, 0, 1};
static uint8_t code_cautin[CODE_LEN]   = {1, 0, 0, 0};
static uint8_t code_selected[CODE_LEN] = {0, 0, 0, 0};

static uint8_t current_mision = 0;
static uint8_t current_mision_idx = 0;
static uint8_t current_x_pos = 0;
static uint8_t current_y_pos = 0;

static bool block_notification = false;
static uint8_t mission_idx = 0;
static uint8_t current_item = 0;

// Hardware village
static const general_menu_t mission_1_hardware_menu = {
    .menu_items = mission_1_hardware,
    .menu_count = MISION1_COUNT,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};
// PatagonSpace - Hardware village
static const general_menu_t mission_1_patagon_menu = {
    .menu_items = mission_1_patagon,
    .menu_count = MISION1_PATAGON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mision_2_menu = {
    .menu_items = mision_2,
    .menu_count = MISION2_COUNT,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};
static const general_menu_t mission_1_preamble = {
    .menu_items = mission_1_text,
    .menu_count = MISION1_PREAMBLE,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};


static general_menu_t current_history = mission_1_preamble;
static bool is_user_finished = false;
static void *exit_cb;

static void module_cb_event(uint8_t button_name, uint8_t button_event);
static void module_cb_code_register_event(uint8_t button_name,
                                          uint8_t button_event);
static void module_exit_missions_app();
static void module_display_code_selector();
static void module_validate_code();
static void show_mission_screen_loading();
static void module_display_preamble_mission();

static void module_update_mision(){
  char menu_item[16];
  char mission_item[16];
  char* tmp_list_mision[MISION_COUNT];

  for(int i=0; i<MISION_COUNT; i++){
    sprintf(menu_item, "mission_%d", i+1);
    uint8_t show_mission = preferences_get_int(menu_item, 0);
    if(show_mission == 1){
      sprintf(mission_item, "Mision %d", i+1);
      list_mision[i] = mission_item;
    }
  }
  general_menu_t mision_menu = {
    .menu_items = list_mision,
    .menu_count = MISION_COUNT,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
  };

  general_register_menu(&mision_menu);
  general_screen_display_menu(current_mision);
}

static void module_display_preamble_mission(){
    uint16_t items_per_screen = 3;
    uint16_t screen_title = 0;
    uint8_t scroll_pos = (4 * 2) + 2;

    general_clear_screen();
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

static void module_cb_event_mission_preamble(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_UP:
    current_item =
        current_item > 0 ? current_item - 1 : (current_history.menu_count - 1);
        module_display_preamble_mission();
    break;
  case BUTTON_DOWN:
    current_item =
        current_item < (current_history.menu_count - 1) ? current_item + 1 : 0;
        if(current_item == current_history.menu_count - 1){
          if(is_user_finished == false){
            show_mission_screen_loading();
          }else{
            is_user_finished = false;
            char mission_str[16];
            sprintf(mission_str, "mission_%d", mission_idx);
            preferences_put_int(mission_str, 1);
            menus_module_set_app_state(true, module_cb_event);
            module_update_mision();
          }
        }else{
          module_display_preamble_mission();
        }
    break;
  case BUTTON_RIGHT:
    break;
  case BUTTON_LEFT:
    break;
  default:
    break;
  }
}

static void show_downloading_bar_mission(){
  oled_screen_clear();
  oled_screen_display_text_center("Descargando", 0, OLED_DISPLAY_NORMAL);
  char mission_str[16];
  sprintf(mission_str, "Mision %d", mission_idx);
  oled_screen_display_text_center(mission_str, 1, OLED_DISPLAY_NORMAL);
  for(int i = 0; i < 128; i++){
    oled_screen_display_loading_bar(i, 3);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
  vTaskDelay(pdMS_TO_TICKS(2000));
}

static void show_mission_screen_loading(){
  oled_screen_fadeout();
  show_downloading_bar_mission();
  char mission_str[16];
  sprintf(mission_str, "mission_%d", current_mision_idx);
  preferences_put_int(mission_str, 1);
  vTaskDelay(pdMS_TO_TICKS(1000));
  // lora_manager_alert_scrolling("Mision_1_desbloqueada");
  oled_screen_display_text_center("Mision", 2, OLED_DISPLAY_NORMAL);
  oled_screen_display_text_center("Descargada", 3, OLED_DISPLAY_NORMAL);
  oled_screen_fadeout();
  is_user_finished = true;
  if(mission_idx == PAT_SPACE){
    current_history = mission_1_patagon_menu;
  }else if(mission_idx == HW_HACK){
    current_history = mission_1_hardware_menu;
  }
  current_item = 0;
  module_display_preamble_mission();
}

void show_mission_screen(uint8_t village_idx){

  mission_idx = village_idx;
  
  // Unlock mission 1
  if(village_idx == PAT_SPACE || village_idx == HW_HACK){
    if(preferences_get_int("mission_1", 0) == 0){
      current_mision_idx = 1;
      oled_screen_fadeout();
      oled_screen_clear();
      menus_module_set_app_state(true, module_cb_event_mission_preamble);
      module_display_preamble_mission();
      
    }
  }else if(village_idx == YWE_HACK || village_idx == EC){
    if(preferences_get_int("mission_2", 0) == 0){
      vTaskDelay(pdMS_TO_TICKS(3000));
      show_downloading_bar_mission();
      preferences_put_int("mission_2", 1);
      vTaskDelay(pdMS_TO_TICKS(1000));
      lora_manager_alert_scrolling("Mision_2_desbloqueada");
      if(llamaneitor_scenes_get_scene()){
        llamaneitor_scenes_main_menu();
      }
    }
  }else if(village_idx == THE_BOSS_1 || village_idx == THE_BOSS_2){
    sounds_play_soundtrack(play_godfather);
  }
  block_notification = false;
}

static void llamaneitor_show_need_mission(){
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Te faltan", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("misiones", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_cat(uint8_t item_index){
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Gato", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Desbloqueado", 40, 3, OLED_DISPLAY_NORMAL);
  oled_screen_display_text(cat_items[item_index].name, 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_unlock_cautin(){
  oled_screen_fadeout();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(2000));
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Cautin", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Desbloqueado", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_error_trick(){
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("El truco", 40, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("solo funciona", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("una vez", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void llamaneitor_mission_first(){
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("La mision", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("es primero", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
}

static void module_validate_code() {
  if (current_x_pos != 4) {
    return;
  }
  oled_screen_clear();

  if(memcmp(code_selected, code_gato_1, CODE_LEN) == 0){
    uint8_t is_unlocked_mission = preferences_get_int("mission_1", 0);
    if(is_unlocked_mission){
      if(!inventory_is_unlocked_item(GM_CAT_1)){
        if(inventory_is_unlocked_item(GM_SOLDERING_IRON)){
          inventory_unlock_item(GM_CAT_1);
          llamaneitor_unlock_cat(GM_CAT_1);
          
        }else{
          llamaneitor_show_need_mission();
        }
      }else{
        llamaneitor_error_trick();
      }
    }else{
      llamaneitor_mission_first();
    }
  }else if(memcmp(code_selected, code_gato_2, CODE_LEN) == 0){
   uint8_t is_unlocked_mission = preferences_get_int("mission_2", 0);
    if(is_unlocked_mission){
      if(!inventory_is_unlocked_item(GM_CAT_2)){
        inventory_unlock_item(GM_CAT_2);
        llamaneitor_unlock_cat(GM_CAT_2);
      }else{
        llamaneitor_error_trick();
      }
    }else{
      llamaneitor_mission_first();
    }
  }else if(memcmp(code_selected, code_gato_3, CODE_LEN) == 0){
    uint8_t is_unlocked_mission = preferences_get_int("mission_3", 0);
    if(is_unlocked_mission){
      if(!inventory_is_unlocked_item(GM_CAT_3)){
        inventory_unlock_item(GM_CAT_3);
        llamaneitor_unlock_cat(GM_CAT_3);
      }else{
        llamaneitor_error_trick();
      }
    }else{
      llamaneitor_mission_first();
    }
  }else if(memcmp(code_selected, code_cautin, CODE_LEN) == 0){
    uint8_t is_unlocked_mission = preferences_get_int("mission_1", 0);
    if(is_unlocked_mission){
      if(!inventory_is_unlocked_item(GM_SOLDERING_IRON)){
        inventory_unlock_item(GM_SOLDERING_IRON);
        llamaneitor_unlock_cautin();
      }else{
        llamaneitor_error_trick();
      }
    }else{
      llamaneitor_mission_first();
    }
  }else{
    oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32,
                               OLED_DISPLAY_NORMAL);
    oled_screen_display_text("Codigo", 40, 1, OLED_DISPLAY_NORMAL);
    oled_screen_display_text("incorrecto", 40, 2, OLED_DISPLAY_NORMAL);
    vTaskDelay(pdMS_TO_TICKS(3000));
    current_x_pos = 0;
    current_y_pos = code_selected[current_x_pos];
    module_display_code_selector();
    return;
  }
  if (exit_cb != NULL) {
    ((void (*)(void))exit_cb)();
  }
}

static void module_exit_missions_app() {
  current_mision = 0;
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Volvere..", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
  menus_module_set_app_state(true, module_cb_event);
  module_update_mision();
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
    general_register_scrolling_menu(&mission_1_hardware_menu);
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
        current_mision > 0 ? current_mision - 1 : (MISION_COUNT - 1);
    module_update_mision();
    break;
  case BUTTON_DOWN:
    current_mision =
        current_mision < (MISION_COUNT - 1) ? current_mision + 1 : 0;
    module_update_mision();
    break;
  case BUTTON_RIGHT:
    mision_selection_handler(current_mision);
    current_mision = 0;
    break;
  case BUTTON_LEFT:
    llamaneitor_scenes_main_menu();
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
    if(current_x_pos == 255){
      current_x_pos = 0;
      if (exit_cb != NULL) {
        ((void (*)(void))exit_cb)();
      }
    }else{
      current_y_pos = code_selected[current_x_pos];
      module_display_code_selector();
    }
    break;
  default:
    break;
  }
}

// static void mision_exit_handler() { menus_module_exit_app(); }

void mision_register_cb_exit(void *cb) { exit_cb = cb; }

void mision_begin() {
  menus_module_set_app_state(true, module_cb_event);
  module_update_mision();
  
}

bool mission_get_state(){
  return block_notification;
}

void mision_enter_code() {
  menus_module_set_app_state(true, module_cb_code_register_event);
  module_display_code_selector();
}