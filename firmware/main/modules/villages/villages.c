#include "villages.h"

#include <string.h>

#include "esp_log.h"
#include "ibeacon_scann.h"
#include "neopixels_module.h"

#define VILLAGE_RSSI_FILTER -70

#define VILLAGE_TAG "VILLAGE"

static void on_village_detected(village_t *village) {
  // TODO: show on screen
  neopixels_set_pixels(3, village->R, village->G, village->B);
  neopixels_refresh();
}

static village_t *get_village_by_uuid(esp_ble_ibeacon_t *ibeacon,
                                      esp_ble_gap_cb_param_t *scan_result) {
  for (uint8_t i = 0; i < VILLAGES_COUNT; i++) {
    int8_t rssi = scan_result->scan_rst.rssi;
    if (!memcmp(villages[i].uuid, ibeacon->ibeacon_vendor.proximity_uuid,
                UUID_LEN)) {
      return rssi > VILLAGE_RSSI_FILTER ? &villages[i] : NULL;
    }
  }
  return NULL;
}

static void on_ibeacon_cb(esp_ble_ibeacon_t *ibeacon,
                          esp_ble_gap_cb_param_t *scan_result) {
  village_t *village = get_village_by_uuid(ibeacon, scan_result);
  if (village) {
    ESP_LOGI(VILLAGE_TAG, "%s\n", village->name);
    ESP_LOGI(VILLAGE_TAG, "%d\n", scan_result->scan_rst.rssi);
    on_village_detected(village);
  } else {
    ESP_LOGE(VILLAGE_TAG, "UUID UNRECOGNIZED\n");
  }
}

void villages_begin() {
  ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb);
  ibeacon_scann_begin();
}