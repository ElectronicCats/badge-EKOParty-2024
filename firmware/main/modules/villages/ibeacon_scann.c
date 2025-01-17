/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

/****************************************************************************
 *
 * This file is for iBeacon demo. It supports both iBeacon sender and receiver
 * which is distinguished by macros IBEACON_SENDER and IBEACON_RECEIVER,
 *
 * iBeacon is a trademark of Apple Inc. Before building devices which use
 *iBeacon technology, visit https://developer.apple.com/ibeacon/ to obtain a
 *license.
 *
 ****************************************************************************/

#include "ibeacon_scann.h"

#include "nvs_flash.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_defs.h"
#include "esp_gattc_api.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "villages.h"

static const char *DEMO_TAG = "IBEACON_DEMO";
extern esp_ble_ibeacon_vendor_t vendor_config;
static on_ibeacon_cb_t on_ibeacon_cb = NULL;

static void on_ibeacon(esp_ble_ibeacon_t *ibeacon,
                       esp_ble_gap_cb_param_t *scan_result) {
  if (on_ibeacon_cb) {
    on_ibeacon_cb(ibeacon, scan_result);
  }
}

/// Declare static functions
static void esp_gap_cb(esp_gap_ble_cb_event_t event,
                       esp_ble_gap_cb_param_t *param);

static esp_ble_scan_params_t ble_scan_params = {
    .scan_type = BLE_SCAN_TYPE_ACTIVE,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval = 0x50,
    .scan_window = 0x30,
    .scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE};

static void esp_gap_cb(esp_gap_ble_cb_event_t event,
                       esp_ble_gap_cb_param_t *param) {
  esp_err_t err;

  switch (event) {
  case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT: {
    break;
  }
  case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT: {
    uint32_t duration = 0;
    esp_ble_gap_start_scanning(duration);
    break;
  }
  case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
    // scan start complete event to indicate scan start successfully or failed
    if ((err = param->scan_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
      ESP_LOGE(DEMO_TAG, "Scan start failed: %s", esp_err_to_name(err));
    }
    break;
  case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
    // adv start complete event to indicate adv start successfully or failed
    if ((err = param->adv_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
      ESP_LOGE(DEMO_TAG, "Adv start failed: %s", esp_err_to_name(err));
    }
    break;
  case ESP_GAP_BLE_SCAN_RESULT_EVT: {
    esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
    switch (scan_result->scan_rst.search_evt) {
    case ESP_GAP_SEARCH_INQ_RES_EVT:
      /* Search for BLE iBeacon Packet */
      if (esp_ble_is_ibeacon_packet(scan_result->scan_rst.ble_adv,
                                    scan_result->scan_rst.adv_data_len)) {
        esp_ble_ibeacon_t *ibeacon_data =
            (esp_ble_ibeacon_t *)(scan_result->scan_rst.ble_adv);
        // ESP_LOGI(DEMO_TAG, "----------iBeacon Found----------");
        on_ibeacon(ibeacon_data, scan_result);
        // ESP_LOG_BUFFER_HEX("IBEACON_DEMO: Device address:",
                          //  scan_result->scan_rst.bda, ESP_BD_ADDR_LEN);
        // ESP_LOG_BUFFER_HEX("IBEACON_DEMO: Proximity UUID:",
                          //  ibeacon_data->ibeacon_vendor.proximity_uuid,
                          //  ESP_UUID_LEN_128);

        uint16_t major = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.major);
        uint16_t minor = ENDIAN_CHANGE_U16(ibeacon_data->ibeacon_vendor.minor);
        // ESP_LOGI(DEMO_TAG, "Major: 0x%04x (%d)", major, major);
        // ESP_LOGI(DEMO_TAG, "Minor: 0x%04x (%d)", minor, minor);
        // ESP_LOGI(DEMO_TAG, "Measured power (RSSI at a 1m distance):%d dbm",
                //  ibeacon_data->ibeacon_vendor.measured_power);
        // ESP_LOGI(DEMO_TAG, "RSSI of packet:%d dbm", scan_result->scan_rst.rssi);
      }
      break;
    default:
      break;
    }
    break;
  }

  case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
    if ((err = param->scan_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
      ESP_LOGE(DEMO_TAG, "Scan stop failed: %s", esp_err_to_name(err));
    } else {
      ESP_LOGI(DEMO_TAG, "Stop scan successfully");
    }
    break;

  case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
    if ((err = param->adv_stop_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
      ESP_LOGE(DEMO_TAG, "Adv stop failed: %s", esp_err_to_name(err));
    } else {
      ESP_LOGI(DEMO_TAG, "Stop adv successfully");
    }
    break;

  default:
    break;
  }
}

void ble_ibeacon_appRegister(void) {
  esp_err_t status;

  ESP_LOGI(DEMO_TAG, "register callback");

  // register the scan callback function to the gap module
  if ((status = esp_ble_gap_register_callback(esp_gap_cb)) != ESP_OK) {
    ESP_LOGE(DEMO_TAG, "gap register error: %s", esp_err_to_name(status));
    return;
  }
}

void ble_ibeacon_init() {
  esp_bluedroid_init();
  esp_bluedroid_enable();
  ble_ibeacon_appRegister();
}

void ibeacon_scann_begin() {
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  esp_bt_controller_init(&bt_cfg);
  esp_bt_controller_enable(ESP_BT_MODE_BLE);

  ble_ibeacon_init();

  esp_ble_gap_set_scan_params(&ble_scan_params);
}

void ibeacon_scann_set_on_ibeacon_cb(on_ibeacon_cb_t cb) { on_ibeacon_cb = cb; }
