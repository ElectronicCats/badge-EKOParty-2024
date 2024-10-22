#include "flame.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "oled_screen.h"
#include "preferences.h"
#include "toast.h"

uint32_t flame_time;

void flame_refresh(uint8_t frame);

static void load_flame_time() {
  flame_time = preferences_get_uint(FLAME_TIME_MEM, FLAME_TIME);
}

static void save_flame_time() {
  preferences_put_uint(FLAME_TIME_MEM, flame_time);
}

static void show_toast_scann(uint8_t dots) {
  if (!toast_is_ready()) {
    return;
  }
  oled_screen_display_bitmap(cup_bmp, 0, 8, 24, 24, OLED_DISPLAY_NORMAL);
  for (int i = 0; i < 3; i++) {
    oled_screen_display_text(i < dots ? "." : "", 104 + (i * 8), 1,
                             OLED_DISPLAY_NORMAL);
  }
}

static void show_flame_animation(uint8_t frame) {
  oled_screen_display_bitmap(flame_bmp_arr[frame], 52, 0, 24, 24,
                             OLED_DISPLAY_NORMAL);
}

static void show_remaining_time() {
  char time[10];
  uint8_t hours = flame_time / 3600;
  uint8_t minutes = (flame_time % 3600) / 60;
  uint8_t seconds = (flame_time % 3600) % 60;
  sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
  oled_screen_display_text_center(time, 3, OLED_DISPLAY_NORMAL);
}

static void flame_task() {
  static uint8_t frame = 0;
  load_flame_time();
  while (1) {
    if (!frame) {
      flame_time--;
      save_flame_time();
    }
    if (llamaneitor_scenes_get_scene() == LLAMANEITOR_FLAME_SCENE) {
      flame_refresh(frame);
    }
    frame = ++frame > 3 ? 0 : frame;
    vTaskDelay(250);
  }
}

void flame_refresh(uint8_t frame) {
  oled_screen_clear_buffer();
  toast_init();
  show_toast_scann(frame);
  show_remaining_time();
  show_flame_animation(frame);
  oled_screen_display_show();
}

void flame_task_begin() {
  xTaskCreate(flame_task, "flame_task", 2048, NULL, 10, NULL);
}

void flame_set_flame_time(uint32_t timestamp) {
  // TODO: Obtener el timestamp y callcular el tiempo restante
}

void flame_feed_flame() {
  flame_time += 600;
  save_flame_time();
}