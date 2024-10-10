#include "villages.h"

#include <string.h>

#include "ibeacon_scann.h"

#define VILLAGE_RSSI_FILTER -70

static void on_village_detected() {}

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
    printf("%s\n", village->name);
    printf("%d\n", scan_result->scan_rst.rssi);
  } else {
    printf("UUID UNRECOGNIZED\n");
  }
}

void villages_begin() {
  ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb);
  ibeacon_scann_begin();
}