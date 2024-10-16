#include "toast.h"

#include "badge_connect.h"
#include "badge_pairing.h"
#include "espnow.h"
#include "general_screens.h"
#include "menus_module.h"
#include "nvs_flash.h"
#include "oled_screen.h"

void toast_exit();

toast_ctx_t *ctx = NULL;

static void show_scaning_dots(uint8_t x, uint8_t page) {
  static uint8_t dots = 0;
  dots = ++dots > 3 ? 0 : dots;
  for (int i = 0; i < 3; i++) {
    oled_screen_display_text(i < dots ? "." : "", x + (i * 8), page,
                             OLED_DISPLAY_NORMAL);
  }
}

static void show_waiting_screen() {
  genera_screen_display_notify_information("Brindis", "");
  show_scaning_dots(52, 3);
}

static void toast_task() {
  while (ctx != NULL) {
    show_waiting_screen();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
  vTaskDelete(NULL);
}

static void toast_input_cb(uint8_t button_name, uint8_t button_event) {
  if (button_event != BUTTON_DOWN) {
    return;
  }
  switch (button_name) {
  case BUTTON_LEFT:
    toast_exit();
    break;
  default:
    break;
  }
}

static void lets_toast() {
  printf("BRINDIS\n");
  toast_exit();
}

void toast_exit() {
  free(ctx);
  ctx = NULL;
  //   menus_module_set_app_state(false, NULL);
  badge_pairing_set_callbacks(NULL, NULL, NULL);
  badge_pairing_deinit();
  // TODO: SET MENU
}

static void nvs_init() {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
}

static void wifi_init() {
  esp_event_loop_create_default();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  nvs_init();

  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
  ESP_ERROR_CHECK(esp_wifi_start());
}

void toast_begin() {
  ctx = malloc(sizeof(toast_ctx_t));
  wifi_init();
  badge_connect_init();
  badge_connect_register_recv_cb(ping_handler);
  // badge_connect_set_ekoparty_badge();
  badge_pairing_begin();
  badge_pairing_set_callbacks(lets_toast, NULL, NULL); // TODO
  badge_pairing_init();
  menus_module_set_app_state(true, toast_input_cb);
  badge_pairing_set_any_team();
  xTaskCreate(toast_task, "vaccination_task", 2048, NULL, 10, NULL);
}