#include <stdio.h>
#include "badge_connect.h"
#include "badge_link_module.h"
#include "buzzer.h"
#include "cat_console.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "flash_fs.h"
#include "flash_fs_screens.h"
#include "keyboard_module.h"
#include "menus_module.h"
#include "open_thread.h"
#include "preferences.h"
#include "sd_card.h"
#include "web_file_browser.h"
#include "wifi_app.h"
#include "neopixels_module.h"
#include "neopixels_events.h"
#include "lora_manager.h"
#include "llamaneitor.h"


static const char* TAG = "main";

void app_main() {
#if !defined(CONFIG_MAIN_DEBUG)
  esp_log_level_set(TAG, ESP_LOG_NONE);
#endif
  preferences_begin();
  if (preferences_get_int("dp_select", 0) == 0) {
    preferences_put_int("dp_select", 5);
  }
  flash_fs_begin(flash_fs_screens_handler);
  sd_card_begin();
  keyboard_module_begin();
  menus_module_begin();
  preferences_put_bool("wifi_connected", false);
  neopixels_module_begin();
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  neopixel_events_run_event(neopixel_scanning_event);
  lora_module_begin();
  buzzer_begin(11);
  buzzer_play_for(1000);
  llamaneitor_begin();
  // Always start the console at the end
  // cat_console_begin();
}