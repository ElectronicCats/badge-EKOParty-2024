#include "sounds.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static void play_sound(){
  // buzzer_set_freq(440);
  // buzzer_play_for(500);
  // vTaskDelay(500 / portTICK_PERIOD_MS);
  // buzzer_play_for(500);
  // vTaskDelay(500 / portTICK_PERIOD_MS);
  // buzzer_play_for(500);
  // vTaskDelay(500 / portTICK_PERIOD_MS);
  // buzzer_set_freq(349);
  // buzzer_play_for(350);

  for(int i = 0; i < 60; i++){
    buzzer_set_freq(notes[i]);
    buzzer_play_for(times[i]);
    vTaskDelay(times[i] / portTICK_PERIOD_MS);
  }
  buzzer_stop();
  vTaskDelete(NULL);
}

void sounds_play_music() {
  xTaskCreate(play_sound, "play_sound", 4096, NULL, 5, NULL);
}