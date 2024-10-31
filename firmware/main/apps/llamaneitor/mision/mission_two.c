#include "mission_two.h"
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
#include "esp_random.h"
#include "screen_saver.h"

#define ITEMOFFSET 1
#define ITEM_PAGE_OFFSET 1
#define NUM_COLUMNS 16

static uint8_t scrolling_history_idx = 0;
static general_menu_t current_history;
static mission_two_state_t current_state = MISSION_TWO_YWH_IDLE;

static void mission_display_scrolling_text();
static void mission_follow_history();
uint8_t mission_hacked_active();

static const general_menu_t mission_two_carhacking_beacon_menu = {
    .menu_items = mission_two_carhacking_beacon,
    .menu_count = MISSION_TWO_CAR_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mission_two_red_beacon_hacked_menu = {
    .menu_items = mission_two_red_beacon_hacked,
    .menu_count = MISSION_TWO_RED_HACK_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mission_two_ywhack_beacon_hacked_menu = {
    .menu_items = mission_two_ywhack_beacon_hacked,
    .menu_count = MISSION_TWO_YWHACK_BEACONHACKED,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mission_two_ywhack_beacon_menu = {
    .menu_items = mission_two_ywhack_beacon,
    .menu_count = MISSION_TWO_YWHACK_BEACON,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static const general_menu_t mission_two_description_menu = {
    .menu_items = mission_two_description,
    .menu_count = MISSION_TWO_DESCRIPTION,
    .menu_level = GENERAL_TREE_APP_INFORMATION,
};

static void module_cb_code_register_event(uint8_t button_name, uint8_t button_event){
  if (button_event != BUTTON_PRESS_DOWN) {
    return;
    }
  switch (button_name) {
    case BUTTON_UP:
      scrolling_history_idx = scrolling_history_idx > 0 ? scrolling_history_idx - 1 : (current_history.menu_count - 1);
          mission_display_scrolling_text();
      break;
    case BUTTON_DOWN:
      scrolling_history_idx = scrolling_history_idx < (current_history.menu_count - 1) ? scrolling_history_idx + 1 : 0;
      if(scrolling_history_idx == (current_history.menu_count - 1)){
        mission_follow_history();
      }else{
        mission_display_scrolling_text();
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

static void mission_one_reset_history(){
  scrolling_history_idx = 0;
  menus_module_set_app_state(true, module_cb_code_register_event);
  mission_display_scrolling_text();
}

static void show_downloading_bar_mission(){
  oled_screen_clear();
  oled_screen_display_text_center("Descargando", 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text_center("Mision 2", 1, OLED_DISPLAY_NORMAL);
  for(int i = 0; i < 100; i++){
    oled_screen_display_loading_bar(i, 3);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static void mission_display_scrolling_text(){
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

  uint16_t end_index = scrolling_history_idx + items_per_screen;
  if (end_index > current_history.menu_count) {
    end_index = current_history.menu_count;
  }

  for (uint16_t i = scrolling_history_idx; i < end_index; i++) {
    oled_screen_display_text(current_history.menu_items[i], 3,
                            (i - scrolling_history_idx) + (ITEMOFFSET + screen_title),
                            OLED_DISPLAY_NORMAL);
  }
  oled_screen_display_show();
}

uint8_t mission_hacked_active(){
  return preferences_get_int(MISSION_TWO_HACKED, 0);
}

static void mission_follow_history(){
  switch(current_state){
    case MISSION_TWO_YWH_IDLE:
      break;
    case MISSION_TWO_RED_HACKED:
      llamaneitor_scenes_main_menu();
      break;
    case MISSION_TWO_CAR_BEACON_IDLE:
      current_history = mission_two_description_menu;
      current_state = MISSION_TWO_SHOW_MISSION;
      preferences_put_int(FSAVE_STATE_TWO, current_state);
      preferences_put_int(FMISSION_2, 1);
      show_downloading_bar_mission();
      mission_one_reset_history();
      break;
    case MISSION_TWO_SHOW_MISSION:
      llamaneitor_scenes_main_menu();
      break;
    default:
    break;
  }
}

static void mission_beacon_dissector(uint8_t village_idx){
  uint8_t is_unlocked_mission_two = preferences_get_int(FMISSION_2, 0);
  uint8_t is_hacked = mission_hacked_active();
  if(village_idx == CAR_HACK){
    if(is_unlocked_mission_two == 0){
      current_history = mission_two_carhacking_beacon_menu;
      current_state = MISSION_TWO_CAR_BEACON_IDLE;
    }else{
      return;
    }
  }
  if(village_idx == YWE_HACK){
    if(is_unlocked_mission_two == 0){
      preferences_put_int(FMISSION_2, 1);
    }
    if(is_hacked == 1){
      current_history = mission_two_ywhack_beacon_hacked_menu;
      
    }else{
      current_history = mission_two_ywhack_beacon_menu;
    }
    current_state = MISSION_TWO_SHOW_MISSION;
  }
  mission_one_reset_history();
}

static void mission_two_hacked_animation(){
  screen_saver_stop();
  oled_screen_clear();
  oled_driver_set_encrypt_value(true);
  oled_screen_display_text("EKOPARTY__CELEBRA", 0, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("SUS_EFGHIJKLM20__", 0, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("A\32OS0EVENTO_ADE__", 0, 2, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("EVEN0EVENTO_ATO__", 0, 3, OLED_DISPLAY_NORMAL);
  oled_driver_set_encrypt_value(false);
  oled_screen_display_text_center("Sistema", 1, OLED_DISPLAY_INVERT);
  oled_screen_display_text_center("Hackeado", 2, OLED_DISPLAY_INVERT);
  oled_screen_display_text_center("By r0r0x", 3, OLED_DISPLAY_INVERT);
  
  vTaskDelay(pdMS_TO_TICKS(2000));
  sounds_stop_music();
  vTaskDelay(pdMS_TO_TICKS(2000));
  sounds_play_soundtrack(play_nggyup);
  preferences_put_int(MISSION_TWO_HACKED, 1);
  current_history = mission_two_red_beacon_hacked_menu;
  current_state = MISSION_TWO_RED_HACKED;
  mission_one_reset_history();
}

static void mission_two_unhack_animation(){
  screen_saver_stop();
  oled_screen_clear();
  oled_screen_display_bitmap(llamaneitor_1, 0, 0, 32, 32, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Sistema", 40, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Recuperado", 40, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Mas cuidado", 40, 2, OLED_DISPLAY_NORMAL);
  vTaskDelay(pdMS_TO_TICKS(3000));
  oled_screen_clear();
  oled_screen_display_text("Completa la", 0, 0, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Mision 2 si", 0, 1, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("No quieres ", 0, 2, OLED_DISPLAY_NORMAL);
  oled_screen_display_text("Ser hackeado ", 0, 2, OLED_DISPLAY_NORMAL);
  oled_screen_clear();
  preferences_put_int(MISSION_TWO_HACKED, 0);
  current_state = MISSION_TWO_YWH_IDLE;
  llamaneitor_scenes_main_menu();
}

void mission_two_hacked_begin(uint8_t village_idx){
  if(mission_hacked_active() == 1){
    return;
  }
  current_state = preferences_get_int(FSAVE_STATE_TWO, MISSION_TWO_RED_HACKED);
  sounds_play_soundtrack(play_imperial_march);
  mission_two_hacked_animation();
}

void mission_two_begin(uint8_t village_idx){
  current_state = preferences_get_int(FSAVE_STATE_TWO, MISSION_TWO_YWH_IDLE);
  mission_beacon_dissector(village_idx);
}