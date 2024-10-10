#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "neopixels_events.h"
#include "neopixels_module.h"

#define MAX_BRIGHTNESS_VALUE 50

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

static TaskHandle_t neopixel_event_handler = NULL;

uint8_t get_random_uint8() {
  uint32_t entropy = esp_random();
  uint64_t time_since_boot = esp_timer_get_time();
  uint32_t seed = (entropy ^ time_since_boot) & 0xFFFFFFFF;
  srand(seed);

  return rand() % 256;
}

static rgb_color get_random_color() {
  rgb_color color;
  color.r = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  color.g = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  color.b = get_random_uint8() % MAX_BRIGHTNESS_VALUE + 1;
  return color;
}

void neopixel_scanning_event() {
  uint8_t neopixel_idx = 0;
  while (1) {
    rgb_color color = get_random_color();
    neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
    neopixels_set_pixel(neopixel_idx, color.r, color.g, color.b);
    neopixels_refresh();
    neopixel_idx = ++neopixel_idx < MAX_LED_NUMBER ? neopixel_idx : 0;
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void neopixel_events_stop_event() {
  neopixels_set_pixels(MAX_LED_NUMBER, 0, 0, 0);
  neopixels_refresh();
  vTaskDelete(neopixel_event_handler);
  neopixel_event_handler = NULL;
}

void neopixel_events_run_event(neopixel_event event) {
  xTaskCreate(event, "effect_function", 2048, NULL, 5, &neopixel_event_handler);
}