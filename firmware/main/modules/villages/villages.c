#include "villages.h"

#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "ibeacon_scann.h"
#include "neopixels_module.h"

#define VILLAGE_RSSI_FILTER -70
#define VILLAGES_TIMEOUT_S 5

#define VILLAGE_TAG "VILLAGE"

esp_timer_handle_t villages_timer = NULL;

typedef struct {
  villages_e idx;
  int8_t rssi;
} village_ctx_t;

static village_ctx_t village_ctx = {.idx = EKOPARTY, .rssi = -200};

static void on_villages_timeout() {
  village_ctx.idx = EKOPARTY;
  village_ctx.rssi = -200;
  neopixels_set_pixels(3, 0, 0, 0);
  neopixels_refresh();
}

static void on_village_detected(village_t *village) {
  // TODO: show on screen
  neopixels_set_pixels(3, village->R, village->G, village->B);
  neopixels_refresh();
}

static village_t *get_village_by_uuid(esp_ble_ibeacon_t *ibeacon,
                                      esp_ble_gap_cb_param_t *scan_result) {
  for (uint8_t i = 1; i < VILLAGES_COUNT; i++) {
    int8_t rssi = scan_result->scan_rst.rssi;
    if (!memcmp(villages[i].uuid, ibeacon->ibeacon_vendor.proximity_uuid,
                UUID_LEN)) {
      if (rssi > VILLAGE_RSSI_FILTER) {
        return &villages[i];
      }
    }
  }
  return NULL;
}

static void on_ibeacon_cb(esp_ble_ibeacon_t *ibeacon,
                          esp_ble_gap_cb_param_t *scan_result) {
  village_t *village = get_village_by_uuid(ibeacon, scan_result);
  if (village) {
    esp_timer_stop(villages_timer);
    esp_timer_start_once(villages_timer, VILLAGES_TIMEOUT_S * 1000 * 1000);
    ESP_LOGI(VILLAGE_TAG, "%s\n", village->name);
    ESP_LOGI(VILLAGE_TAG, "%d\n", scan_result->scan_rst.rssi);
    if (village->idx == village_ctx.idx) {
      village_ctx.rssi = scan_result->scan_rst.rssi;
    } else if (scan_result->scan_rst.rssi > village_ctx.rssi) {
      village_ctx.rssi = scan_result->scan_rst.rssi;
      village_ctx.idx = village->idx;
      on_village_detected(village);
    }
  } else {
    ESP_LOGE(VILLAGE_TAG, "UUID UNRECOGNIZED\n");
  }
}

village_t *villages_get_current_village() { return &villages[village_ctx.idx]; }

void villages_begin() {
  ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb);
  ibeacon_scann_begin();

  esp_timer_create_args_t villages_timer_args = {
      .arg = NULL, .callback = on_villages_timeout};
  esp_timer_create(&villages_timer_args, &villages_timer);
}