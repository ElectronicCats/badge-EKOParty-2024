#include "badge_connect.h"
#include "badge_link_module.h"
#include "buzzer.h"
#include "cat_console.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "flash_fs.h"
#include "flash_fs_screens.h"
#include "keyboard_module.h"
#include "leds.h"
#include "menus_module.h"
#include "open_thread.h"
#include "preferences.h"
#include "sd_card.h"
#include "web_file_browser.h"
#include "wifi_app.h"
#include <stdio.h>

static const char *TAG = "main";

void app_main() {
#if !defined(CONFIG_MAIN_DEBUG)
  esp_log_level_set(TAG, ESP_LOG_NONE);
#endif
  preferences_begin();

  bool stealth_mode = preferences_get_bool("stealth_mode", false);
  if (!stealth_mode) {
    leds_begin();
  }
  // Hardcoded for the dragon
  if (preferences_get_int("dp_select", 0) == 0) {
    preferences_put_int("dp_select", 5);
  }
  flash_fs_begin(flash_fs_screens_handler);
  sd_card_begin();
  keyboard_module_begin();
  menus_module_begin();
  preferences_put_bool("wifi_connected", false);

  // Always start the console at the end
  cat_console_begin();
}
